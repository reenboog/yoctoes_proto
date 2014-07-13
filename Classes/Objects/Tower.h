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
    bool isSelected() const;
    void setSelected(bool selected);

    void applyUnit(Unit *unit);
    void checkForApplying(Unit *unit);
    int takeHalfUnits();

private:
    bool initWithType(Constants::TowerType type);
    void updadeUnitsLabel();

    int unitsCount_;
    char id_;
    Constants::TeamType team_;
    Constants::TowerType towerType_;
    float generateUnitTime_;
    float timeAfterLastUnit_;
    bool selected_;
    bool selectionAnimated_;
    cocos2d::Label *unitsLabel_;
    cocos2d::Sprite *selection_;
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

inline bool Tower::isSelected() const {
    return selected_;
}

inline void Tower::setSelected(bool selected) {
    selected_ = selected;
}

#endif //__TOWER_H_
