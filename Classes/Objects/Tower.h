#ifndef __TOWER_H_
#define __TOWER_H_

#include "CCLabel.h"
#include "CCSprite.h"
#include "Constants.h"

class Unit;

class Tower : public cocos2d::Sprite {
public:
    static Tower *createWithType(Constants::TeamType team);
    ~Tower();

    void update(float dt);

    char getID() const;
    void setID(char id);
    const Constants::TeamType &getTeam() const;
    void setSelected(bool selected);

    void applyUnit(Unit *unit);
    void checkForApplying(Unit *unit);
    int takeHalfUnits();
    void changeToTeam(Constants::TeamType newTeam);

private:
    bool initWithType(Constants::TeamType team);
    void updateUnitsLabel();
    std::string determineFilename();

    int unitsCount_;
    char id_;
    Constants::TeamType team_;
    float generateUnitTime_;
    float timeAfterLastUnit_;
    bool selected_;
    bool selectionAnimated_;
    cocos2d::Label *unitsLabel_;
    cocos2d::Sprite *selection_;
    bool alreadyApplied_;
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

inline void Tower::setSelected(bool selected) {
    selected_ = selected;
}

#endif //__TOWER_H_
