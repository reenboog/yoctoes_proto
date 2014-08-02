#include "RedTowerView.h"

using namespace cocos2d;

RedTowerView *RedTowerView::create() {
    RedTowerView *tower = new RedTowerView();
    if (tower->init()) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

RedTowerView::~RedTowerView() {
}

bool RedTowerView::init() {
    if (!TowerViewNode::init())
        return false;

    body_ = Sprite::create("red_tower.png");
    this->addChild(body_);

    unitsLabel_ = Label::createWithTTF("1", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(16.0f, 16.0f); //fixme
    this->addChild(unitsLabel_);

    return true;
}

void RedTowerView::selectTower() {
    selection_ = Sprite::create("select.png");
    this->addChild(selection_);
}

void RedTowerView::unselectTower() {
    this->removeChild(selection_, true);
}