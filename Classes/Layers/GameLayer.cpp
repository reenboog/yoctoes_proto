#include "GameLayer.h"
#include "Road.h"
#include "Unit.h"
#include "HUDLayer.h"
#include "EventsMediator.h"
#include "TowersManager.h"

using namespace std;
using namespace cocos2d;

const int n = 9;
const int testMap_[n][n] = {
        {6, 1, 1, 1, 1, 2, 0, 0, 4},/*{h, _, _, _, _, j, _, _, i, }, 0 */
        {1, 0, 0, 1, 0, 1, 0, 0, 1},/*{_, _, _, _, _, _, _, _, _, }, 1 */
        {1, 7/*2*/, 0, 2, 0, 1, 1, 2, 1},/*{_, m, _, b, _, _, _, k, _, }, 2 */
        {0, 1, 0, 0, 0, 1, 0, 0, 1},/*{_, _, _, _, _, _, _, _, _, }, 3 */
        {0, 1, 0, 0, 0, 1, 1, 1, 1},/*{_, _, _, _, _, _, _, _, _, }, 4 */
        {1, 1, 8, 0, 0, 2, 0, 2, 0},/*{_, _, c, _, _, e, _, f, _, }, 5 */
        {3, 0, 1, 0, 0, 1, 0, 0, 0},/*{a, _, _, _, _, _, _, _, _, }, 6 */
        {0, 0, 2/*7*/, 0, 0, 1, 1, 1, 5},/*{_, _, d, _, _, _, _, _, l, }, 7 */
        {0, 0, 1, 1, 2, 1, 0, 0, 0},/*{_, _, _, _, g, _, _, _, _, }, 8 */
        /*                             0  1  2  3  4  5  6  7  8       */
};
const float tileWidth = 38.0f;
const int UNITS_IN_ONE_GROUP = 5;

GameLayer::~GameLayer() {
}

Scene *GameLayer::scene() {
    Scene *scene = Scene::create();

    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);

    HUDLayer *hud = HUDLayer::create();
    scene->addChild(hud, 50);

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

    playerGroup_ = TeamGroup::alfa;

    this->createBoard();
    this->createRoadsManually();

    this->scheduleUpdate();

    return true;
}

void GameLayer::update(float dt) {
    int size = towers_.size();
    for (int i = 0; i < size; ++i) {
        Tower *ct = towers_.at((unsigned long) i);
        ct->update(dt);

//        int chanse = randInRangei(0, 2);
//        if (chanse > 0)
//            continue;
//        //npc tower actions
//        if (ct->getTeamColor() != TeamColor::blue) {
//            if (ct->getActionCooldown() < 0) {
//                vector<Tower *> towers = findAvailableTowersFromTower(ct);
//                int sizeT = towers.size();
//                if (sizeT > 0) {
//                    Tower *dst = towers.at((unsigned long) randInRangei(0, sizeT - 1));
//                    towers.clear();
//                    towers.push_back(ct);
//                    this->sendUnitsFromTowersToTower(towers, dst);
//                }
//                ct->setActionCooldown(randInRangef(10.0f, 15.0f));
//            }
//        }
    }
    this->checkUnitsCollision();
    this->removeUnits();
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
                if (testMap_[i][j] == 2) {  //unfilled
                    tower = TowersManager::sharedInstance()->createTowerWithParams(TowerType::combat_weak_neutral, TeamColor::unfilled);
                } else if (testMap_[i][j] == 3) {
                    tower = TowersManager::sharedInstance()->createTowerWithParams(TowerType::combat_weak_neutral, TeamColor::blue);
                    playerColor_ = tower->getTeamColor();
                } else if (testMap_[i][j] == 4) {
                    tower = TowersManager::sharedInstance()->createTowerWithParams(TowerType::combat_weak_neutral, TeamColor::red);
                } else if (testMap_[i][j] == 5) {
                    tower = TowersManager::sharedInstance()->createTowerWithParams(TowerType::combat_weak_neutral, TeamColor::yellow);
                } else if (testMap_[i][j] == 6) {
                    tower = TowersManager::sharedInstance()->createTowerWithParams(TowerType::combat_weak_neutral, TeamColor::green);
                } else if (testMap_[i][j] == 7) {
                    tower = TowersManager::sharedInstance()->createTowerWithParams(TowerType::power, TeamColor::unfilled);
                } else if (testMap_[i][j] == 8) {
                    tower = TowersManager::sharedInstance()->createTowerWithParams(TowerType::pit, TeamColor::unfilled);
                }

                tower->setPosition({tileWidth * j + tileWidth / 2, tileWidth * (n - i)});
                this->addChild(tower, 10);

                if (i == 6 && j == 0) {
                    tower->setID('a');
                }
                if (i == 2 && j == 3) {
                    tower->setID('b');
                }
                if (i == 5 && j == 2) {
                    tower->setID('c');
                }
                if (i == 7 && j == 2) {
                    tower->setID('d');
                }
                if (i == 5 && j == 5) {
                    tower->setID('e');
                }
                if (i == 5 && j == 7) {
                    tower->setID('f');
                }
                if (i == 8 && j == 4) {
                    tower->setID('g');
                }
                if (i == 0 && j == 0) {
                    tower->setID('h');
                }
                if (i == 0 && j == 8) {
                    tower->setID('i');
                }
                if (i == 0 && j == 5) {
                    tower->setID('j');
                }
                if (i == 2 && j == 7) {
                    tower->setID('k');
                }
                if (i == 7 && j == 8) {
                    tower->setID('l');
                }
                if (i == 2 && j == 1) {
                    tower->setID('m');
                }

                tower->setDelegate(this);
                tower->setUpdateDelegate(TowersManager::sharedInstance());
                towers_.push_back(tower);
                distanceFromStartForTower_[tower] = INT_MAX;
            }
        }
    }
}

