#ifndef __SCRIPTS_MEDIATOR_H_
#define __SCRIPTS_MEDIATOR_H_

#include "GameLayer.h"

class Tower;
class GameLayer;

typedef void (GameLayer::* GameLayerMemFun)();

class EventsMediator {
public:
    static EventsMediator *sharedInstance();

    void setGameLayer(GameLayer *gameLayer);
    void selectorToGameLayer(GameLayerMemFun foo);

private:
    static EventsMediator *sharedInstance_;
    GameLayer *gameLayer_;

    EventsMediator();
    ~EventsMediator();

//    void selectorFromTower(Tower *tower, TowerMemFun foo);
};

inline void EventsMediator::setGameLayer(GameLayer *gameLayer) {
    gameLayer_ = gameLayer;
}

#endif //__SCRIPTS_MEDIATOR_H_
