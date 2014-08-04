#include "EventsMediator.h"
#include "Tower.h"

EventsMediator *EventsMediator::sharedInstance_ = nullptr;

EventsMediator *EventsMediator::sharedInstance() {
    if (sharedInstance_ == nullptr) {
        sharedInstance_ = new EventsMediator();
    }

    return sharedInstance_;
}

EventsMediator::EventsMediator() {
}

EventsMediator::~EventsMediator() {
}

//void EventsMediator::selectorFromTower(Tower *tower, TowerMemFun foo) {
//    (tower->*foo)();
//}
//
//void EventsMediator::selectorToGameLayer(GameLayerMemFun foo) {
//    (gameLayer_->*foo)();
//}
