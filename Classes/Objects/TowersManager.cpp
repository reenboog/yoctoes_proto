#include "TowersManager.h"
#include "WeakTowerView.h"
#include "StrongTowerView.h"
#include "Func.h"
#include "PowerTowerView.h"
#include "PitTowerView.h"

using namespace std;
using namespace cocos2d;

const int kPitMenuTag = 234423;

TowersManager *TowersManager::sharedInstance_ = nullptr;

TowersManager *TowersManager::sharedInstance() {
    if (sharedInstance_ == nullptr) {
        sharedInstance_ = new TowersManager();
    }

    return sharedInstance_;
}

TowersManager::TowersManager() {
}

TowersManager::~TowersManager() {
}

#pragma mark - creations

Tower *TowersManager::createTowerWithParams(TowerType towerType, TeamColor color) {
    Tower *tower = Tower::createWithType(color);
    tower->setTowerType(towerType);
    switch (towerType) {
        case TowerType::combat_weak_neutral:
            tower->updateTowerView(WeakTowerView::create());
            break;
        case TowerType::combat_strong_neutral:
            tower->updateTowerView(StrongTowerView::create());
            break;
        case TowerType::pit:
            tower->updateTowerView(PitTowerView::create());
            break;
        case TowerType::power:
            tower->updateTowerView(PowerTowerView::create());
            break;
    }
    tower->setParams(weakTowerParams);
    tower->getTowerView()->applyColor(this->colorForTeam(color));
    tower->setGroup(this->groupForTeam(color));

    if (color != TeamColor::unfilled) {
        towerColorSet_[tower] = color;
    }

    return tower;
}

#pragma mark - updates

void TowersManager::changeTeam(Tower *tower, TeamColor color) {
    tower->setTeamColor(color);
    if (tower->getTowerFunction() == TowerFunction::combat) {
        tower->updateTowerView(WeakTowerView::create());
        this->removeEffectDst(tower);
    } else if (tower->getTowerFunction() == TowerFunction::power) {
        this->removeEffectSrc(tower);
        tower->updateTowerView(PowerTowerView::create());
    } else {
        this->removeEffectSrc(tower);
        set<TowerType> types = this->getTowerTypesForColor(tower->getTeamColor());
        this->showPitMenu(tower, types);
        return;
    }
    towerColorSet_[tower] = color;
    tower->getTowerView()->applyColor(this->colorForTeam(color));
    tower->setGroup(this->groupForTeam(color));
    tower->setGenerateUnitCooldown(randInRangef(2.0f, 3.0f));
}

void TowersManager::upgradeTower(Tower *tower) {
    tower->updateTowerView(StrongTowerView::create());
    tower->setParams(strongTowerParams);
    tower->getTowerView()->applyColor(this->colorForTeam(tower->getTeamColor()));
    tower->updateUnitsLabel();
}

void TowersManager::replacePit(Tower *tower, TowerType type) {
    switch (type) {
        case TowerType::power:
            tower->updateTowerView(PowerTowerView::create());
            break;
        case TowerType::combat_weak_neutral:
            tower->updateTowerView(WeakTowerView::create());
            tower->setParams(weakTowerParams);
            break;
        case TowerType::combat_strong_neutral:
            tower->updateTowerView(StrongTowerView::create());
            tower->setParams(strongTowerParams);
            break;
    }
    tower->setTowerType(type);
    tower->setGroup(this->groupForTeam(tower->getTeamColor()));
    tower->getTowerView()->applyColor(this->colorForTeam(tower->getTeamColor()));
}

Color3B TowersManager::colorForTeam(TeamColor color) {
    Color3B newColor;
    switch (color) {
        case TeamColor::blue:
            newColor = Color3B(39, 113, 200);
            break;
        case TeamColor::red:
            newColor = Color3B(205, 26, 69);
            break;
        case TeamColor::yellow:
            newColor = Color3B(244, 242, 46);
            break;
        case TeamColor::green:
            newColor = Color3B(46, 197, 21);
            break;
        default:
            newColor = Color3B(217, 151, 228);
    }

    return newColor;
}

