#ifndef __YELLOW_TOWER_VIEW_H_
#define __YELLOW_TOWER_VIEW_H_

#include "TowerViewNode.h"

class YellowTowerView : public TowerViewNode {
public:
    static YellowTowerView *create();
    ~YellowTowerView();

    cocos2d::Label *getUnitsLabel() const;

    void selectTower();
    void unselectTower();
private:
    bool init();

    cocos2d::Sprite *body_;
    cocos2d::Sprite *selection_;
    cocos2d::Label *unitsLabel_;
};

inline cocos2d::Label *YellowTowerView::getUnitsLabel() const {
    return unitsLabel_;
}

#endif //__YELLOW_TOWER_VIEW_H_