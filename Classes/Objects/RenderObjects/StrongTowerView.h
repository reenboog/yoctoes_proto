#ifndef __STRONG_TOWER_VIEW_H_
#define __STRONG_TOWER_VIEW_H_

#include "TowerViewNode.h"

class StrongTowerView  : public TowerViewNode {
public:
    static StrongTowerView *create();
    ~StrongTowerView();

    cocos2d::Label *getUnitsLabel() const;

    void selectTower();
    void unselectTower();
    void applyColor(cocos2d::Color3B);
    void showUpgdare();
    void hideUpgrade();
private:
    bool init();

    cocos2d::Sprite *body_;
    cocos2d::Sprite *selection_;
    cocos2d::Label *unitsLabel_;
};

inline cocos2d::Label *StrongTowerView::getUnitsLabel() const {
    return unitsLabel_;
}

#endif //__STRONG_TOWER_VIEW_H_
