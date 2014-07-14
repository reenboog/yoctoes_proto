#include "GameLayer.h"
#include "Tower.h"
#include "Road.h"
#include "Unit.h"

using namespace std;
using namespace cocos2d;

const int n = 9;
const int testMap_[n][n] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _}, 0 */
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _}, 1 */
        {0, 0, 0, 1, 2, 1, 1, 0, 0},/*{_, _, _, _, b, _, _, _, _}, 2 */
        {0, 0, 0, 1, 0, 0, 1, 1, 1},/*{_, _, _, _, _, _, _, _, _}, 3 */
        {0, 0, 0, 1, 0, 0, 0, 0, 1},/*{_, _, _, _, _, _, _, _, _}, 4 */
        {0, 3, 1, 2, 1, 1, 2, 1, 4},/*{_, a, _, c, _, _, e, _, f}, 5 */
        {0, 1, 0, 1, 0, 0, 0, 0, 1},/*{_, _, _, _, _, _, _, _, _}, 6 */
        {0, 1, 1, 2, 1, 2, 1, 1, 1},/*{_, _, _, d, _, g, _, _, _}, 7 */
        {0, 0, 0, 0, 0, 0, 0, 0, 0},/*{_, _, _, _, _, _, _, _, _}, 8 */
        /*                             0  1  2  3  4  5  6  7  8    */
};
const float tileWidth = 38.0f;

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
    this->createRoadsManually();

    this->scheduleUpdate();

    return true;
}

void GameLayer::update(float dt) {
    int size = towers_.size();
    for (int i = 0; i < size; ++i) {
        towers_.at((unsigned long) i)->update(dt);
    }
}

#pragma mark - board and path

void GameLayer::createBoard() {
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

            } else {
                Tower *tower = nullptr;
                if (testMap_[i][j] == 2) {  //neutral
                    tower = Tower::createWithType(Constants::TeamType::neutral);
                } else if (testMap_[i][j] == 3) {   //me
                    tower = Tower::createWithType(Constants::TeamType::red);
                    playerTeam_ = tower->getTeam();
                } else if (testMap_[i][j] == 4) {   //enemy
                    tower = Tower::createWithType(Constants::TeamType::blue);
                }

                tower->setPosition({tileWidth * j + tileWidth / 2, tileWidth * (n - i)});
                this->addChild(tower, 10);

                if (i == 5 && j == 1) {
                    tower->setID('a');
                }
                if (i == 2 && j == 4) {
                    tower->setID('b');
                }
                if (i == 5 && j == 3) {
                    tower->setID('c');
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
                distanceFromStartForTower_[tower] = INT_MAX;
            }
        }
    }
}

void GameLayer::createRoadsManually() {
    Road *road;

    road = new Road(this->towerWithID('a'), this->towerWithID('c'), 2);
    road->addRoadPoint({tileWidth * 2 + tileWidth / 2, tileWidth * (n - 5)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('a'), this->towerWithID('d'), 3);
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 6)});
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 2 + tileWidth / 2, tileWidth * (n - 7)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('b'), this->towerWithID('c'), 3);
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 4)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('c'), this->towerWithID('d'), 1);
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 6)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('b'), this->towerWithID('f'), 6);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 4)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('c'), this->towerWithID('e'), 2);
    road->addRoadPoint({tileWidth * 4 + tileWidth / 2, tileWidth * (n - 5)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 5)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('e'), this->towerWithID('f'), 1);
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 5)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('d'), this->towerWithID('g'), 1);
    road->addRoadPoint({tileWidth * 4 + tileWidth / 2, tileWidth * (n - 7)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('g'), this->towerWithID('f'), 4);
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 6)});
    roads_.push_back(road);
}

