#ifndef __WEAK_TOWER_VIEW_H_
#define __WEAK_TOWER_VIEW_H_

#include "TowerViewNode.h"

class WeakTowerView : public TowerViewNode {
public:
    static WeakTowerView *create();
    ~WeakTowerView();

    cocos2d::Label *getUnitsLabel() const;

    void selectTower();
    void unselectTower();
    void applyColor(cocos2d::Color3B);
private:
    bool init();

    cocos2d::Sprite *body_;
    cocos2d::Sprite *selection_;
    cocos2d::Label *unitsLabel_;
};

inline cocos2d::Label *WeakTowerView::getUnitsLabel() const {
    return unitsLabel_;
}

#endif //__WEAK_TOWER_VIEW_H_
