#include "Tower.h"

#ifndef __ROAD_H_
#define __ROAD_H_

class Tower;

class Road {
public:
    Road(Tower *towerOne, Tower *towerTwo, int distance);

    bool connects(Tower *towerOne, Tower *towerTwo);

    Tower *getTowerOne() const;
    Tower *getTowerTwo() const;
    int getDistance() const;

private:
    Tower *towerOne_;
    Tower *towerTwo_;
    int distance_;
};

inline Tower *Road::getTowerOne() const {
    return towerOne_;
}

inline Tower *Road::getTowerTwo() const {
    return towerTwo_;
}

inline int Road::getDistance() const {
    return distance_;
}

#endif //__ROAD_H_
