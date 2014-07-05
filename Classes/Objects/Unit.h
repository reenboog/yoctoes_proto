#ifndef __UNIT_H_
#define __UNIT_H_

#include "cocos2d.h"

class Unit : public cocos2d::Sprite {
public:
    static Unit *create();
    ~Unit();

private:
    bool init();
};


#endif //__UNIT_H_
