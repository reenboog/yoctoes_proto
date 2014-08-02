#ifndef __GREEN_TOWER_VIEW_H_
#define __GREEN_TOWER_VIEW_H_

#include "TowerViewNode.h"

class GreenTowerView : public TowerViewNode {
public:
    static GreenTowerView *create();
    ~GreenTowerView();

    cocos2d::Label *getUnitsLabel() const;

    void selectTower();
    void unselectTower();
private:
    bool init();

    cocos2d::Sprite *body_;
    cocos2d::Sprite *selection_;
    cocos2d::Label *unitsLabel_;
};

inline cocos2d::Label *GreenTowerView::getUnitsLabel() const {
    return unitsLabel_;
}

#endif //__GREEN_TOWER_VIEW_H_
