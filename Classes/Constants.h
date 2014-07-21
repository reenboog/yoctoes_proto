#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define SCREEN_SIZE Director::getInstance()->getWinSize()
#define SCREEN_CENTER cocos2d::Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2)

//typedef void (Tower::* TowerMemFun)();

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

    enum class Events : int {
        T_afterCaptureTheTowerWin = 0,
        T_afterCaptureTheTowerLose,
    };

};

#endif // __CONSTANTS_H__