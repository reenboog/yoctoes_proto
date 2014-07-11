#include "Tower.h"
#include "Unit.h"

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
}

bool Tower::initWithType(Constants::TowerType type) {
    std::string filename = "tower.png"; //todo: add default value
    if (type == Constants::TowerType::player) {
        filename = "tower.png";
    } else if (type == Constants::TowerType::enemy) {
        filename = "enemy_tower.png";
    }
    if (!Sprite::initWithFile(filename))
        return false;

    towertype_ = type;

    return true;
}

bool Tower::applyUnit(Unit *unit) {
    printf("check mek mek");
    return false;
}
