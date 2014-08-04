#ifndef __TOWERS_MANAGER_H_
#define __TOWERS_MANAGER_H_

#include <iosfwd>
#include "Constants.h"
#include "Tower.h"

class TowersManager : public UpdateProtocol {
public:
    static TowersManager *sharedInstance();

    Tower *createTowerWithParams(TowerType towerType, TeamColor teamColor, NatureType natureType, int level);

    virtual void changeTeam(Tower *tower, TeamColor color);
    virtual void upgradeTower(Tower *tower);

    void addPoweredTower(Tower *, Tower *);
    void removeEffectSrc(Tower *);
    void removeEffectDst(Tower *);
private:
    static TowersManager *sharedInstance_;

    TowersManager();
    ~TowersManager();

    cocos2d::Color3B colorForTeam(TeamColor);
    TeamGroup groupForTeam(TeamColor);

    std::vector<std::pair<Tower *, Tower*>> poweredTowers_;
    void checkPowerTower(Tower *);
};

#endif //__TOWERS_MANAGER_H_