void GameLayer::createRoadsManually() {
    Road *road;

    road = new Road(this->towerWithID('a'), this->towerWithID('c'), 2);
    road->addRoadPoint({tileWidth * 0 + tileWidth / 2, tileWidth * (n - 5)});
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 5)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('c'), this->towerWithID('d'), 1);
    road->addRoadPoint({tileWidth * 2 + tileWidth / 2, tileWidth * (n - 6)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('a'), this->towerWithID('m'), 4);
    road->addRoadPoint({tileWidth * 0 + tileWidth / 2, tileWidth * (n - 5)});
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 5)});
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 3)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('c'), this->towerWithID('m'), 3);
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 5)});
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 3)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('m'), this->towerWithID('h'), 6);
    road->addRoadPoint({tileWidth * 0 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 0 + tileWidth / 2, tileWidth * (n - 1)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('h'), this->towerWithID('b'), 4);
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 0)});
    road->addRoadPoint({tileWidth * 2 + tileWidth / 2, tileWidth * (n - 0)});
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 0)});
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 1)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('b'), this->towerWithID('j'), 3);
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 1)});
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 0)});
    road->addRoadPoint({tileWidth * 4 + tileWidth / 2, tileWidth * (n - 0)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('j'), this->towerWithID('k'), 3);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 1)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 2)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('j'), this->towerWithID('e'), 4);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 1)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 4)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('j'), this->towerWithID('f'), 6);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 1)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 4)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('j'), this->towerWithID('i'), 10);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 1)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 1)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('i'), this->towerWithID('k'), 2);
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 1)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 2)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('d'), this->towerWithID('g'), 2);
    road->addRoadPoint({tileWidth * 2 + tileWidth / 2, tileWidth * (n - 8)});
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 8)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('g'), this->towerWithID('e'), 3);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 8)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 6)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('g'), this->towerWithID('l'), 4);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 8)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 7)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('l'), this->towerWithID('e'), 4);
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 7)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 6)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('e'), this->towerWithID('f'), 3);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 4)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('e'), this->towerWithID('k'), 4);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 2)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('k'), this->towerWithID('f'), 4);
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 4)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('f'), this->towerWithID('i'), 5);
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 1)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('e'), this->towerWithID('i'), 7);
    road->addRoadPoint({tileWidth * 5 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 6 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 7 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 4)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 3)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 2)});
    road->addRoadPoint({tileWidth * 8 + tileWidth / 2, tileWidth * (n - 1)});
    roads_.push_back(road);

    road = new Road(this->towerWithID('h'), this->towerWithID('j'), 4);
    road->addRoadPoint({tileWidth * 1 + tileWidth / 2, tileWidth * (n - 0)});
    road->addRoadPoint({tileWidth * 2 + tileWidth / 2, tileWidth * (n - 0)});
    road->addRoadPoint({tileWidth * 3 + tileWidth / 2, tileWidth * (n - 0)});
    road->addRoadPoint({tileWidth * 4 + tileWidth / 2, tileWidth * (n - 0)});
    roads_.push_back(road);
}

