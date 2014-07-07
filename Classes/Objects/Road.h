#ifndef __ROAD_H_
#define __ROAD_H_

#include <deque>
#import <CoreGraphics/CoreGraphics.h>

class Tower;

class Road {
public:
    Road(Tower *towerOne, Tower *towerTwo, int distance);

    bool connects(Tower *towerOne, Tower *towerTwo);

    Tower *getTowerOne() const;
    Tower *getTowerTwo() const;
    int getDistance() const;

    void addRoadPoint(CGPoint point);
    std::deque<CGPoint> const &getRoadPoints() const;

private:
    Tower *towerOne_;
    Tower *towerTwo_;
    int distance_;

    std::deque<CGPoint> roadPoints_;
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

inline std::deque<CGPoint> const &Road::getRoadPoints() const {
    return roadPoints_;
}

#endif //__ROAD_H_
