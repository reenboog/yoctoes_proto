#include "GameLayer.h"
#include "Tower.h"
#include "Road.h"

using namespace std;
using namespace cocos2d;

const int n = 9;
const int testMap_[n][n] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _}, 0 */
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _}, 1 */
        {0, 0, 0, 1, 2, 1, 1, 0, 0},/*{_, _, _, _, b, _, _, _, _}, 2 */
        {0, 0, 0, 1, 0, 0, 1, 1, 1},/*{_, _, _, _, _, _, _, _, _}, 3 */
        {0, 0, 0, 1, 0, 0, 0, 0, 1},/*{_, _, _, _, _, _, _, _, _}, 4 */
        {0, 2, 1, 2, 1, 1, 2, 1, 2},/*{_, a, _, c, _, _, e, _, f}, 5 */
        {0, 1, 0, 1, 0, 0, 0, 0, 1},/*{_, _, _, _, _, _, _, _, _}, 6 */
        {0, 1, 1, 2, 1, 2, 1, 1, 1},/*{_, _, _, d, _, g, _, _, _}, 7 */
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _}, 8 */
        /*                             0  1  2  3  4  5  6  7  8    */
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

    this->showBoard();
    this->createRoadsManually();

    Tower *src = this->towerWithID('g');
    Tower *dst = this->towerWithID('a');

    src->setDistanceFromStart(0);
    this->dijkstra();
    this->printShortestRouteTo(dst);

    return true;
}

#pragma mark - board and path

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

                if (i == 5 && j == 1) {
                    tower->setID('a');
                }
                if (i == 2 && j == 4) {
                    tower->setID('b');
                }
                if (i == 5 && j == 3) {
                    tower->setID('c');;
                }
                if (i == 7 && j == 3) {
                    tower->setID('d');
                }
                if (i == 5 && j == 6) {
                    tower->setID('e');
                }
                if (i == 5 && j == 8) {
                    tower->setID('f');
                }
                if (i == 7 && j == 5) {
                    tower->setID('g');
                }

                towers_.push_back(tower);
            }
        }
    }
}

void GameLayer::createRoadsManually() {
    Road *road;

    road = new Road(this->towerWithID('a'), this->towerWithID('c'), 2);
    roads_.push_back(road);

    road = new Road(this->towerWithID('a'), this->towerWithID('d'), 4);
    roads_.push_back(road);

    road = new Road(this->towerWithID('b'), this->towerWithID('c'), 4);
    roads_.push_back(road);

    road = new Road(this->towerWithID('c'), this->towerWithID('d'), 2);
    roads_.push_back(road);

    road = new Road(this->towerWithID('b'), this->towerWithID('f'), 7);
    roads_.push_back(road);

    road = new Road(this->towerWithID('c'), this->towerWithID('e'), 3);
    roads_.push_back(road);

    road = new Road(this->towerWithID('e'), this->towerWithID('f'), 2);
    roads_.push_back(road);

    road = new Road(this->towerWithID('d'), this->towerWithID('g'), 2);
    roads_.push_back(road);

    road = new Road(this->towerWithID('g'), this->towerWithID('f'), 5);
    roads_.push_back(road);
}

void GameLayer::dijkstra() {
    while (towers_.size() > 0) {
        Tower *smallest = extractSmallest(towers_);
        vector<Tower *> *adjacentTowers = adjacentRemainingTowers(smallest);

        const int size = adjacentTowers->size();
        for (int i = 0; i < size; ++i) {
            Tower *adjacent = adjacentTowers->at(i);
            int distance = this->distance(smallest, adjacent) + smallest->getDistanceFromStart();
            if (distance < adjacent->getDistanceFromStart()) {
                adjacent->setDistanceFromStart(distance);
                adjacent->setPrevious(smallest);
            }
        }
        delete adjacentTowers;
    }
}

Tower *GameLayer::extractSmallest(vector<Tower *> &towers) {
    int size = towers.size();
    if (size == 0) return NULL;
    int smallestPosition = 0;
    Tower *smallest = towers.at(0);
    for (int i = 1; i < size; ++i) {
        Tower *current = towers.at(i);
        if (current->getDistanceFromStart() < smallest->getDistanceFromStart()) {
            smallest = current;
            smallestPosition = i;
        }
    }
    towers.erase(towers.begin() + smallestPosition);
    return smallest;
}

vector<Tower *> *GameLayer::adjacentRemainingTowers(Tower *tower) {
    vector<Tower *> *adjacentTowers = new vector<Tower *>();
    const int size = roads_.size();
    for (int i = 0; i < size; ++i) {
        Road *road = roads_.at(i);
        Tower *adjacent = NULL;
        if (road->getTowerOne() == tower) {
            adjacent = road->getTowerTwo();
        } else if (road->getTowerTwo() == tower) {
            adjacent = road->getTowerOne();
        }
        if (adjacent && contains(towers_, adjacent)) {
            adjacentTowers->push_back(adjacent);
        }
    }
    return adjacentTowers;
}

int GameLayer::distance(Tower *towerOne, Tower *towerTwo) {
    const int size = roads_.size();
    for (int i = 0; i < size; ++i) {
        Road *road = roads_.at(i);
        if (road->connects(towerOne, towerTwo)) {
            return road->getDistance();
        }
    }
    return -1; // should never happen
}

bool GameLayer::contains(vector<Tower *> &towers, Tower *tower) {
    const int size = towers.size();
    for (int i = 0; i < size; ++i) {
        if (tower == towers.at(i)) {
            return true;
        }
    }
    return false;
}

void GameLayer::printShortestRouteTo(Tower *destination) {
    Tower *previous = destination;
    printf("Distance from start: %d\n", destination->getDistanceFromStart());
    while (previous) {
        printf("%c ", previous->getID());
        previous = previous->getPrevious();
    }
    printf("\n");
}


Tower *GameLayer::towerWithID(char id) {
    for (std::vector<Tower *>::iterator it = towers_.begin(); it != towers_.end(); ++it) {
        Tower *currentTower = *it;
        if (currentTower->getID() == id) {
            return currentTower;
        }
    }

    return NULL;
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