TeamGroup TowersManager::groupForTeam(TeamColor color) {
    TeamGroup teamGroup;
    switch (color) {
        case TeamColor::blue:
            teamGroup = TeamGroup::alfa;
            break;
        case TeamColor::red:
            teamGroup = TeamGroup::omega;
            break;
        case TeamColor::yellow:
            teamGroup = TeamGroup::omega;
            break;
        case TeamColor::green:
            teamGroup = TeamGroup::alfa;
            break;
        default:
            teamGroup = TeamGroup::neutral;
    }

    return teamGroup;
}

#pragma mark - powerups

void TowersManager::addPoweredTower(Tower *src, Tower *dst) {
    this->checkPowerTower(src);
    poweredTowers_.push_back(make_pair(src, dst));
}

void TowersManager::removeEffectSrc(Tower *tower) { // power tower captured
    int size = poweredTowers_.size();
    for (int i = 0; i < size; ++i) {
        if (poweredTowers_.at((unsigned long) i).first == tower) {
            Tower *dst = poweredTowers_.at((unsigned long) i).second;
            dst->setPower(dst->getPower() - 1);
            poweredTowers_.erase(poweredTowers_.begin() + i);   //delete current power tower
            break;
        }
    }
}

void TowersManager::removeEffectDst(Tower *tower) { // subservient tower captured
    int size = poweredTowers_.size();
    for (int i = size - 1; i >= 0; --i) {
        if (poweredTowers_.at((unsigned long) i).second == tower) {
            Tower *src = poweredTowers_.at((unsigned long) i).first;
            src->setPower(1);
            poweredTowers_.erase(poweredTowers_.begin() + i);
        }
    }
}

void TowersManager::checkPowerTower(Tower *tower) {
    int size = poweredTowers_.size();
    for (int i = 0; i < size; ++i) {
        if (poweredTowers_.at((unsigned long) i).first == tower) {
            Tower *dst = poweredTowers_.at((unsigned long) i).second;
            dst->setPower(dst->getPower() - 1);
            poweredTowers_.erase(poweredTowers_.begin() + i);   //delete current power tower
            break;
        }
    }
}

set<TowerType> TowersManager::getTowerTypesForColor(TeamColor color) {
    set<TowerType> types;

    for (map<Tower *, TeamColor>::iterator iterator = towerColorSet_.begin(); iterator != towerColorSet_.end(); ++iterator) {
        if (iterator->second == color) {
            types.insert(iterator->first->getTowerType());
        }
    }

    return types;
}

void TowersManager::showPitMenu(Tower *tower, set<TowerType> types) {
    int size = types.size();
    float angle = 0.0f;
    float r = 35.0;
    float deltaAngle = (float) (2 * M_PI / size);
    Menu *pitMenu = Menu::create();
    pitMenu->setPosition({0.0f, 0.0f});
    for (set<TowerType>::iterator it = types.begin(); it != types.end(); ++it) {
        TowerType currentType = *it;
        float x = r * cos(angle);
        float y = r * sin(angle);
        angle = angle + deltaAngle;
        Sprite *menuSprite;
        switch (currentType) {
            case TowerType::power:
                menuSprite = PowerTowerView::getRenderedImage();
                break;
            case TowerType::combat_weak_neutral:
                menuSprite = WeakTowerView::getRenderedImage();
                break;
            case TowerType::combat_strong_neutral:
                menuSprite = StrongTowerView::getRenderedImage();
                break;
        }

        MenuItemSprite *item = MenuItemSprite::create(menuSprite, menuSprite,
                CC_CALLBACK_1(TowersManager::selectTower, this, tower, currentType));

        item->setPosition(x, y);
        pitMenu->addChild(item);
    }

    tower->addChild(pitMenu, 15, kPitMenuTag);
}

void TowersManager::selectTower(Ref *pSender, Tower *tower, TowerType towerType) {
    this->removeTipMenuFromTower(tower);
    this->replacePit(tower, towerType);
}

void TowersManager::removeTipMenuFromTower(Tower *tower) {
    Node *node = tower->getChildByTag(kPitMenuTag);
    if (node) {
        tower->removeChild(node, true);
    }
}
