#ifndef __HUD_LAYER_H_
#define __HUD_LAYER_H_

#include "cocos2d.h"

class HUDLayer : public cocos2d::Layer {
public:
    static HUDLayer *create();
    ~HUDLayer();

private:
    bool init();
    void restartCallback(cocos2d::Ref* pSender);

    cocos2d::Menu *menu_;
};

#endif //__HUD_LAYER_H_
