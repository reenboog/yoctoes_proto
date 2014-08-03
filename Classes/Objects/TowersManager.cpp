#include "TowersManager.h"
#include "WeakTowerView.h"
#include "StrongTowerView.h"
#include "Func.h"

using namespace std;
using namespace cocos2d;

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

Tower *TowersManager::createTowerWithParams(TeamColor color, NatureType type, int level) {
    Tower *tower = Tower::createWithType(color);
    tower->updateTowerView(WeakTowerView::create());
    tower->setParams(weakTowerParams);
    tower->getTowerView()->applyColor(this->colorForTeam(color));
    tower->setGroup(this->groupForTeam(color));

    return tower;
}

#pragma mark - updates

void TowersManager::changeTeam(Tower *tower, TeamColor color) {
    tower->setTeamColor(color);
    tower->updateTowerView(WeakTowerView::create());
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
