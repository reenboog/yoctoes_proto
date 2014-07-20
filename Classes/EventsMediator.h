#ifndef __SCRIPTS_MEDIATOR_H_
#define __SCRIPTS_MEDIATOR_H_

class Tower;
class GameLayer;

typedef void (Tower::* TowerMemFun)();
typedef void (Tower::* GameLayerMemFun)();

class EventsMediator {
public:
    static EventsMediator *sharedInstance();

    void selectorFromTower(Tower *tower, TowerMemFun foo);
    void selectorFromGameLayer(GameLayerMemFun foo);

private:
    static EventsMediator *sharedInstance_;

    EventsMediator();
    ~EventsMediator();
};

#endif //__SCRIPTS_MEDIATOR_H_
