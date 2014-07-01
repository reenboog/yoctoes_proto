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

    // touches
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

private:
    cocos2d::Sprite *back_;
};

#endif // __GAME_LAYER_H__
