#include "Tower.h"
#include "Unit.h"
#include "Func.h"

using namespace std;
using namespace cocos2d;

const int UNITS_LIMIT = 30;

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
    if (type == Constants::TowerType::type1) {
        filename = "tower.png";
        team_ = Constants::TeamType::red;
    } else if (type == Constants::TowerType::type2) {
        filename = "enemy_tower.png";
        team_ = Constants::TeamType::blue;
    }

    if (!Sprite::initWithFile(filename))
        return false;

    unitsLabel_ = Label::createWithTTF("0", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(32.0f, 32.0f); //fixme
    this->addChild(unitsLabel_);

    generateUnitTime_ = Constants::TowerType::type0 == type ? 0 : randInRangef(2.0f, 3.0f);

    towerType_ = type;

    return true;
}

void Tower::update(float dt) {
    if (unitsCount_ < UNITS_LIMIT) {
        if (timeAfterLastUnit_ <= generateUnitTime_) {
            timeAfterLastUnit_ += dt;
        } else {
            timeAfterLastUnit_ = 0;
            unitsCount_ = unitsCount_ + 1;
            this->updadeUnitsLabel();
        }
    }
}

void Tower::checkForApplying(Unit *unit) {
    if (team_ != unit->getTeam()) {
        this->applyUnit(unit);
    }
}

void Tower::applyUnit(Unit *unit) {
    int count = unit->getCount();
    unit->stopAllActions();
    unit->removeFromParentAndCleanup(true);

    int sign = team_ != unit->getTeam() ? -1 : 1;
    unitsCount_ = MAX(unitsCount_ + sign * count, 0);
    this->updadeUnitsLabel();
}

void Tower::updadeUnitsLabel() {
    unitsLabel_->setString(stringWithFormat("%d", unitsCount_));
}

int Tower::takeHalfUnits() {    //todo: refactor me!
    int takingCount = unitsCount_ / 2;
    unitsCount_ = unitsCount_ - takingCount;
    this->updadeUnitsLabel();
    return takingCount;
}
