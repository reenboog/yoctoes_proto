#ifndef __NEUTRAL_TOWER_VIEW_H_
#define __NEUTRAL_TOWER_VIEW_H_

#include "TowerViewNode.h"

class NeutralTowerView : public TowerViewNode {
public:
    static NeutralTowerView *create();
    ~NeutralTowerView();

    cocos2d::Label *getUnitsLabel() const;

    void selectTower();
    void unselectTower();
private:
    bool init();

    cocos2d::Sprite *body_;
    cocos2d::Sprite *selection_;
    cocos2d::Label *unitsLabel_;
};

inline cocos2d::Label *NeutralTowerView::getUnitsLabel() const {
    return unitsLabel_;
}

#endif //__NEUTRAL_TOWER_VIEW_H_
