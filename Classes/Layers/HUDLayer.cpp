#include "HUDLayer.h"
#include "GameState.h"

using namespace cocos2d;

HUDLayer *HUDLayer::create() {
    HUDLayer *hud = new HUDLayer();
    if (hud && hud->init()) {
        hud->autorelease();
    } else {
        delete hud;
        hud = NULL;
    }

    return hud;
}

HUDLayer::~HUDLayer() {

}

bool HUDLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    MenuItemSprite *restart = MenuItemSprite::create(Sprite::create("restart.png"),
            Sprite::create("restart.png"),
            this,
            menu_selector(HUDLayer::restartCallback));
    restart->setPosition(210, 160);
    
    menu_ = Menu::create(restart, NULL);
    this->addChild(menu_);

    return true;
}

void HUDLayer::restartCallback(Ref* pSender) {
    GameState::sharedInstance()->startGameLayer();
}
