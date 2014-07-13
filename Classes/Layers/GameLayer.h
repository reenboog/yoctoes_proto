#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "Constants.h"
#include "Tower.h"

class Road;
class Tower;

class GameLayer : public cocos2d::Layer {
public:
    static cocos2d::Scene *scene();

    ~GameLayer();

    CREATE_FUNC(GameLayer);

    // touches
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

private:
    std::vector<Road *> roads_;
    std::vector<Tower *> towers_;
    std::vector<Tower *> towersCopy_;
    std::vector<Tower *> selectedTowers_;
    std::map<Tower *, Tower *> previousForTower_;
    std::map<Tower *, int> distanceFromStartForTower_;

    virtual bool init();
    void createBoard();
    void createRoadsManually();
    void update(float dt);

    void dijkstra(Constants::TeamType teamSrc);
    Tower *extractSmallest(std::vector<Tower *> &towers);
    std::vector<Tower *> *adjacentRemainingTowers(Tower *tower);
    int distance(Tower *towerOne, Tower *towerTwo);
    bool contains(std::vector<Tower *> &towers, Tower *tower);
    std::vector<Road *> routeFromTower(Tower *source);
    void sendUnitsFromTowersToTower(std::vector<Tower *>source, Tower *destination);

    Tower *towerWithID(char id);
    bool isTowerSelected(Tower *tower);
};

#endif // __GAME_LAYER_H__
