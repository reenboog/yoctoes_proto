#include "Tower.h"
#include "Unit.h"
#include "TowerViewNode.h"
#include "EventsMediator.h"

using namespace std;
using namespace cocos2d;

const int UNITS_LIMIT = 30;

WinLoseProtocol::~WinLoseProtocol() {
}

Tower *Tower::createWithType(TeamColor color) {
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

bool Tower::initWithType(TeamColor color) {
    color_ = color;
    if (!Node::init())
        return false;

    unitsCount_ = 1;

    lastAppliedUnit_ = nullptr;

    generateUnitCooldown_ = TeamColor::unfilled == color_ ? 0 : randInRangef(2.0f, 3.0f);
    if (color_ != TeamColor::blue && color_ != TeamColor::unfilled) {
        actionCooldown_ = randInRangef(5.0f, 6.0f);    //FIXME: bicycle
    } else {
        actionCooldown_ = 1.0f;
    }

    natureType_ = (NatureType) randInRangei(0, 4);

    return true;
}

void Tower::update(float dt) {
    //unit generation
    if (TeamColor::unfilled != color_) {
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
    if (color_ != TeamColor::blue && color_ != TeamColor::unfilled) {
        actionCooldown_ -= dt;    //FIXME: bicycle
    }

    //selection action
    if (selected_) {
        if (!selectionAnimated_) {
            selectionAnimated_ = true;
            towerView_->selectTower();
        }
    } else {
        selectionAnimated_ = false;
        towerView_->unselectTower();
    }
}

void Tower::updateTowerView(TowerViewNode *newView) {
    this->removeChild(towerView_, true);
    towerView_ = newView;
    this->addChild(towerView_);
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

    if (color_ == TeamColor::unfilled) {
        unitsCount_ = unitsCount_ + count;
        this->changeTeam(this, unit->getTeamColor());
    } else if (group_ == unit->getTeamGroup()) {
        unitsCount_ = unitsCount_ + count * (int) influenceOfTheFirstToSecond(this->getNatureType(), unit->getNatureType());
    } else {
        unitsCount_ = unitsCount_ - count;
        if (unitsCount_ < 0) {
            unitsCount_ = -unitsCount_;
            this->changeTeam(this, unit->getTeamColor());
        }
    }

    this->updateUnitsLabel();
    this->checkWin();
}

void Tower::updateUnitsLabel() {
    towerView_->getUnitsLabel()->setString(stringWithFormat("%d", unitsCount_));
}

int Tower::takeHalfUnits() {    //todo: refactor me!
    int takingCount = unitsCount_ / 2;
    unitsCount_ = unitsCount_ - takingCount;
    this->updateUnitsLabel();
    return takingCount;
}

void Tower::changeTeam(Tower *tower, TeamColor color) {
    if (updateDelegate_) {
        updateDelegate_->changeTeam(tower, color);
    }
}

//void Tower::changeTeam(this, TeamColor newTeam) {
//    //tower already has params - according to this we need to change image
//
//    color_ = newTeam;
//    string filename = this->determineFilename();
//    Sprite *newSprite = Sprite::create(filename);
//    this->setSpriteFrame(newSprite->getSpriteFrame());
//    generateUnitCooldown_ = randInRangef(2.0f, 3.0f);
//
//    //check events after capture
//    if (events_.find(Event::T_afterCaptureTheTowerWin) != events_.end()) {
//        GameLayerMemFun pFoo = &GameLayer::win;
//        EventsMediator::sharedInstance()->selectorToGameLayer(pFoo);
//    }
//}

void Tower::checkWin() {
    if (delegate_) {
        delegate_->checkWin();
    }
}

#pragma mark - events

//void Tower::addEvent(Event event) {
//    events_.insert(event);
//}
