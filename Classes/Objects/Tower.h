#ifndef __TOWER_H_
#define __TOWER_H_

#include "CCSprite.h"
#include "Constants.h"

class Unit;

class Tower : public cocos2d::Sprite {
public:
    static Tower *createWithType(Constants::TowerType type);
    ~Tower();

    char getID() const;
    void setID(char id);
    const Constants::TeamType &getTeam() const;
    bool applyUnit(Unit *unit);

private:
    bool initWithType(Constants::TowerType type);

    char id_;
    Constants::TeamType team_;
    Constants::TowerType towerType_;
};

inline char Tower::getID() const {
    return id_;
}

inline void Tower::setID(char id) {
    id_ = id;
}

inline const Constants::TeamType &Tower::getTeam() const {
    return team_;
}

#endif //__TOWER_H_
