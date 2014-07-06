#include "GameLayer.h"
#include "Tower.h"

using namespace std;
using namespace cocos2d;

static inline int generateID(int i, int j) {
    return (100 + i) * 100 + 200 + j;
}

const int n = 9;
const int testMap_[n][n] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _},*/
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _},*/
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _},*/
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _},*/
        {0, 2, 1, 0, 0, 0, 2, 0, 0},/*{_, 1, _, _, _, _, 3, _, _},*/
        {0, 0, 1, 0, 0, 0, 1, 0, 0},/*{_, _, _, _, _, _, _, _, _},*/
        {0, 0, 1, 1, 2, 1, 1, 0, 0},/*{_, _, _, _, 2, _, _, _, _},*/
        {0, 2, 1, 0, 0, 0, 0, 0, 0},/*{_, 0, _, _, _, _, _, _, _},*/
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _},*/
};

GameLayer::~GameLayer() {
    for (int i = 0; i < towersCount_; ++i)
        delete[] graph_[i];
    delete[] graph_;
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

    this->showBoard();

    this->createGraphAndRoards();
    this->dijkstra(0);

    return true;
}

#pragma mark - map

void GameLayer::showBoard() {
    float tileWidth = 38.0f;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (testMap_[i][j] == 0) {

                Sprite *empty = Sprite::create("empty.png");
                empty->setPosition({tileWidth * j + tileWidth / 2, tileWidth * (n - i)});
                this->addChild(empty);

            } else if (testMap_[i][j] == 1) {

                Sprite *road = Sprite::create("road.png");
                road->setPosition({tileWidth * j + tileWidth / 2, tileWidth * (n - i)});
                this->addChild(road);

            } else if (testMap_[i][j] == 2) {

                Tower *tower = Tower::createWithType(Constants::TowerType::common);
                tower->setPosition({tileWidth * j + tileWidth / 2, tileWidth * (n - i)});
                this->addChild(tower);

                tower->setID(generateID(i, j));
                towers_.push_back(tower);

                if (i == 7 && j == 1) {
                    tower->setIndex(0);
                }
                if (i == 4 && j == 1) {
                    tower->setIndex(1);
                }
                if (i == 6 && j == 4) {
                    tower->setIndex(2);
                }
                if (i == 4 && j == 6) {
                    tower->setIndex(3);
                }
            }
        }
    }
}

void GameLayer::createGraphAndRoards() {
    towersCount_ = 4;   //todo: fill value from tmx
    graph_ = new int *[towersCount_];
    for (int i = 0; i < towersCount_; ++i)
        graph_[i] = new int[towersCount_];

//  roads
//    {0, 5, 4, 0,}
//    {5, 0, 5, 0,}
//    {4, 5, 0, 4,}
//    {0, 0, 4, 0,}

    for (int i = 0; i < towersCount_; ++i) {
        for (int j = 0; j < towersCount_; ++j) {
            graph_[i][j] = 0;
        }
    }
    graph_[0][1] = graph_[1][0] = graph_[1][2] = graph_[2][1] = 5;
    graph_[0][2] = graph_[2][0] = graph_[2][3] = graph_[3][2] = 4;
}

void GameLayer::dijkstra(int src) {
    int dist[towersCount_];

    bool sptSet[towersCount_];

    for (int i = 0; i < towersCount_; i++) {
        dist[i] = INT_MAX, sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < towersCount_ - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < towersCount_; v++) {
            if (!sptSet[v] && graph_[u][v] && dist[u] != INT_MAX && dist[u] + graph_[u][v] < dist[v]) {
                dist[v] = dist[u] + graph_[u][v];
            }
        }
    }

    printSolution(dist, towersCount_);
}

int GameLayer::minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, minIndex = 0;

    for (int v = 0; v < towersCount_; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v], minIndex = v;
        }
    }

    return minIndex;
}

int GameLayer::printSolution(int dist[], int n) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < towersCount_; i++)
        printf("%d \t\t %d\n", i, dist[i]);
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
