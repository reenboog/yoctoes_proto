#ifndef __TOWER_H_
#define __TOWER_H_

#include "CCSprite.h"
#include "Constants.h"

class Tower : public cocos2d::Sprite {
public:
    static Tower *createWithType(Constants::TowerType type);
    ~Tower();

    char getID() const;
    void setID(char id);
    Tower *getPrevious() const;
    void setPrevious(Tower *previous);
    int getDistanceFromStart() const;
    void setDistanceFromStart(int distanceFromStart);

private:
    bool initWithType(Constants::TowerType type);

    Constants::TowerType towertype_;
    char id_;
    Tower *previous_;
    int distanceFromStart_;
};

inline char Tower::getID() const {
    return id_;
}

inline void Tower::setID(char id) {
    id_ = id;
}

inline Tower *Tower::getPrevious() const {
    return previous_;
}

inline void Tower::setPrevious(Tower *previous) {
    previous_ = previous;
}

inline int Tower::getDistanceFromStart() const {
    return distanceFromStart_;
}

inline void Tower::setDistanceFromStart(int distanceFromStart) {
    distanceFromStart_ = distanceFromStart;
}

#endif //__TOWER_H_
