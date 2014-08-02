#ifndef __TOWER_VIEW_NODE_H_
#define __TOWER_VIEW_NODE_H_

#include "cocos2d.h"

class TowerViewNode : public cocos2d::Node {
public:
    bool init();

    virtual cocos2d::Label *getUnitsLabel() const;
    virtual void selectTower();
    virtual void unselectTower();
};

#endif //__TOWER_VIEW_NODE_H_
