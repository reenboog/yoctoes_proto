#ifndef __POWER_TOWER_VIEW_H_
#define __POWER_TOWER_VIEW_H_

#include "TowerViewNode.h"

class PowerTowerView : public TowerViewNode {
public:
    static PowerTowerView *create();
    static cocos2d::Sprite *getRenderedImage();
    ~PowerTowerView();

    cocos2d::Label *getUnitsLabel() const;

    void selectTower();
    void unselectTower();
    void applyColor(cocos2d::Color3B);
    void showUpgdare();
    void hideUpgrade();
private:
    bool init();

    cocos2d::Sprite *body_;
    cocos2d::Sprite *cross_;
    cocos2d::Sprite *selection_;
    cocos2d::Label *unitsLabel_;
};

inline cocos2d::Label *PowerTowerView::getUnitsLabel() const {
    return unitsLabel_;
}

#endif //__POWER_TOWER_VIEW_H_
