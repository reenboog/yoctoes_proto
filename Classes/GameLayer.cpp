
#include "GameLayer.h"

#define zBack 0

GameLayer::~GameLayer() {
    
}

GameLayer::GameLayer(): Layer() {
    this->back = false;
}

Scene* GameLayer::scene() {
    // random_device rd;
    // srand(rd());
    
    Scene *scene = Scene::create();
    GameLayer *layer = GameLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // set up touches
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

// touches
bool GameLayer::onTouchBegan(Touch* touch, Event  *event) {
    return true;
}

void GameLayer::onTouchEnded(Touch *touch, Event *event) {
}

void GameLayer::onTouchMoved(Touch* touch, Event  *event) {
}

void GameLayer::onTouchCancelled(Touch* touch, Event  *event) {
}