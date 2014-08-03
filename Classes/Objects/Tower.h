#ifndef __TOWER_H_
#define __TOWER_H_

#include "cocos2d.h"
#include "Constants.h"
#include "TowerViewNode.h"

class Unit;
class Tower;
class TowerViewNode;

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
// UpdateProtocol
//
class UpdateProtocol {
public:
    virtual void upgradeTower(Tower *) = 0;
    virtual void changeTeam(Tower *, TeamColor) = 0;
};

//
// Tower
//
class Tower : public cocos2d::Node {
public:
    static Tower *createWithType(TeamColor color);
    ~Tower();

    void update(float dt);

    char getID() const;
    void setID(char id);
    const TeamColor &getTeamColor() const;
    void setTeamColor(TeamColor const &color);
    void setSelected(bool selected);
    const TeamGroup &getTeamGroup() const;
    void setGroup(TeamGroup const &group);
    float getActionCooldown() const;
    void setActionCooldown(float actionCooldown);
    NatureType const &getNatureType() const;
    TowerViewNode *getTowerView() const;
    void setTowerView(TowerViewNode *towerView);
    void setGenerateUnitCooldown(float generateUnitCooldown);
    int getCurrentLevel() const;
    void setCurrentLevel(int currentLevel);
    void setParams(TowerParams const &params);

    void applyUnit(Unit *unit);
    void checkForApplying(Unit *unit);
    int takeHalfUnits();
    void updateTowerView(TowerViewNode *newView);

    CC_SYNTHESIZE(WinLoseProtocol*, delegate_, Delegate)
    CC_SYNTHESIZE(UpdateProtocol*, updateDelegate_, UpdateDelegate);

private:
    bool initWithType(TeamColor color);
    void updateUnitsLabel();
    void checkWin();
    void changeTeam(Tower *, TeamColor);
    void upgradeTower(Ref* pSender);

    int unitsCount_;
    char id_;
    TeamColor color_;
    TeamGroup group_;
    float generateUnitCooldown_;
    float actionCooldown_;
    float timeAfterLastUnit_;
    bool selected_;
    bool selectionAnimated_;
    Unit *lastAppliedUnit_;
    NatureType natureType_;
    TowerViewNode *towerView_;
    int currentLevel_;

    bool readyForUpdate_;
    bool updateButtonShown_;
    cocos2d::Menu *upgradeMenu_;
    TowerParams params_;
    int unitsLimit_;
};

inline char Tower::getID() const {
    return id_;
}

inline void Tower::setID(char id) {
    id_ = id;
}

inline const TeamColor &Tower::getTeamColor() const {
    return color_;
}

inline void Tower::setTeamColor(TeamColor const &color) {
    color_ = color;
}

inline void Tower::setSelected(bool selected) {
    selected_ = selected;
}

inline TeamGroup const &Tower::getTeamGroup() const {
    return group_;
}

inline void Tower::setGroup(TeamGroup const &group) {
    group_ = group;
}

inline float Tower::getActionCooldown() const {
    return actionCooldown_;
}

inline void Tower::setActionCooldown(float actionCooldown) {
    actionCooldown_ = actionCooldown;
}

inline NatureType const &Tower::getNatureType() const {
    return natureType_;
}

inline TowerViewNode *Tower::getTowerView() const {
    return towerView_;
}

inline void Tower::setTowerView(TowerViewNode *towerView) {
    towerView_ = towerView;
}

inline void Tower::setGenerateUnitCooldown(float generateUnitCooldown) {
    generateUnitCooldown_ = generateUnitCooldown;
}

inline int Tower::getCurrentLevel() const {
    return currentLevel_;
}

inline void Tower::setCurrentLevel(int currentLevel) {
    currentLevel_ = currentLevel;
}

inline void Tower::setParams(TowerParams const &params) {
    params_ = params;
    unitsLimit_ = params.unitCap;
}

#endif //__TOWER_H_
