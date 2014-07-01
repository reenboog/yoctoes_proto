#ifndef __TOWER_H_
#define __TOWER_H_

#include "CCSprite.h"
#include "Constants.h"

class Tower : public cocos2d::Sprite {
public:
    static Tower *createWithType(Constants::TowerType type);
    ~Tower();

    void updateToType(Constants::TowerType type);

private:
    bool initWithType(Constants::TowerType type);

    Constants::TowerType type_;
    Constants::TowerElement element_;
};

#endif //__TOWER_H_
