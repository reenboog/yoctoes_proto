#include "YellowTowerView.h"

using namespace cocos2d;

YellowTowerView *YellowTowerView::create() {
    YellowTowerView *tower = new YellowTowerView();
    if (tower->init()) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

YellowTowerView::~YellowTowerView() {
}

bool YellowTowerView::init() {
    if (!TowerViewNode::init())
        return false;

    body_ = Sprite::create("yellow_tower.png");
    this->addChild(body_);

    unitsLabel_ = Label::createWithTTF("1", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(16.0f, 16.0f); //fixme
    this->addChild(unitsLabel_);

    return true;
}

void YellowTowerView::selectTower() {
    selection_ = Sprite::create("select.png");
    this->addChild(selection_);
}

void YellowTowerView::unselectTower() {
    this->removeChild(selection_, true);
}