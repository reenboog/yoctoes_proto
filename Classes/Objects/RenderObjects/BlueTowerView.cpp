#include "BlueTowerView.h"

using namespace cocos2d;

BlueTowerView *BlueTowerView::create() {
    BlueTowerView *tower = new BlueTowerView();
    if (tower->init()) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

BlueTowerView::~BlueTowerView() {
}

bool BlueTowerView::init() {
    if (!TowerViewNode::init())
        return false;

    body_ = Sprite::create("blue_tower.png");
    this->addChild(body_);

    unitsLabel_ = Label::createWithTTF("1", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(16.0f, 16.0f); //fixme
    this->addChild(unitsLabel_);


    return true;
}

void BlueTowerView::selectTower() {
    selection_ = Sprite::create("select.png");
    this->addChild(selection_);
}

void BlueTowerView::unselectTower() {
    this->removeChild(selection_, true);
}
