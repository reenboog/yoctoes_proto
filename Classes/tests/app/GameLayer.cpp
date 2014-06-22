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

    CCLOG("THIS IS A TEST.");

    return true;
}