#include "Road.h"
#include "Tower.h"

Road::Road(Tower *towerOne, Tower *towerTwo, int distance)
        : towerOne_(towerOne), towerTwo_(towerTwo), distance_(distance) {
    // nothing but the blues
}

bool Road::connects(Tower *towerOne, Tower *towerTwo) {
    return ((towerOne == towerOne_ && towerTwo == towerTwo_) || (towerOne == towerTwo_ && towerTwo == towerOne_));
}

void Road::addRoadPoint(cocos2d::Point point) {
    roadPoints_.push_back(point);
}
