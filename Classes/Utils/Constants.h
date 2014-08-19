#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#import "Types.h"

#define SCREEN_SIZE Director::getInstance()->getWinSize()
#define SCREEN_CENTER cocos2d::Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2)

enum class TowerFunction : int {
    pit = 0,
    combat,
    power,
};

enum class TowerType : int {
    pit = 0,
    combat_weak_neutral,
    combat_strong_neutral,
    power,
};

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

//enum class Event : int {
//    T_afterCaptureTheTowerWin = 0,
//    T_afterCaptureTheTowerLose,
//};

enum class NatureType : int {
    neutral = 0,
    fire,
    water,
    earth,
    evil,
};

const TowerParams weakTowerParams = {15, 1.0f, 1.0f};
const TowerParams strongTowerParams = {30, 0.5f, 1.0f};


#endif // __CONSTANTS_H__