void GameLayer::dijkstra(TeamColor teamSrc) {
    TeamColor team = teamSrc;
    Tower *destination = extractSmallest(towersCopy_, false);
    while (towersCopy_.size() > 0) {
        Tower *smallest = extractSmallest(towersCopy_);
        vector<Tower *> *adjacentTowers = adjacentRemainingTowers(smallest);

        const int size = adjacentTowers->size();
        for (int i = 0; i < size; ++i) {
            Tower *adjacent = adjacentTowers->at((unsigned long) i);
            int distance = this->distance(smallest, adjacent) + distanceFromStartForTower_[smallest];
            if (distance < distanceFromStartForTower_[adjacent]) {
                if (this->groupForColor(team) != adjacent->getTeamGroup() || adjacent->getTeamGroup() == TeamGroup::neutral) {
                    if (smallest == destination) {
                        distance = distance + SHRT_MAX / 2;
                    } else {
                        distance = distance + SHRT_MAX;
                    }
                }
                distanceFromStartForTower_[adjacent] = distance;
                previousForTower_[adjacent] = smallest;
            }
        }
        delete adjacentTowers;
    }
}

Tower *GameLayer::extractSmallest(vector<Tower *> &towers, bool remove) {
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
    if (remove)
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

    this->dijkstra(source.at(0)->getTeamColor());    //find way for units with team of first tower

    int size = source.size();
    for (int i = 0; i < size; ++i) {
        Tower *currentSource = source.at((unsigned long) i);

        if (currentSource->getTowerFunction() == TowerFunction::power) {
            if (currentSource->getTeamGroup() == destination->getTeamGroup()) {
                this->applyPowerUp(currentSource, destination);
                continue;
            } else {
                continue;
            }
        }

        vector<Road *> route = this->routeFromTower(currentSource);

        if (route.size() == 0) {
            continue;
        }

        int allUnitsForSend = 0;
        bool needSwap = false;
        if (route.at(0)->getTowerOne() != currentSource) {
            needSwap = true;
            allUnitsForSend = route.at(0)->getTowerTwo()->takeHalfUnits();
        } else {
            allUnitsForSend = route.at(0)->getTowerOne()->takeHalfUnits();
        }

        float delayTime = 0.0f;
        int unitsForSend = allUnitsForSend > UNITS_IN_ONE_GROUP ? UNITS_IN_ONE_GROUP : allUnitsForSend;
        while (unitsForSend > 0) {

            Unit *unit = Unit::create(currentSource->getTeamColor());
            unit->setPosition(currentSource->getPosition());
            needSwap ? unit->setRoute(route, true) : unit->setRoute(route);
            unit->setCount(unitsForSend);
            unit->setTeamGroup(currentSource->getTeamGroup());
            this->addChild(unit, 20);
            unit->setSpeed(currentSource->getUnitsSpeed());
            unit->setNatureType(currentSource->getNatureType());
            unit->startTrek(delayTime);
            units_.push_back(unit);

            allUnitsForSend = allUnitsForSend - unitsForSend;
            unitsForSend = allUnitsForSend > UNITS_IN_ONE_GROUP ? UNITS_IN_ONE_GROUP : allUnitsForSend;
            delayTime = delayTime + 0.3f;
        }

        route.clear();
    }

    previousForTower_.clear();
    for (map<Tower *, int>::iterator it = distanceFromStartForTower_.begin(); it != distanceFromStartForTower_.end(); ++it) {
        distanceFromStartForTower_[it->first] = INT_MAX;
    }
    destination->setSelected(false);
    if (source.at(0)->getTeamColor() == TeamColor::blue) {
        int selectedSize = selectedTowers_.size();
        for (int i = 0; i < selectedSize; ++i) {
            selectedTowers_.at((unsigned long) i)->setSelected(false);
        }
        selectedTowers_.clear();
    }

}

