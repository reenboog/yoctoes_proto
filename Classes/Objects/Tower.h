#ifndef __TOWER_H_
#define __TOWER_H_

#include "CCSprite.h"
#include "Constants.h"

class Tower : public cocos2d::Sprite {
public:
    static Tower *createWithType(Constants::TowerType type);
    ~Tower();

    void updateToType(Constants::TowerType type);
    inline int getID() const;
    inline void setID(int id);
    int getIndex() const;
    void setIndex(int index);

private:
    bool initWithType(Constants::TowerType type);

    Constants::TowerType towertype_;
    Constants::TowerElement element_;
    Constants::TileType tileType_;
    int id_;
    int index_;
};

// id in format: (100 + i) * 100 + 200 + j; example: 101213
inline int Tower::getID() const {
    return id_;
}

inline void Tower::setID(int id) {
    id_ = id;
}

inline int Tower::getIndex() const {
    return index_;
}

inline void Tower::setIndex(int index) {
    index_ = index;
}

#endif //__TOWER_H_
