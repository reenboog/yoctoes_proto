#include "GameLayer.h"
#include "Tower.h"
#include "RoadTile.h"

using namespace std;
using namespace cocos2d;

// 0 - empty
// 1 - road
// 2 - tower
const int n = 5;
const int m = 9;
int board_[n][m] = {
        {0, 0,  0,  0,  0,  0,  0,  0, 0},
        {0, 0, -1,  0, -1, -1, -1, -1, 0},
        {0, 0, -1, -1, -1,  0, -1,  0, 0},
        {0, -1,-1,  0,  0, -1, -1,  0, 0},
        {0, 0,  0,  0,  0,  0,  0,  0, 0},
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
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board_[i][j] == 0) {
                Sprite *empty = Sprite::create("empty.png");
                empty->setAnchorPoint({0.0f, 0.0f});
                empty->setPosition({32.0f * j, 32.0f * (n - i)});
                this->addChild(empty);
            } else if (board_[i][j] == -1) {
                RoadTile *roadTile = RoadTile::createWithType(Constants::RoadType::flat);
                roadTile->setPosition({32.0f * j, 32.0f * (n - i)});
                this->addChild(roadTile);

                roadTiles_.push_back(roadTile);
            } else if (board_[i][j] == 2) {
                Tower *tower = Tower::createWithType(Constants::TowerType::common);
                tower->setPosition({32.0f * j, 32.0f * (5 - i)});
                this->addChild(tower);

                towers_.push_back(tower);
            }
        }
    }

    vector<pair<int, int> > oldWave;
    oldWave.push_back(pair<int, int>(3, 1));
    int nstep = 0;
    board_[3][1] = nstep;
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {-1, 0, 1, 0};
    while (oldWave.size() > 0) {
        ++nstep;
        wave.clear();
        for (vector<pair<int, int> >::iterator i = oldWave.begin(); i != oldWave.end(); ++i) {
            for (int d = 0; d < 4; ++d) {
                int nx = i->first + dx[d];
                int ny = i->second + dy[d];
                if (board_[nx][ny] == -1) {
                    wave.push_back(pair<int, int>(nx, ny));
                    board_[nx][ny] = nstep;
                    if (nx == 1 && ny == 7)
                        goto done;
                }
            }
        }
        oldWave = wave;
    }
    done:
    CCLOG("done");
    int x = 1;
    int y = 7;
    wave.clear();
    wave.push_back(pair<int, int>(x, y));
    while (board_[x][y] != 0) {
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (board_[x][y] - 1 == board_[nx][ny]) {
                x = nx;
                y = ny;
                wave.push_back(pair<int, int>(x, y));
                break;
            }
        }
    }

    for (vector<pair<int, int> >::iterator i = wave.begin(); i != wave.end(); ++i) {
        Sprite *point = Sprite::create("unit.png");
        point->setAnchorPoint({0.0f, 0.0f});
        point->setScale(0.6f);
        point->setPosition({32.0f * i->second, 32.0f * (n - i->first)});
        this->addChild(point);
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
