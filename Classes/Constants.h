#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define SCREEN_SIZE CCDirector::sharedDirector()->getWinSize()
#define SCREEN_CENTER CCPoint(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2)

namespace Constants {

    enum class TeamColor : int {
        unfilled = 0,
        red,
        blue,
        green,
        yellow,
    };

    enum class TeamGroup : int {
        neutral = 0,
        alfa,
        omega,
    };

};

#endif // __CONSTANTS_H__