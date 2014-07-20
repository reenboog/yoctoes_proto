#include "GameState.h"
#include "GameLayer.h"

using namespace cocos2d;

GameState *GameState::sharedInstance_ = nullptr;

GameState *GameState::sharedInstance() {
    if (sharedInstance_ == nullptr) {
        sharedInstance_ = new GameState();
    }

    return sharedInstance_;
}

GameState::GameState() {
}

GameState::~GameState() {
}

#pragma mark -

void GameState::startScene(cocos2d::Scene *scene) {
    if(directorRunned_) {
        Director::getInstance()->replaceScene(scene);
    } else {
        Director::getInstance()->runWithScene(scene);
        directorRunned_ = true;
    }
}

void GameState::startGameLayer() {
    currentState_ = State::gameLayer;
    Scene *scene = GameLayer::scene();
    if(scene) {
        startScene(scene);
    }
}
