#include "Unit.h"

using namespace std;
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

    this->setScale(0.5f);
    speed_ = 1.0f;

    return true;
}

void Unit::startTrek() {
    vector<FiniteTimeAction *> actions;

    const int size = wayPoints_.size();
    for (int i = 0; i < size; ++i) {
        MoveTo *moveTo = MoveTo::create(speed_, wayPoints_.at(i));
        actions.push_back(moveTo);
    }

    Sequence *action = makeSequence(actions);
    this->runAction(action);
}

Sequence *Unit::makeSequence(vector<FiniteTimeAction *> actions) {
    Sequence *seq = NULL;
    int size = actions.size();
    for (int i = 0; i < size; ++i) {
        FiniteTimeAction *action = actions.at(i);
        if (!seq) {
            seq = Sequence::create(action, NULL);
        } else {
            seq = Sequence::create(seq, action, NULL);
        }
    }
    return seq;
}
