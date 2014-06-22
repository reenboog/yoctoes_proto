#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class GameLayer: public Layer {
public:
    virtual ~GameLayer();

    static Scene* scene();
    virtual bool init();
    
    GameLayer();
    
    CREATE_FUNC(GameLayer);
    
    // touches
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
private:
    Sprite *back;
};

#endif // __HELLOWORLD_SCENE_H__
