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
private:
    Sprite *back;
};

#endif // __HELLOWORLD_SCENE_H__
