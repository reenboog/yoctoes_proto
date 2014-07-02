#include "GameLayer.h"
#include "Tower.h"

using namespace cocos2d;

const int board_[4][4] = {
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {1, 0, 0, 0}
};

GameLayer::~GameLayer() {
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

    this->createBoard();

    return true;
}

#pragma mark - map

void GameLayer::createBoard() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board_[i][j] > 0) {
                Tower *tower = Tower::createWithType(Constants::TowerType::common);
                tower->setPosition({50.0f * j, 50.0f * (3 - i)});
                this->addChild(tower);

                towers_.push_back(tower);
            }
        }
    }
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