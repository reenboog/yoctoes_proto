#include "RoadTile.h"

RoadTile *RoadTile::createWithType(Constants::RoadType type) {
    RoadTile *roadTile = new RoadTile();
    if (roadTile->initWithType(type)) {
        roadTile->autorelease();
    } else {
        CC_SAFE_DELETE(roadTile);
    }
    return roadTile;
}

bool RoadTile::initWithType(Constants::RoadType type) {
    //TODO: fill filename here
    if (!Sprite::initWithFile("road.png"))
        return false;

    this->setAnchorPoint({0.0f, 0.0f});

    type_ = type;
    tileType_ = Constants::TileType::road;

    return true;
}
