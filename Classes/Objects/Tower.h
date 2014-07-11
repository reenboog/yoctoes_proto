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
    bool applyUnit(Unit *unit);

private:
    bool initWithType(Constants::TowerType type);

    Constants::TowerType towertype_;
    char id_;
};

inline char Tower::getID() const {
    return id_;
}

inline void Tower::setID(char id) {
    id_ = id;
}

#endif //__TOWER_H_