void GameLayer::dijkstra(Constants::TeamType teamSrc) {
    Constants::TeamType team = teamSrc;
    while (towersCopy_.size() > 0) {
        Tower *smallest = extractSmallest(towersCopy_);
        vector<Tower *> *adjacentTowers = adjacentRemainingTowers(smallest);

        const int size = adjacentTowers->size();
        for (int i = 0; i < size; ++i) {
            Tower *adjacent = adjacentTowers->at((unsigned long) i);
            int distance = this->distance(smallest, adjacent) + distanceFromStartForTower_[smallest];
            if (distance < distanceFromStartForTower_[adjacent]) {
                if (team != adjacent->getTeam() && adjacent->getTeam() != Constants::TeamType::neutral) {
                    distance = distance * 30;   //fixme
                }
                distanceFromStartForTower_[adjacent] = distance;
                previousForTower_[adjacent] = smallest;
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
        Tower *current = towers.at((unsigned long) i);
        if (distanceFromStartForTower_[current] < distanceFromStartForTower_[smallest]) {
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
        Road *road = roads_.at((unsigned long) i);
        Tower *adjacent = NULL;
        if (road->getTowerOne() == tower) {
            adjacent = road->getTowerTwo();
        } else if (road->getTowerTwo() == tower) {
            adjacent = road->getTowerOne();
        }
        if (adjacent && contains(towersCopy_, adjacent)) {
            adjacentTowers->push_back(adjacent);
        }
    }
    return adjacentTowers;
}

int GameLayer::distance(Tower *towerOne, Tower *towerTwo) {
    const int size = roads_.size();
    for (int i = 0; i < size; ++i) {
        Road *road = roads_.at((unsigned long) i);
        if (road->connects(towerOne, towerTwo)) {
            return road->getDistance();
        }
    }
    return -1; // should never happen
}

bool GameLayer::contains(vector<Tower *> &towers, Tower *tower) {
    const int size = towers.size();
    for (int i = 0; i < size; ++i) {
        if (tower == towers.at((unsigned long) i)) {
            return true;
        }
    }
    return false;
}

void GameLayer::sendUnitsFromTowersToTower(std::vector<Tower *> source, Tower *destination) {
    towersCopy_ = towers_;
    distanceFromStartForTower_[destination] = 0; //find way from destination to all source towers

    this->dijkstra(source.at(0)->getTeam());    //find way for units with team of first tower

    int size = source.size();
    for (int i = 0; i < size; ++i) {
        Tower *currentSource = source.at((unsigned long) i);

        vector<Road *> route = this->routeFromTower(currentSource);

        int unitsForSend = 0;
        Unit *unit = Unit::create(currentSource->getTeam());
        unit->setPosition(currentSource->getPosition());
        if (route.at(0)->getTowerOne() != currentSource) {
            unit->setRoute(route, true);
            unitsForSend = route.at(0)->getTowerTwo()->takeHalfUnits();
        } else {
            unit->setRoute(route);
            unitsForSend = route.at(0)->getTowerOne()->takeHalfUnits();
        }
        unit->setCount(unitsForSend);
        this->addChild(unit, 20);
        unit->startTrek();

        route.clear();
    }

    previousForTower_.clear();
    for (map<Tower *, int>::iterator it = distanceFromStartForTower_.begin(); it != distanceFromStartForTower_.end(); ++it) {
        distanceFromStartForTower_[it->first] = INT_MAX;
    }
    destination->setSelected(false);
    int selectedSize = selectedTowers_.size();
    for (int i = 0; i < selectedSize; ++i) {
        selectedTowers_.at((unsigned long) i)->setSelected(false);
    }
    selectedTowers_.clear();

}

vector<Road *> GameLayer::routeFromTower(Tower *source) {

    vector<char> pathTowers;
    vector<Road *> route;

    Tower *previous = source;   //going back from source to destination
    while (previous) {
        pathTowers.push_back(previous->getID());
        previous = previousForTower_[previous];
    }

    int size = pathTowers.size();
    for (int i = 0; i < size - 1; ++i) {
        char first = pathTowers.at((unsigned long) i);
        char second = pathTowers.at((unsigned long) (i + 1));
        for (vector<Road *>::iterator it = roads_.begin(); it != roads_.end(); ++it) {
            Road *currentRoad = *it;
            if ((currentRoad->getTowerOne()->getID() == first && currentRoad->getTowerTwo()->getID() == second) ||
                    (currentRoad->getTowerOne()->getID() == second && currentRoad->getTowerTwo()->getID() == first)) {
                route.push_back(currentRoad);
            }
        }
    }

    return route;
}

#pragma mark - touches

bool GameLayer::onTouchBegan(Touch *touch, Event *event) {
    cocos2d::Point locationInWorld = this->convertToWorldSpace(touch->getLocation());
    for (vector<Tower *>::iterator it = towers_.begin(); it != towers_.end(); ++it) {
        Tower *currentTower = *it;
        cocos2d::Point position = currentTower->getPosition();
        cocos2d::Size size = currentTower->getContentSize();
        cocos2d::Rect rect = cocos2d::Rect(position.x - size.width / 2, position.y - size.height / 2, size.width, size.height);
        if (rect.containsPoint(locationInWorld)) {
//            if (currentTower->getTeam() != playerTeam_ && selectedTowers_.size() == 0) {
//                return false;
//            }
            if (this->isTowerSelected(currentTower)) {
                currentTower->setSelected(false);
                selectedTowers_.erase(std::remove(selectedTowers_.begin(), selectedTowers_.end(), currentTower), selectedTowers_.end());
                return false;
            }
            currentTower->setSelected(true);
            selectedTowers_.push_back(currentTower);
            return true;
        }
    }

    // if tap outside the tower - unselect all
    int size = selectedTowers_.size();
    for (int i = size - 1; i >= 0; --i) {
        selectedTowers_.at(i)->setSelected(false);
        selectedTowers_.pop_back();
    }

    return false;
}

void GameLayer::onTouchMoved(Touch *touch, Event *event) {
    cocos2d::Point locationInWorld = this->convertToWorldSpace(touch->getLocation());
    for (vector<Tower *>::iterator it = towers_.begin(); it != towers_.end(); ++it) {
        Tower *currentTower = *it;
        cocos2d::Point position = currentTower->getPosition();
        cocos2d::Size size = currentTower->getContentSize();
        cocos2d::Rect rect = cocos2d::Rect(position.x - size.width / 2, position.y - size.height / 2, size.width, size.height);
        if (rect.containsPoint(locationInWorld)) {
            if (this->isTowerSelected(currentTower)) {
                return;
            } else {
                currentTower->setSelected(true);
                selectedTowers_.push_back(currentTower);
            }
        }
    }
}

void GameLayer::onTouchEnded(Touch *touch, Event *event) {
    int size = selectedTowers_.size();
    if (size > 1) {
        Tower *destination = selectedTowers_.at((unsigned long) (size - 1));
        selectedTowers_.pop_back();
        this->sendUnitsFromTowersToTower(selectedTowers_, destination);
    }
}

void GameLayer::onTouchCancelled(Touch *touch, Event *event) {
}

#pragma mark - other

Tower *GameLayer::towerWithID(char id) {
    for (std::vector<Tower *>::iterator it = towers_.begin(); it != towers_.end(); ++it) {
        Tower *currentTower = *it;
        if (currentTower->getID() == id) {
            return currentTower;
        }
    }

    return NULL;
}

bool GameLayer::isTowerSelected(Tower *tower) {
    return std::find(selectedTowers_.begin(), selectedTowers_.end(), tower) != selectedTowers_.end();
}
