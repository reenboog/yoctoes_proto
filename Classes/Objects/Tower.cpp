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

    this->setAnchorPoint({0.0f, 0.0f});

    type_ = type;
    element_ = Constants::TowerElement::none;

    return true;
}

#pragma mark -

void Tower::updateToType(Constants::TowerType type) {

}
