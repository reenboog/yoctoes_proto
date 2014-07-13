#include "Tower.h"
#include "Unit.h"
#include "Func.h"

using namespace std;
using namespace cocos2d;

const int UNITS_LIMIT = 30;

Tower *Tower::createWithType(Constants::TeamType team) {
    Tower *tower = new Tower();
    if (tower->initWithType(team)) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

Tower::~Tower() {
}

bool Tower::initWithType(Constants::TeamType team) {
    team_ = team;
    string filename = this->determineFilename();
    if (!Sprite::initWithFile(filename))
        return false;

    unitsLabel_ = Label::createWithTTF("0", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(32.0f, 32.0f); //fixme
    this->addChild(unitsLabel_);

    generateUnitTime_ = Constants::TeamType::neutral == team_ ? 0 : randInRangef(2.0f, 3.0f);

    return true;
}

void Tower::update(float dt) {
    if (Constants::TeamType::neutral != team_) {
        if (unitsCount_ < UNITS_LIMIT) {
            if (timeAfterLastUnit_ <= generateUnitTime_) {
                timeAfterLastUnit_ += dt;
            } else {
                timeAfterLastUnit_ = 0;
                unitsCount_ = unitsCount_ + 1;
                this->updateUnitsLabel();
            }
        }
    }
    if (selected_) {
        if (!selectionAnimated_) {
            selectionAnimated_ = true;
            selection_ = Sprite::create("select.png");
            selection_->setAnchorPoint({0.0f, 0.0f});
            this->addChild(selection_);
        }
    } else {
        selectionAnimated_ = false;
        this->removeChild(selection_, true);
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

    unitsCount_ = unitsCount_ + count;
    if (team_ == Constants::TeamType::neutral) {
        this->changeToTeam(unit->getTeam());
    } else if (unitsCount_ < 0) {
        unitsCount_ = -unitsCount_;
        this->changeToTeam(unit->getTeam());
    }
    this->updateUnitsLabel();
}

void Tower::updateUnitsLabel() {
    unitsLabel_->setString(stringWithFormat("%d", unitsCount_));
}

int Tower::takeHalfUnits() {    //todo: refactor me!
    int takingCount = unitsCount_ / 2;
    unitsCount_ = unitsCount_ - takingCount;
    this->updateUnitsLabel();
    return takingCount;
}

std::string Tower::determineFilename() {
    string filename = "neutral.png"; //todo: add default value
    if (team_ == Constants::TeamType::red) {
        filename = "tower.png";
    } else if (team_ == Constants::TeamType::blue) {
        filename = "enemy_tower.png";
    }
    return filename;
}

void Tower::changeToTeam(Constants::TeamType newTeam) {
    //tower already has params - according to this we need to change image

    team_ = newTeam;
    string filename = this->determineFilename();
    Sprite *newSprite = Sprite::create(filename);
    this->setSpriteFrame(newSprite->getSpriteFrame());
    generateUnitTime_ = randInRangef(2.0f, 3.0f);
}
