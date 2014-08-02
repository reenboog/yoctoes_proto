#ifndef __BLUE_TOWER_VIEW_H_
#define __BLUE_TOWER_VIEW_H_

#include "TowerViewNode.h"

class BlueTowerView : public TowerViewNode {
public:
    static BlueTowerView *create();
    ~BlueTowerView();

    cocos2d::Label *getUnitsLabel() const;

    void selectTower();
    void unselectTower();
private:
    bool init();

    cocos2d::Sprite *body_;
    cocos2d::Sprite *selection_;
    cocos2d::Label *unitsLabel_;
};

inline cocos2d::Label *BlueTowerView::getUnitsLabel() const {
    return unitsLabel_;
}

#endif //__BLUE_TOWER_VIEW_H_
