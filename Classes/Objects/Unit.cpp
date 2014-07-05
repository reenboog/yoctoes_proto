#include "Unit.h"

using namespace cocos2d;

Unit *Unit::create() {
    Unit *unit = new Unit();
    if (unit->init()) {
        unit->autorelease();
    } else {
        CC_SAFE_DELETE(unit);
    }
    return unit;
}

Unit::~Unit() {
}

bool Unit::init() {
    if (!Sprite::initWithFile("unit.png"))
        return false;

    this->setAnchorPoint({0.0f, 0.0f});

    return true;
}
