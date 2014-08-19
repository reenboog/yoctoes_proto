#ifndef __PIT_TOWER_VIEW_H_
#define __PIT_TOWER_VIEW_H_

#include "TowerViewNode.h"

class PitTowerView : public TowerViewNode {
public:
    static PitTowerView *create();
    ~PitTowerView();

    cocos2d::Label *getUnitsLabel() const;

    void applyColor(cocos2d::Color3B);
private:
    bool init();

    cocos2d::Sprite *body_;
    cocos2d::Label *unitsLabel_;
};

inline cocos2d::Label *PitTowerView::getUnitsLabel() const {
    return unitsLabel_;
}

#endif //__PIT_TOWER_VIEW_H_
