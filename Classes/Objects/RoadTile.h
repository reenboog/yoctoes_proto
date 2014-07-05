#ifndef __ROAD_TILE_H_
#define __ROAD_TILE_H_

#include "cocos2d.h"
#include "Constants.h"

class RoadTile : public cocos2d::Sprite {
public:
    static RoadTile *createWithType(Constants::RoadType type);

private:
    bool initWithType(Constants::RoadType type);

    Constants::RoadType type_;
    Constants::TileType tileType_;
};


#endif //__ROAD_TILE_H_
