#ifndef __GAME_STATE_H_
#define __GAME_STATE_H_

#include "cocos2d.h"

enum State : int {
    gameLayer = 0,
};

class GameState {
public:
    static GameState *sharedInstance();

    void startGameLayer();
private:
    static GameState *sharedInstance_;
    bool directorRunned_;
    State currentState_;

    GameState();
    ~GameState();

    void startScene(cocos2d::Scene *scene);
};


#endif //__GAME_STATE_H_
