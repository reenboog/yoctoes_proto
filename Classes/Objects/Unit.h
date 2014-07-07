#ifndef __UNIT_H_
#define __UNIT_H_

#include "cocos2d.h"

class Unit : public cocos2d::Sprite {
public:
    static Unit *create();
    ~Unit();

    void startTrek();
    void setWayPoints(std::vector<cocos2d::Point> wayPoints);

private:
    bool init();
    cocos2d::Sequence *makeSequence(std::vector<cocos2d::FiniteTimeAction *> actions);

    float speed_;
    std::vector<cocos2d::Point> wayPoints_;
};

inline void Unit::setWayPoints(std::vector<cocos2d::Point> wayPoints) {
    wayPoints_ = wayPoints;
}


#endif //__UNIT_H_
