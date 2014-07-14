#ifndef __UNIT_H_
#define __UNIT_H_

#include "cocos2d.h"
#include "Constants.h"

class Road;

class Unit : public cocos2d::Node {
public:
    static Unit *create(Constants::TeamType team);
    ~Unit();

    void startTrek();
    void setRoute(std::vector<Road *> route, bool needSwapFirst = false);
    int getCount() const;
    void setCount(int count);
    const Constants::TeamType &getTeam() const;
    void setTeam(Constants::TeamType const &team);

private:
    bool init(Constants::TeamType team);
    cocos2d::Sequence *addActionsToSequence(std::vector<cocos2d::FiniteTimeAction *> actions, cocos2d::Sequence *sequence);
    std::string determineFilename();

    float speed_;
    Constants::TeamType team_;
    std::vector<Road *> route_;
    bool needSwapFirst_;
    int count_;
    cocos2d::Sprite *unitBody_;
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
}

inline const Constants::TeamType &Unit::getTeam() const {
    return team_;
}

inline void Unit::setTeam(Constants::TeamType const &team) {
    team_ = team;
}

#endif //__UNIT_H_
