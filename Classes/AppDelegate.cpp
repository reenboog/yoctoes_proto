
#include "AppDelegate.h"
#include "GameLayer.h"
#include "GameConfig.h"
#include "Localized.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
    Localized::purge();
    GameConfig::purge();
//    Analytics::purge();
//    AdsManager::purge();
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
    GameConfig::sharedInstance()->load();
    
    Localized::load();

    // create a scene. it's an autorelease object
    auto scene = GameLayer::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
