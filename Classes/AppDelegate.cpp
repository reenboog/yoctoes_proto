#include "AppDelegate.h"
#include "GameConfig.h"
#include "Localized.h"

#include "SimpleAudioEngine.h"
#import "GameState.h"

using namespace cocos2d;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
    Localized::purge();
    GameConfig::purge();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("yoctoes");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    GameConfig::sharedInstance()->loadFilePaths();
//    GameConfig::sharedInstance()->load();
    
//    Localized::load();

    GameState::sharedInstance()->startGameLayer();

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
