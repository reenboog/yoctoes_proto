#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

class GameLayer1 : public cocos2d::Layer {
public:
    virtual ~GameLayer1();

    static cocos2d::Scene *scene();

    virtual bool init();

    GameLayer1();

    CREATE_FUNC(GameLayer1);
private:
    cocos2d::Sprite *back_;
};

#endif // __GAME_LAYER_H__
