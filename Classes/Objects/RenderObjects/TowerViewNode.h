#ifndef __TOWER_VIEW_NODE_H_
#define __TOWER_VIEW_NODE_H_

#include "cocos2d.h"

class TowerViewNode : public cocos2d::Node {
public:
    bool init();

    virtual cocos2d::Label *getUnitsLabel() const;
    virtual void selectTower();
    virtual void unselectTower();
    virtual void applyColor(cocos2d::Color3B);
    virtual void showUpgdare();
    virtual void hideUpgrade();
};

#endif //__TOWER_VIEW_NODE_H_
