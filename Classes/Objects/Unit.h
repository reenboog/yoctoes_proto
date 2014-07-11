#ifndef __UNIT_H_
#define __UNIT_H_

#include "cocos2d.h"

class Road;

class Unit : public cocos2d::Sprite {
public:
    static Unit *create();
    ~Unit();

    void startTrek();
    void setRoute(std::vector<Road *> route, bool needSwapFirst = false);

private:
    bool init();
    cocos2d::Sequence *addActionsToSequence(std::vector<cocos2d::FiniteTimeAction *> actions, cocos2d::Sequence *sequence);

    float speed_;
    std::vector<Road *> route_;
    bool needSwapFirst_;
};

inline void Unit::setRoute(std::vector<Road *> route, bool needSwapFirst) {
    route_ = route;
    needSwapFirst_ = needSwapFirst;
}


#endif //__UNIT_H_
