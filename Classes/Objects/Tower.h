#ifndef __TOWER_H_
#define __TOWER_H_

#include "CCLabel.h"
#include "CCSprite.h"
#include "Constants.h"

class Unit;

class Tower : public cocos2d::Sprite {
public:
    static Tower *createWithType(Constants::TowerType type);
    ~Tower();

    void update(float dt);

    char getID() const;
    void setID(char id);
    const Constants::TeamType &getTeam() const;
    int getUnitsCount() const;

    void applyUnit(Unit *unit);
    void checkForApplying(Unit *unit);
    int takeHalfUnits();

private:
    bool initWithType(Constants::TowerType type);
    void updadeUnitsLabel();

    char id_;
    Constants::TeamType team_;
    Constants::TowerType towerType_;
    float generateUnitTime_;
    float timeAfterLastUnit_;
    cocos2d::Label *unitsLabel_;
    int unitsCount_;
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

inline int Tower::getUnitsCount() const {
    return unitsCount_;
}

#endif //__TOWER_H_
