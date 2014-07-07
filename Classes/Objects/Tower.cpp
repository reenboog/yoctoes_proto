#include "Tower.h"

Tower *Tower::createWithType(Constants::TowerType type) {
    Tower *tower = new Tower();
    if (tower->initWithType(type)) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

Tower::~Tower() {
    //
}

bool Tower::initWithType(Constants::TowerType type) {
    //TODO: fill filename here
    if (!Sprite::initWithFile("tower.png"))
        return false;

    towertype_ = type;
    distanceFromStart_ = INT_MAX;

    return true;
}

#pragma mark -

