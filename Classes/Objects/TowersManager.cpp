#include "TowersManager.h"
#include "WeakTowerView.h"
#include "StrongTowerView.h"
#include "Func.h"

using namespace std;

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
    switch (color) {
        case TeamColor::blue:
            tower->getTowerView()->applyColor(cocos2d::Color3B(39, 113, 200));
            tower->setGroup(TeamGroup::alfa);
            break;
        case TeamColor::red:
            tower->getTowerView()->applyColor(cocos2d::Color3B(205, 26, 69));
            tower->setGroup(TeamGroup::omega);
            break;
        case TeamColor::yellow:
            tower->getTowerView()->applyColor(cocos2d::Color3B(244, 242, 46));
            tower->setGroup(TeamGroup::omega);
            break;
        case TeamColor::green:
            tower->getTowerView()->applyColor(cocos2d::Color3B(46, 197, 21));
            tower->setGroup(TeamGroup::alfa);
            break;
        default:
            tower->getTowerView()->applyColor(cocos2d::Color3B(217, 151, 228));
            tower->setGroup(TeamGroup::neutral);
    }

    return tower;
}

#pragma mark - updates

void TowersManager::changeTeam(Tower *tower, TeamColor color) {
    tower->setTeamColor(color);
    tower->updateTowerView(WeakTowerView::create());
    switch (color) {
        case TeamColor::blue:
            tower->getTowerView()->applyColor(cocos2d::Color3B(39, 113, 200));
            tower->setGroup(TeamGroup::alfa);
            break;
        case TeamColor::red:
            tower->getTowerView()->applyColor(cocos2d::Color3B(205, 26, 69));
            tower->setGroup(TeamGroup::omega);
            break;
        case TeamColor::yellow:
            tower->getTowerView()->applyColor(cocos2d::Color3B(244, 242, 46));
            tower->setGroup(TeamGroup::omega);
            break;
        case TeamColor::green:
            tower->getTowerView()->applyColor(cocos2d::Color3B(46, 197, 21));
            tower->setGroup(TeamGroup::alfa);
            break;
        default:
            tower->getTowerView()->applyColor(cocos2d::Color3B(217, 151, 228));
            tower->setGroup(TeamGroup::neutral);
    }
    tower->setGenerateUnitCooldown(randInRangef(2.0f, 3.0f));
}

void TowersManager::upgradeTower(Tower *tower) {
    tower->updateTowerView(StrongTowerView::create());
    tower->setParams(strongTowerParams);
    switch (tower->getTeamColor()) {
        case TeamColor::blue:
            tower->getTowerView()->applyColor(cocos2d::Color3B(39, 113, 200));
            break;
        case TeamColor::red:
            tower->getTowerView()->applyColor(cocos2d::Color3B(205, 26, 69));
            break;
        case TeamColor::yellow:
            tower->getTowerView()->applyColor(cocos2d::Color3B(244, 242, 46));
            break;
        case TeamColor::green:
            tower->getTowerView()->applyColor(cocos2d::Color3B(46, 197, 21));
            break;
        default:
            tower->getTowerView()->applyColor(cocos2d::Color3B(217, 151, 228));
    }
}
