#include "TowersManager.h"
#include "BlueTowerView.h"
#include "RedTowerView.h"
#include "YellowTowerView.h"
#include "GreenTowerView.h"
#include "NeutralTowerView.h"
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
    switch (color) {
        case TeamColor::blue:
            tower->updateTowerView(BlueTowerView::create());
            tower->setGroup(TeamGroup::alfa);
            break;
        case TeamColor::red:
            tower->updateTowerView(RedTowerView::create());
            tower->setGroup(TeamGroup::omega);
            break;
        case TeamColor::yellow:
            tower->updateTowerView(YellowTowerView::create());
            tower->setGroup(TeamGroup::omega);
            break;
        case TeamColor::green:
            tower->updateTowerView(GreenTowerView::create());
            tower->setGroup(TeamGroup::alfa);
            break;
        default:
            tower->updateTowerView(NeutralTowerView::create());
            tower->setGroup(TeamGroup::neutral);
    }

    return tower;
}

#pragma mark - updates

void TowersManager::changeTeam(Tower *tower, TeamColor color) {
    tower->setTeamColor(color);
    switch (color) {
        case TeamColor::blue:
            tower->updateTowerView(BlueTowerView::create());
            tower->setGroup(TeamGroup::alfa);
            break;
        case TeamColor::red:
            tower->updateTowerView(RedTowerView::create());
            tower->setGroup(TeamGroup::omega);
            break;
        case TeamColor::yellow:
            tower->updateTowerView(YellowTowerView::create());
            tower->setGroup(TeamGroup::omega);
            break;
        case TeamColor::green:
            tower->updateTowerView(GreenTowerView::create());
            tower->setGroup(TeamGroup::alfa);
            break;
        default:
            tower->updateTowerView(NeutralTowerView::create());
            tower->setGroup(TeamGroup::neutral);
    }
    tower->setGenerateUnitCooldown(randInRangef(2.0f, 3.0f));
}

TowerViewNode *TowersManager::getTowerViewNode(TeamColor color) {
    TowerViewNode *towerViewNode = nullptr;
    switch (color) {
        case TeamColor::blue:
            towerViewNode = BlueTowerView::create();
            break;
        case TeamColor::red:
            towerViewNode = RedTowerView::create();
            break;
        case TeamColor::yellow:
            towerViewNode = YellowTowerView::create();
            break;
        case TeamColor::green:
            towerViewNode = GreenTowerView::create();
            break;
        default:
            towerViewNode = NeutralTowerView::create();
    }
    return towerViewNode;
}
