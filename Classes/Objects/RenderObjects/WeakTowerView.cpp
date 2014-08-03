#include "WeakTowerView.h"

using namespace cocos2d;

WeakTowerView *WeakTowerView::create() {
    WeakTowerView *tower = new WeakTowerView();
    if (tower->init()) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

WeakTowerView::~WeakTowerView() {
}

bool WeakTowerView::init() {
    if (!TowerViewNode::init())
        return false;

    body_ = Sprite::create("weak_tower.png");
    this->addChild(body_);

    unitsLabel_ = Label::createWithTTF("1", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(16.0f, 16.0f); //fixme
    this->addChild(unitsLabel_);


    return true;
}

void WeakTowerView::applyColor(Color3B color) {
    body_->setColor(color);
}

void WeakTowerView::selectTower() {
    selection_ = Sprite::create("select.png");
    this->addChild(selection_);
}

void WeakTowerView::unselectTower() {
    this->removeChild(selection_, true);
}
