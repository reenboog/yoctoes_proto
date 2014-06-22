
#include "GameLayer.h"

#define zBack 0

GameLayer::~GameLayer() {
    
}

GameLayer::GameLayer(): Layer() {
    this->back = NULL;
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
    
    CCLOG("THIS IS A TEST.");
    
    return true;
}