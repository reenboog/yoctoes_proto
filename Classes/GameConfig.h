#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include "cocos2d.h"

class GameConfig {
public:
    ~GameConfig();

    void load();
    void save();

    cocos2d::Size getDesignLayoutSize();
    cocos2d::Point getVisibleOrigin();

    bool areRemoteNotificationsEnabled();
    void setRemoteNotificationsEnabled(bool enabled);

    bool isAppAlreadyRated();
    void setAppRated(bool rated);

    bool wasRateBadgeAlreadyShown();
    void setRateBadgeAlreadyShown(bool shown);

    void setMusicVolume(float volume);
    float getMusicVolume();

    void setSoundVolume(float volume);
    float getSoundVolume();

    void setCurrentLanguageType(int type);
    int getCurrentLanguageType();

//    void loadFilePaths();

    static GameConfig *sharedInstance();

    static void purge();

private:
    static GameConfig *sharedInstance_;

    GameConfig();

    void setDesignLayoutSize(const cocos2d::Size &size);
    void setVisibleOrigin(const cocos2d::Point &point);

    cocos2d::Point visibleOrigin_;
    cocos2d::Size designLayoutSize_;

    bool rateBadgeWasAlreadyShown_;
    bool remoteNotificationsEnabled_;
    bool appWasRated_;

    float soundVolume_;
    float musicVolume_;

    int currentLanguageType_;
};

inline bool GameConfig::areRemoteNotificationsEnabled() {
    return remoteNotificationsEnabled_;
}

inline void GameConfig::setRemoteNotificationsEnabled(bool enabled) {
    remoteNotificationsEnabled_ = enabled;
}

inline bool GameConfig::isAppAlreadyRated() {
    return appWasRated_;
}

inline void GameConfig::setAppRated(bool rated) {
    appWasRated_ = rated;
}

inline bool GameConfig::wasRateBadgeAlreadyShown() {
    return rateBadgeWasAlreadyShown_;
}

inline void GameConfig::setRateBadgeAlreadyShown(bool shown) {
    rateBadgeWasAlreadyShown_ = shown;
}

inline float GameConfig::getMusicVolume() {
    return musicVolume_;
}

inline void GameConfig::setMusicVolume(float volume) {
    musicVolume_ = volume;
}

inline float GameConfig::getSoundVolume() {
    return soundVolume_;
}

inline void GameConfig::setSoundVolume(float volume) {
    soundVolume_ = volume;
}

inline int GameConfig::getCurrentLanguageType() {
    return currentLanguageType_;
}

inline void GameConfig::setCurrentLanguageType(int type) {
    currentLanguageType_ = type;
}

inline cocos2d::Size GameConfig::getDesignLayoutSize() {
    return designLayoutSize_;
}

inline void GameConfig::setDesignLayoutSize(const cocos2d::Size &size) {
    designLayoutSize_ = size;
}

inline cocos2d::Point GameConfig::getVisibleOrigin() {
    return visibleOrigin_;
}

inline void GameConfig::setVisibleOrigin(const cocos2d::Point &point) {
    visibleOrigin_ = point;
}

#endif // __GAME_CONFIG_H__
