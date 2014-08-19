#include "PitTowerView.h"
#include "Func.h"

using namespace cocos2d;

PitTowerView *PitTowerView::create() {
    PitTowerView *tower = new PitTowerView();
    if (tower->init()) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

PitTowerView::~PitTowerView() {

}

bool PitTowerView::init() {
    if (!TowerViewNode::init())
        return false;

    body_ = Sprite::create("pit_tower.png");
    this->addChild(body_);

    unitsLabel_ = Label::createWithTTF("1", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(16.0f, 16.0f); //fixme
    this->addChild(unitsLabel_);

    return true;
}

void PitTowerView::applyColor(Color3B color) {
    body_->setColor(color);
}
