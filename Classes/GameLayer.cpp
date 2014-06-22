#include "GameLayer.h"

using namespace cocos2d;

GameLayer::~GameLayer() {
}

GameLayer::GameLayer() : Layer() {
    this->back_ = NULL;
}

Scene *GameLayer::scene() {
    Scene *scene = Scene::create();

    GameLayer *layer = GameLayer::create();

    scene->addChild(layer);

    return scene;
}

bool GameLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

#pragma mark - touches

bool GameLayer::onTouchBegan(Touch *touch, Event *event) {
    return true;
}

void GameLayer::onTouchEnded(Touch *touch, Event *event) {
}

void GameLayer::onTouchMoved(Touch *touch, Event *event) {
}

void GameLayer::onTouchCancelled(Touch *touch, Event *event) {
}