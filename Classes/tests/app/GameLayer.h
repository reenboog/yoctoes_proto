#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer {
public:
    virtual ~GameLayer();

    static cocos2d::Scene *scene();

    virtual bool init();

    GameLayer();

    CREATE_FUNC(GameLayer);
private:
    cocos2d::Sprite *back_;
};

#endif // __GAME_LAYER_H__