void GameLayer::applyPowerUp(Tower *src, Tower *dst) {
    TowersManager::sharedInstance()->addPoweredTower(src, dst);
    dst->setPower(dst->getPower() + 1);
    //TODO: can start animation
}

vector<Road *> GameLayer::routeFromTower(Tower *source) {

    vector<char> pathTowers;
    vector<Road *> route;
    long int weight = 0;

    Tower *previous = source;   //going back from source to destination
    while (previous) {
        weight = weight + distanceFromStartForTower_[previous];
        pathTowers.push_back(previous->getID());
        previous = previousForTower_[previous];
    }

    if (weight > SHRT_MAX) {
        return route;
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

vector<Tower *> GameLayer::findAvailableTowersFromTower(Tower *tower) {
    vector<Tower *> towers;
    int size = roads_.size();
    for (int i = 0; i < size; ++i) {
        Road *rd = roads_.at((unsigned long) i);
        if (rd->getTowerOne() == tower) {
            towers.push_back(rd->getTowerTwo());
        } else if (rd->getTowerTwo() == tower) {
            towers.push_back(rd->getTowerOne());
        }
    }

    return towers;
};

#pragma mark - touches

bool GameLayer::onTouchBegan(Touch *touch, Event *event) {
    cocos2d::Point locationInWorld = this->convertToWorldSpace(touch->getLocation());
    for (vector<Tower *>::iterator it = towers_.begin(); it != towers_.end(); ++it) {
        Tower *currentTower = *it;
        cocos2d::Point position = currentTower->getPosition();
        cocos2d::Size size = cocos2d::Size(32.0f, 32.0f);   //FIXME:
        cocos2d::Rect rect = cocos2d::Rect(position.x - size.width / 2, position.y - size.height / 2, size.width, size.height);
        if (rect.containsPoint(locationInWorld)) {
            if (currentTower->getTeamColor() != playerColor_ && selectedTowers_.size() == 0) {
                return false;
            }
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
        selectedTowers_.at((unsigned long) i)->setSelected(false);
        selectedTowers_.pop_back();
    }

    return false;
}

void GameLayer::onTouchMoved(Touch *touch, Event *event) {
    cocos2d::Point locationInWorld = this->convertToWorldSpace(touch->getLocation());
    for (vector<Tower *>::iterator it = towers_.begin(); it != towers_.end(); ++it) {
        Tower *currentTower = *it;
        cocos2d::Point position = currentTower->getPosition();
        cocos2d::Size size = cocos2d::Size(32.0f, 32.0f);   //FIXME:
        cocos2d::Rect rect = cocos2d::Rect(position.x - size.width / 2, position.y - size.height / 2, size.width, size.height);
        if (rect.containsPoint(locationInWorld)) {

            if (this->isTowerSelected(currentTower)) {
                return;
            } else if (selectedTowers_.size() > 1) {
                Tower *lastSelected = selectedTowers_.back();
                if (lastSelected->getTeamColor() != playerColor_) {
                    lastSelected->setSelected(false);
                    selectedTowers_.pop_back();
                }
            }

            currentTower->setSelected(true);
            selectedTowers_.push_back(currentTower);
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

TeamGroup GameLayer::groupForColor(TeamColor color) {
    if (color == TeamColor::blue || color == TeamColor::green)
        return TeamGroup::alfa;

    if (color == TeamColor::red || color == TeamColor::yellow)
        return TeamGroup::omega;

    return TeamGroup::neutral;
}

#pragma mark -

void GameLayer::checkWin() {
    bool win = true;
    for (std::vector<Tower *>::iterator it = towers_.begin(); it != towers_.end(); ++it) {
        Tower *currentTower = *it;
        if (currentTower->getTeamGroup() != playerGroup_) {
            win = false;
            break;
        }
    }
    if (win) {
        this->win();
    }
}

void GameLayer::checkLose() {
    CCLOG("LOSE");
}

void GameLayer::win() {
    this->getEventDispatcher()->removeEventListenersForTarget(this, false);
    Label *winLabel = Label::createWithTTF("YOU WIN", "Chapaza.ttf", 48);
    winLabel->setColor(Color3B::RED);
    winLabel->setPosition(SCREEN_CENTER);
    this->addChild(winLabel, 100);
}

void GameLayer::checkUnitsCollision() {
    int size = units_.size();
    for (int i = 0; i < size; ++i) {
        for (int j = (i + 1); j < size; ++j) {
            if (units_.at(i) != units_.at(j)) {
                if (units_.at(i)->getTeamGroup() != units_.at(j)->getTeamGroup()) {
                    bool collided = this->checkCollisionBetweenUnits(units_.at(i), units_.at(j));
                    if (collided) {
                        int firstUnitCount = units_.at(i)->getCount();
                        units_.at(i)->setCount(firstUnitCount - units_.at(j)->getCount() * (int) influenceOfTheFirstToSecond(units_.at(j)->getNatureType(), units_.at(i)->getNatureType()));
                        units_.at(j)->setCount(units_.at(j)->getCount() - firstUnitCount * (int) influenceOfTheFirstToSecond(units_.at(i)->getNatureType(), units_.at(j)->getNatureType()));
                        if (units_.at(i)->getCount() <= 0) {
                            units_.at(i)->setShouldBeRemoved(true);
                        }
                        if (units_.at(j)->getCount() <= 0) {
                            units_.at(j)->setShouldBeRemoved(true);
                        }
                    }
                }
            }
        }
    }
}

bool GameLayer::checkCollisionBetweenUnits(Unit *unitOne, Unit *unitTwo) {  //TODO: refactor later with normal art
    Sprite *unitOneSprite = unitOne->getUnitBody();
    Sprite *unitTwoSprite = unitTwo->getUnitBody();
    Rect unitOneRect = Rect(
            unitOne->getPosition().x - unitOneSprite->getContentSize().width / 4,
            unitOne->getPosition().y - unitOneSprite->getContentSize().height / 4,
            unitOneSprite->getContentSize().width / 2,
            unitOneSprite->getContentSize().height / 2);
    Rect unitTwoRect = Rect(
            unitTwo->getPosition().x - unitTwoSprite->getContentSize().width / 4,
            unitTwo->getPosition().y - unitTwoSprite->getContentSize().height / 4,
            unitTwoSprite->getContentSize().width / 2,
            unitTwoSprite->getContentSize().height / 2);
    if (unitOneRect.intersectsRect(unitTwoRect)) {
        if (unitOne->getLastCollidedUnit() != unitTwo) {
            unitOne->setLastCollidedUnit(unitTwo);
            unitTwo->setLastCollidedUnit(unitOne);
            return true;
        }
    }
    return false;
}

void GameLayer::removeUnits() {
    int size = units_.size();
    for (int i = size - 1; i >= 0; --i) {
        Unit *currentUnit = units_.at(i);
        if (currentUnit->isShouldBeRemoved()) {
            units_.erase(units_.begin() + i);
            currentUnit->removeFromParentAndCleanup(true);
        }
    }
}

#pragma mark - draw

//void GameLayer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) {
//    customCommand_.init(_globalZOrder);
//    customCommand_.func = CC_CALLBACK_0(GameLayer::onDrawPrimitives, this, transform, transformUpdated);
//    renderer->addCommand(&customCommand_);
//}
//
//void GameLayer::onDrawPrimitives(const kmMat4 &transform, bool transformUpdated) {
//    kmGLPushMatrix();
//    kmGLLoadMatrix(&transform);
//
//    glLineWidth(1);
//    DrawPrimitives::setDrawColor4B(255,255,255,255);
//    DrawPrimitives::setPointSize(1);
//
//    // Anti-Aliased
//    glEnable(GL_LINE_SMOOTH);
//
//    // filled poly
//    glLineWidth(1);
//    Point filledVertices[] = { Point(10,120), Point(50,120), Point(50,170), Point(25,200), Point(10,170) };
//    DrawPrimitives::drawSolidPoly(filledVertices, 5, Color4F(0.5f, 0.5f, 1, 1 ) );
//
////    DrawPrimitives::drawLine({0.0f, 0.0f}, {500.0f, 500.0f});
//}
