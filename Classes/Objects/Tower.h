#ifndef __TOWER_H_
#define __TOWER_H_

#include "CCLabel.h"
#include "CCSprite.h"
#include "Constants.h"

class Unit;

//
// WinLoseProtocol
//
class WinLoseProtocol {
public:
    virtual void checkWin() = 0;
    virtual void checkLose() = 0;

    virtual ~WinLoseProtocol() = 0;
};

//
// Tower
//
class Tower : public cocos2d::Sprite {
public:
    static Tower *createWithType(Constants::TeamColor color);
    ~Tower();

    void update(float dt);

    char getID() const;
    void setID(char id);
    const Constants::TeamColor &getTeamColor() const;
    void setSelected(bool selected);
    const Constants::TeamGroup &getTeamGroup() const;
//    void setTeamGroup(Constants::TeamGroup const &group);
    float getActionCooldown() const;
    void setActionCooldown(float actionCooldown);
    void addEvent(Constants::Events event);

    void applyUnit(Unit *unit);
    void checkForApplying(Unit *unit);
    int takeHalfUnits();
    void changeToTeam(Constants::TeamColor TeamColor);

    CC_SYNTHESIZE(WinLoseProtocol*, delegate_, Delegate)

private:
    bool initWithType(Constants::TeamColor color);
    void updateUnitsLabel();
    std::string determineFilename();
    void checkWin();

    int unitsCount_;
    char id_;
    Constants::TeamColor color_;
    Constants::TeamGroup group_;
    float generateUnitCooldown_;
    float actionCooldown_;
    float timeAfterLastUnit_;
    bool selected_;
    bool selectionAnimated_;
    cocos2d::Label *unitsLabel_;
    cocos2d::Sprite *selection_;
    Unit *lastAppliedUnit_;
    std::set<Constants::Events> events_;

};

inline char Tower::getID() const {
    return id_;
}

inline void Tower::setID(char id) {
    id_ = id;
}

inline const Constants::TeamColor &Tower::getTeamColor() const {
    return color_;
}

inline void Tower::setSelected(bool selected) {
    selected_ = selected;
}

inline Constants::TeamGroup const &Tower::getTeamGroup() const {
    return group_;
}

//inline void Tower::setTeamGroup(Constants::TeamGroup const &group) {
//    group_ = group;
//}

inline float Tower::getActionCooldown() const {
    return actionCooldown_;
}

inline void Tower::setActionCooldown(float actionCooldown) {
    actionCooldown_ = actionCooldown;
}

#endif //__TOWER_H_
