#include "Tower.h"

Tower *Tower::createWithType(Constants::TowerType type) {
    return nullptr;
}

Tower::~Tower() {
    //
}

bool Tower::initWithType(Constants::TowerType type) {
    if (!(Sprite::init()))
        return false;

    type_ = Constants::TowerType::common;
    element_ = Constants::TowerElement::none;

    return true;
}

#pragma mark -

void Tower::updateToType(Constants::TowerType type) {

}
