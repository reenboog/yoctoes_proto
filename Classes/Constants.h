#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

namespace Constants {

    enum class TileType : int {
        nothing = 0,
        road = 1,
        tower = 2,
    };

    enum class TowerElement : int {
        none = 0,
        water,
        fire,
        air,
        earth,
    };

    enum class RoadType : int {
        flat = 0,
        leftAngle,
        rightAngle,
    };

    enum class TeamType : int {
        neutral = 0,
        red,
        blue,
        green,
        yellow,
    };

};

#endif // __CONSTANTS_H__