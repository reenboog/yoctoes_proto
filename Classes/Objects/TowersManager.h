#ifndef __TOWERS_MANAGER_H_
#define __TOWERS_MANAGER_H_

#include <iosfwd>
#include "Constants.h"
#include "Tower.h"

class TowersManager : public UpdateProtocol {
public:
    static TowersManager *sharedInstance();

    Tower *createTowerWithParams(TeamColor, NatureType, int);

    virtual void changeTeam(Tower *tower, TeamColor color);
private:
    static TowersManager *sharedInstance_;

    TowersManager();
    ~TowersManager();

    TowerViewNode *getTowerViewNode(TeamColor);
};

#endif //__TOWERS_MANAGER_H_
