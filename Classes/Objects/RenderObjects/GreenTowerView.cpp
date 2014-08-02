#include "GreenTowerView.h"

using namespace cocos2d;

GreenTowerView *GreenTowerView::create() {
    GreenTowerView *tower = new GreenTowerView();
    if (tower->init()) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

GreenTowerView::~GreenTowerView() {
}

bool GreenTowerView::init() {
    if (!TowerViewNode::init())
        return false;

    body_ = Sprite::create("green_tower.png");
    this->addChild(body_);

    unitsLabel_ = Label::createWithTTF("1", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(16.0f, 16.0f); //fixme
    this->addChild(unitsLabel_);

    return true;
}

void GreenTowerView::selectTower() {
    selection_ = Sprite::create("select.png");
    this->addChild(selection_);
}

void GreenTowerView::unselectTower() {
    this->removeChild(selection_, true);
}

