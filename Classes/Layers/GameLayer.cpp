#include "GameLayer.h"
#include "Tower.h"

using namespace cocos2d;

// 0 - empty
// 1 - road
// 2 - tower

const int board_[5][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 2, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 1, 2},
        {0, 2, 1, 0, 0, 0, 0, 0, 0},
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
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board_[i][j] == 0) {
                Sprite *empty = Sprite::create("empty.png");
                empty->setAnchorPoint({0.0f, 0.0f});
                empty->setPosition({32.0f * j, 32.0f * (5 - i)});
                this->addChild(empty);
            } else if (board_[i][j] == 1) {
                Sprite *road = Sprite::create("road.png");
                road->setAnchorPoint({0.0f, 0.0f});
                road->setPosition({32.0f * j, 32.0f * (5 - i)});
                this->addChild(road);
            } else if (board_[i][j] == 2) {
                Tower *tower = Tower::createWithType(Constants::TowerType::common);
                tower->setPosition({32.0f * j, 32.0f * (5 - i)});
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