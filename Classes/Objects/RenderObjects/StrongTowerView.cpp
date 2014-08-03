#include "StrongTowerView.h"

using namespace cocos2d;

StrongTowerView *StrongTowerView::create() {
    StrongTowerView *tower = new StrongTowerView();
    if (tower->init()) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

StrongTowerView::~StrongTowerView() {
}

bool StrongTowerView::init() {
    if (!TowerViewNode::init())
        return false;

    body_ = Sprite::create("strong_tower.png");
    this->addChild(body_);

    unitsLabel_ = Label::createWithTTF("1", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(16.0f, 16.0f); //fixme
    this->addChild(unitsLabel_);


    return true;
}

void StrongTowerView::applyColor(Color3B color) {
    body_->setColor(color);
}

void StrongTowerView::selectTower() {
    selection_ = Sprite::create("select.png");
    this->addChild(selection_);
}

void StrongTowerView::unselectTower() {
    this->removeChild(selection_, true);
}

void StrongTowerView::showUpgdare() {
    //
}

void StrongTowerView::hideUpgrade() {
    //
}
