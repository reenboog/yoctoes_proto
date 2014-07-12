#ifndef __ROAD_H_
#define __ROAD_H_

#include <deque>
#include "cocos2d.h"

class Tower;

class Road {
public:
    Road(Tower *towerOne, Tower *towerTwo, int distance);
    ~Road();

    bool connects(Tower *towerOne, Tower *towerTwo);

    Tower *getTowerOne() const;
    Tower *getTowerTwo() const;
    int getDistance() const;

    void addRoadPoint(cocos2d::Point point);
    std::vector<cocos2d::Point> getRoadPoints() const;

private:
    Tower *towerOne_;
    Tower *towerTwo_;
    int distance_;

    std::vector<cocos2d::Point> roadPoints_;
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

inline std::vector<cocos2d::Point> Road::getRoadPoints() const {
    return roadPoints_;
}

#endif //__ROAD_H_
