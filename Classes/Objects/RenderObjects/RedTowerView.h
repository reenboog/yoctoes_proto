#ifndef __RED_TOWER_VIEW_H_
#define __RED_TOWER_VIEW_H_

#include "TowerViewNode.h"

class RedTowerView : public TowerViewNode {
public:
    static RedTowerView *create();
    ~RedTowerView();

    cocos2d::Label *getUnitsLabel() const;

    void selectTower();
    void unselectTower();
private:
    bool init();

    cocos2d::Sprite *body_;
    cocos2d::Sprite *selection_;
    cocos2d::Label *unitsLabel_;
};

inline cocos2d::Label *RedTowerView::getUnitsLabel() const {
    return unitsLabel_;
}

#endif //__RED_TOWER_VIEW_H_
