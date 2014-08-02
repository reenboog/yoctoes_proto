#ifndef __UNIT_H_
#define __UNIT_H_

#include "cocos2d.h"
#include "Constants.h"
#include "Func.h"

class Road;

class Unit : public cocos2d::Node {
public:
    static Unit *create(TeamColor team);
    ~Unit();

    void startTrek(float delayTime);
    void setRoute(std::vector<Road *> route, bool needSwapFirst = false);
    int getCount() const;
    void setCount(int count);
    const TeamColor &getTeamColor() const;
    void setColor(TeamColor const &color);
    TeamGroup const &getTeamGroup() const;
    void setTeamGroup(TeamGroup const &group);
    Unit *getLastCollidedUnit() const;
    void setLastCollidedUnit(Unit *lastCollidedUnit);
    cocos2d::Sprite *getUnitBody() const;
    bool isShouldBeRemoved() const;
    void setShouldBeRemoved(bool shouldBeRemoved);
    NatureType const &getNatureType() const;
    void setNatureType(NatureType const &natureType);

private:
    bool init(TeamColor color);
    cocos2d::Sequence *addActionsToSequence(std::vector<cocos2d::FiniteTimeAction *> actions, cocos2d::Sequence *sequence);
    std::string determineFilename();

    float speed_;
    TeamColor color_;
    TeamGroup group_;
    std::vector<Road *> route_;
    bool needSwapFirst_;
    int count_;
    cocos2d::Sprite *unitBody_;
    cocos2d::Sprite *shadow_;
    cocos2d::Label *countLabel_;
    Unit *lastCollidedUnit_;
    bool shouldBeRemoved_;
    NatureType natureType_;
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

inline const TeamColor &Unit::getTeamColor() const {
    return color_;
}

inline void Unit::setColor(TeamColor const &color) {
    color_ = color;
}

inline TeamGroup const &Unit::getTeamGroup() const {
    return group_;
}

inline void Unit::setTeamGroup(TeamGroup const &group) {
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

inline NatureType const &Unit::getNatureType() const {
    return natureType_;
}

inline void Unit::setNatureType(NatureType const &natureType) {
    natureType_ = natureType;
}

#endif //__UNIT_H_
