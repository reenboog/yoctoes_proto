#ifndef __UNIT_H_
#define __UNIT_H_

#include "cocos2d.h"
#include "Constants.h"
#include "Func.h"

class Road;

class Unit : public cocos2d::Node {
public:
    static Unit *create(Constants::TeamColor team);
    ~Unit();

    void startTrek(float delayTime);
    void setRoute(std::vector<Road *> route, bool needSwapFirst = false);
    int getCount() const;
    void setCount(int count);
    const Constants::TeamColor &getTeamColor() const;
    void setColor(Constants::TeamColor const &color);
    Constants::TeamGroup const &getTeamGroup() const;
    void setTeamGroup(Constants::TeamGroup const &group);
    Unit *getLastCollidedUnit() const;
    void setLastCollidedUnit(Unit *lastCollidedUnit);
    cocos2d::Sprite *getUnitBody() const;
    bool isShouldBeRemoved() const;
    void setShouldBeRemoved(bool shouldBeRemoved);

private:
    bool init(Constants::TeamColor color);
    cocos2d::Sequence *addActionsToSequence(std::vector<cocos2d::FiniteTimeAction *> actions, cocos2d::Sequence *sequence);
    std::string determineFilename();

    float speed_;
    Constants::TeamColor color_;
    Constants::TeamGroup group_;
    std::vector<Road *> route_;
    bool needSwapFirst_;
    int count_;
    cocos2d::Sprite *unitBody_;
    cocos2d::Sprite *shadow_;
    cocos2d::Label *countLabel_;
    Unit *lastCollidedUnit_;
    bool shouldBeRemoved_;
};

inline void Unit::setRoute(std::vector<Road *> route, bool needSwapFirst) {
    route_ = route;
    needSwapFirst_ = needSwapFirst;
}

inline int Unit::getCount() const {
    return count_;
}

inline void Unit::setCount(int count) {
    count_ = count;
    countLabel_->setString(stringWithFormat("%d", count));
}

inline const Constants::TeamColor &Unit::getTeamColor() const {
    return color_;
}

inline void Unit::setColor(Constants::TeamColor const &color) {
    color_ = color;
}

inline Constants::TeamGroup const &Unit::getTeamGroup() const {
    return group_;
}

inline void Unit::setTeamGroup(Constants::TeamGroup const &group) {
    group_ = group;
}

inline Unit *Unit::getLastCollidedUnit() const {
    return lastCollidedUnit_;
}

inline void Unit::setLastCollidedUnit(Unit *lastCollidedUnit) {
    lastCollidedUnit_ = lastCollidedUnit;
}

inline cocos2d::Sprite *Unit::getUnitBody() const {
    return unitBody_;
}

inline bool Unit::isShouldBeRemoved() const {
    return shouldBeRemoved_;
}

inline void Unit::setShouldBeRemoved(bool shouldBeRemoved) {
    shouldBeRemoved_ = shouldBeRemoved;
}


#endif //__UNIT_H_
