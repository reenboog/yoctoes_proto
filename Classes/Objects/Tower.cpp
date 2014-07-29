#include "Tower.h"
#include "Unit.h"
#include "EventsMediator.h"

using namespace std;
using namespace cocos2d;

const int UNITS_LIMIT = 30;

WinLoseProtocol::~WinLoseProtocol() {
}

Tower *Tower::createWithType(Constants::TeamColor color) {
    Tower *tower = new Tower();
    if (tower->initWithType(color)) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

Tower::~Tower() {
}

bool Tower::initWithType(Constants::TeamColor color) {
    color_ = color;
    string filename = this->determineFilename();
    if (!Sprite::initWithFile(filename))
        return false;

    unitsCount_ = 1;

    unitsLabel_ = Label::createWithTTF("1", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(32.0f, 32.0f); //fixme
    this->addChild(unitsLabel_);

    lastAppliedUnit_ = nullptr;

    generateUnitCooldown_ = Constants::TeamColor::unfilled == color_ ? 0 : randInRangef(2.0f, 3.0f);
    if (color_ != Constants::TeamColor::blue && color_ != Constants::TeamColor::unfilled) {
        actionCooldown_ = randInRangef(5.0f, 6.0f);    //FIXME: bicycle
    } else {
        actionCooldown_ = 1.0f;
    }

    natureType_ = (Constants::NatureTypes) randInRangei(0, 4);

    return true;
}

void Tower::update(float dt) {
    //unit generation
    if (Constants::TeamColor::unfilled != color_) {
        if (unitsCount_ < UNITS_LIMIT) {
            if (timeAfterLastUnit_ <= generateUnitCooldown_) {
                timeAfterLastUnit_ += dt;
            } else {
                timeAfterLastUnit_ = 0;
                unitsCount_ = unitsCount_ + 1;
                this->updateUnitsLabel();
            }
        }
    }

    //npc tower action
    if (color_ != Constants::TeamColor::blue && color_ != Constants::TeamColor::unfilled) {
        actionCooldown_ -= dt;    //FIXME: bicycle
    }

    //selection action
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
    if (group_ != unit->getTeamGroup()) {
        unit->stopAllActions();
        this->applyUnit(unit);
    }
}

void Tower::applyUnit(Unit *unit) {
    int count = unit->getCount();
    unit->stopAllActions();
    unit->setShouldBeRemoved(true);
    if (lastAppliedUnit_ != unit) {
        lastAppliedUnit_ = unit;
    } else {
        return;
    }

    if (color_ == Constants::TeamColor::unfilled) {
        unitsCount_ = unitsCount_ + count;
        this->changeToTeam(unit->getTeamColor());
    } else if (group_ == unit->getTeamGroup()) {
        unitsCount_ = unitsCount_ + count * (int) influenceOfTheFirstToSecond(this->getNatureType(), unit->getNatureType());
    } else {
        unitsCount_ = unitsCount_ - count;
        if (unitsCount_ < 0) {
            unitsCount_ = -unitsCount_;
            this->changeToTeam(unit->getTeamColor());
        }
    }

    this->updateUnitsLabel();
    this->checkWin();
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
    string filename;
    switch (color_) {
        case Constants::TeamColor::blue:
            filename = "blue_tower.png";
            group_ = Constants::TeamGroup::alfa;
            break;
        case Constants::TeamColor::red:
            filename = "red_tower.png";
            group_ = Constants::TeamGroup::omega;
            break;
        case Constants::TeamColor::green:
            filename = "green_tower.png";
            group_ = Constants::TeamGroup::alfa;
            break;
        case Constants::TeamColor::yellow:
            filename = "yellow_tower.png";
            group_ = Constants::TeamGroup::omega;
            break;
        default:
            filename = "neutral_tower.png";
            group_ = Constants::TeamGroup::neutral;
    }

    return filename;
}

void Tower::changeToTeam(Constants::TeamColor newTeam) {
    //tower already has params - according to this we need to change image

    color_ = newTeam;
    string filename = this->determineFilename();
    Sprite *newSprite = Sprite::create(filename);
    this->setSpriteFrame(newSprite->getSpriteFrame());
    generateUnitCooldown_ = randInRangef(2.0f, 3.0f);

    //check events after capture
    if (events_.find(Constants::Events::T_afterCaptureTheTowerWin) != events_.end()) {
        GameLayerMemFun pFoo = &GameLayer::win;
        EventsMediator::sharedInstance()->selectorToGameLayer(pFoo);
    }
}

void Tower::checkWin() {
    if (delegate_) {
        delegate_->checkWin();
    }
}

#pragma mark - events

void Tower::addEvent(Constants::Events event) {
    events_.insert(event);
}
