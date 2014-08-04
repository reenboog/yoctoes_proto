#include "PowerTowerView.h"

using namespace cocos2d;

PowerTowerView *PowerTowerView::create() {
    PowerTowerView *tower = new PowerTowerView();
    if (tower->init()) {
        tower->autorelease();
    } else {
        CC_SAFE_DELETE(tower);
    }
    return tower;
}

PowerTowerView::~PowerTowerView() {
}

bool PowerTowerView::init() {
    if (!TowerViewNode::init())
        return false;

    body_ = Sprite::create("empty.png");
    this->addChild(body_);

    cross_ = Sprite::create("cross.png");
    this->addChild(cross_);

    unitsLabel_ = Label::createWithTTF("1", "Chapaza.ttf", 13);
    unitsLabel_->setAnchorPoint({1.0f, 1.0f});
    unitsLabel_->setColor(Color3B::BLACK);
    unitsLabel_->setPosition(16.0f, 16.0f); //fixme
    this->addChild(unitsLabel_);

    return true;
}

void PowerTowerView::applyColor(Color3B color) {
    body_->setColor(color);
}

void PowerTowerView::selectTower() {
    selection_ = Sprite::create("select.png");
    this->addChild(selection_);
}

void PowerTowerView::unselectTower() {
    this->removeChild(selection_, true);
}

void PowerTowerView::showUpgdare() {
    //
}

void PowerTowerView::hideUpgrade() {
    //
}
