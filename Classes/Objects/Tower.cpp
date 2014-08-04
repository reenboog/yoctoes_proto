#include "Tower.h"
#include "Unit.h"
#include "TowerViewNode.h"
#include "EventsMediator.h"

using namespace std;
using namespace cocos2d;

const int LEVEL_CUP = 2;

WinLoseProtocol::~WinLoseProtocol() {
}

Tower *Tower::createWithType(TeamColor color) {
    Tower *tower = new Tower();
    if (tower->initWithType(color)) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

Tower::~Tower() {
}

bool Tower::initWithType(TeamColor color) {
    color_ = color;
    if (!Node::init())
        return false;

    unitsCount_ = 1;
    currentLevel_ = 1;
    readyForUpdate_ = false;
    updateButtonShown_ = false;
    unitsLimit_ = 0;
    power_ = 1;

    lastAppliedUnit_ = nullptr;

    generateUnitCooldown_ = TeamColor::unfilled == color_ ? 0 : randInRangef(1.0f, 1.0f);
    if (color_ != TeamColor::blue && color_ != TeamColor::unfilled) {
        actionCooldown_ = randInRangef(5.0f, 6.0f);    //FIXME: bicycle
    } else {
        actionCooldown_ = 1.0f;
    }

    natureType_ = (NatureType) randInRangei(0, 4);

    return true;
}

void Tower::update(float dt) {
    //unit generation
    readyForUpdate_ = false;
    if (TeamColor::unfilled != color_) {
        if (unitsCount_ < unitsLimit_ * power_) {
            if (timeAfterLastUnit_ <= generateUnitCooldown_) {
                timeAfterLastUnit_ += dt;
            } else {
                timeAfterLastUnit_ = 0;
                unitsCount_ = unitsCount_ + 1;
                this->updateUnitsLabel();
            }
        }
        if (currentLevel_ < LEVEL_CUP && towerType_ == TowerType::combat) {
            readyForUpdate_ = unitsCount_ >= unitsLimit_ * currentLevel_;
        }
    }

    //npc tower action
    if (color_ != TeamColor::blue && color_ != TeamColor::unfilled) {
        actionCooldown_ -= dt;    //FIXME: bicycle
    }

    //selection action
    if (selected_) {
        if (!selectionAnimated_) {
            selectionAnimated_ = true;
            towerView_->selectTower();
        }
    } else {
        selectionAnimated_ = false;
        towerView_->unselectTower();
    }

    if (readyForUpdate_) {
        if (color_ == TeamColor::blue) {
            if (!updateButtonShown_) {
                updateButtonShown_ = true;

                MenuItemSprite *upgrade = MenuItemSprite::create(
                        Sprite::create("upgrade_n.png"),
                        Sprite::create("upgrade_s.png"),
                        this,
                        menu_selector(Tower::upgradeTower));
                upgrade->setPosition(33, 15); //FIXME
                upgrade->setScale(3.0f);
                upgradeMenu_ = cocos2d::Menu::create(upgrade, NULL);
                upgradeMenu_->setPosition(0, 0); //FIXME
                this->addChild(upgradeMenu_, 120);
            }
        }
    } else {
        updateButtonShown_ = false;
        this->removeChild(upgradeMenu_, true);
    }
}

void Tower::updateTowerView(TowerViewNode *newView) {
    this->removeChild(towerView_, true);
    towerView_ = newView;
    this->addChild(towerView_);
}

void Tower::checkForApplying(Unit *unit) {
    if (group_ != unit->getTeamGroup()) {
        unit->stopAllActions();
        this->applyUnit(unit);
    }
}

void Tower::applyUnit(Unit *unit) {
    int count = unit->getCount();
    unit->stopAllActions();
    unit->setShouldBeRemoved(true);
    if (lastAppliedUnit_ != unit) {
        lastAppliedUnit_ = unit;
    } else {
        return;
    }

    if (color_ == TeamColor::unfilled) {
        unitsCount_ = unitsCount_ + count;
        this->changeTeam(this, unit->getTeamColor());
    } else if (group_ == unit->getTeamGroup()) {
        unitsCount_ = unitsCount_ + count * (int) influenceOfTheFirstToSecond(this->getNatureType(), unit->getNatureType());
    } else {
        unitsCount_ = unitsCount_ - count;
        if (unitsCount_ < 0) {
            unitsCount_ = -unitsCount_;
            this->changeTeam(this, unit->getTeamColor());
        }
    }

    this->updateUnitsLabel();
    this->checkWin();
}

void Tower::updateUnitsLabel() {
    towerView_->getUnitsLabel()->setString(stringWithFormat("%d", unitsCount_));
}

int Tower::takeHalfUnits() {    //todo: refactor me!
    int takingCount = unitsCount_ / 2;
    unitsCount_ = unitsCount_ - takingCount;
    this->updateUnitsLabel();
    return takingCount;
}

void Tower::changeTeam(Tower *tower, TeamColor color) {
    if (updateDelegate_) {
        updateDelegate_->changeTeam(tower, color);
    }
}

void Tower::upgradeTower(Ref *pSender) {
    if (updateDelegate_) {
        currentLevel_ = currentLevel_ + 1;
        updateButtonShown_ = false;
        this->removeChild(upgradeMenu_, true);
        unitsCount_ = unitsCount_ / 2;
        updateDelegate_->upgradeTower(this);
    }
}

void Tower::checkWin() {
    if (delegate_) {
        delegate_->checkWin();
    }
}
