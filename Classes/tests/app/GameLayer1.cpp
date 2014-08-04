#include "GameLayer1.h"
#include "Tower.h"

using namespace cocos2d;

GameLayer1::~GameLayer1() {
}

GameLayer1::GameLayer1() : Layer() {
    this->back_ = NULL;
}

Scene *GameLayer1::scene() {
    Scene *scene = Scene::create();

    GameLayer1 *layer = GameLayer1::create();

    scene->addChild(layer);

    return scene;
}

bool GameLayer1::init() {
    if (!Layer::init()) {
        return false;
    }

    CCLOG("THIS IS A TEST.");

    return true;
}
