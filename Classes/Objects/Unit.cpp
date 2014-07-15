#include "Unit.h"
#include "Road.h"
#include "Tower.h"

using namespace std;
using namespace cocos2d;

Unit *Unit::create(Constants::TeamColor color) {
    Unit *unit = new Unit();
    if (unit->init(color)) {
        unit->autorelease();
    } else {
        CC_SAFE_DELETE(unit);
    }
    return unit;
}

Unit::~Unit() {
}

bool Unit::init(Constants::TeamColor color) {
    if (!Node::init())
        return false;

    color_ = color;

    unitBody_ = Sprite::create(this->determineFilename());
    this->addChild(unitBody_);

    countLabel_ = Label::createWithTTF("0", "Chapaza.ttf", 13);
    countLabel_->setColor(Color3B::RED);
    this->addChild(countLabel_);

    speed_ = 0.5f;  //seconds from one tile to another

    return true;
}

void Unit::startTrek() {
    int size = route_.size();
    Sequence *resultAction = nullptr;

    Tower *currentTowerDestination = nullptr;
    for (int i = 0; i < size; ++i) {
        vector<cocos2d::Point> currentPoints;
        if (i == 0) {
            if (needSwapFirst_) {
                currentTowerDestination = route_[i]->getTowerOne();
                currentPoints = route_[i]->getRoadPoints();
                reverse(currentPoints.begin(), currentPoints.end());
            } else {
                currentTowerDestination = route_[i]->getTowerTwo();
                currentPoints = route_[i]->getRoadPoints();
            }
        } else {
            if (currentTowerDestination == route_[i]->getTowerOne()) {
                currentTowerDestination = route_[i]->getTowerTwo();
                currentPoints = route_[i]->getRoadPoints();
            } else {    // currentTowerDestination == route_[i]->getTowerTwo()
                currentTowerDestination = route_[i]->getTowerOne();
                currentPoints = route_[i]->getRoadPoints();
                reverse(currentPoints.begin(), currentPoints.end());
            }
        }
        currentPoints.push_back(currentTowerDestination->getPosition());

        int localSize = currentPoints.size();
        vector<FiniteTimeAction *> actions;
        for (int i = 0; i < localSize; ++i) {
            MoveTo *moveTo = MoveTo::create(speed_, currentPoints.at((unsigned long) i));
            actions.push_back(moveTo);
        }

        CallFunc *checkForApplyingAction =  CallFunc::create([this, currentTowerDestination]() {
            currentTowerDestination->checkForApplying(this);
        });
        actions.push_back(checkForApplyingAction);

        resultAction = addActionsToSequence(actions, resultAction);
    }

    vector<FiniteTimeAction *> actions;
    CallFunc *applyUnitAction =  CallFunc::create([this, currentTowerDestination]() {
        currentTowerDestination->applyUnit(this);
    });
    actions.push_back(applyUnitAction);
    resultAction = addActionsToSequence(actions, resultAction);

    this->runAction(resultAction);
}

Sequence *Unit::addActionsToSequence(vector<FiniteTimeAction *> actions, Sequence *sequence) {
    int size = actions.size();
    for (int i = 0; i < size; ++i) {
        FiniteTimeAction *action = actions.at(i);
        if (!sequence) {
            sequence = Sequence::create(action, NULL);
        } else {
            sequence = Sequence::create(sequence, action, NULL);
        }
    }

    return sequence;
}

std::string Unit::determineFilename() {
    string filename = "unit.png"; //todo: add default value
    if (color_ == Constants::TeamColor::red) {
        filename = "enemy.png";
    } else if (color_ == Constants::TeamColor::blue) {
        filename = "unit.png";
    }
    return filename;

}
