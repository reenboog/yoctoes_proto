#include "GameConfig.h"
#include "Constants.h"
#include "Shared.h"
#include "Localized.h"

#include "rapidjson/document.h"
#include <string>

using namespace cocos2d;

GameConfig *GameConfig::__sharedInstance = nullptr;


GameConfig::~GameConfig() {
}

GameConfig::GameConfig() {
}

GameConfig *GameConfig::sharedInstance() {
    if (__sharedInstance == nullptr) {
        __sharedInstance = new GameConfig();
    }

    return __sharedInstance;
}

void GameConfig::purge() {
    delete __sharedInstance;
    __sharedInstance = nullptr;

    FileUtils::getInstance()->destroyInstance();
}

void GameConfig::load() {
    // rateBadgeWasAlreadyShown = UserDefault::getInstance()->getBoolForKey(kRateUsNotification, false);
}

void GameConfig::save() {
    // use user defaults here
    // UserDefault::getInstance()->setBoolForKey(kRateUsNotification, rateBadgeWasAlreadyShown);
}

void GameConfig::loadFilePaths() {
    // load file paths
    ssize_t configDataSize = 0;
    unsigned char *t = (FileUtils::getInstance()->getFileData("Res/config.json", "r", &configDataSize));

    char *configData = new char[configDataSize + 1];
    memcpy(configData, t, configDataSize);
    configData[configDataSize] = NULL;

    delete[] t;
    t = NULL;


    LanguageType currentLanguage = Application::getInstance()->getCurrentLanguage();

    string languagePrefix = Localized::languageShortNameForType(currentLanguage);

    auto addResourcePath = [=](const string &path) {
        FileUtils::getInstance()->addSearchPath((path + languagePrefix).c_str());
        FileUtils::getInstance()->addSearchPath(path.c_str());
    };

    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

    rapidjson::Document configDoc;
    configDoc.Parse<0>(configData);

    string layoutBaseDimensionType = configDoc["layoutBaseDimension"].GetString();

    float frameBaseDimension = frameSize.height;

    if (layoutBaseDimensionType.compare("width") == 0) {
        frameBaseDimension = frameSize.width;
    }

    const auto &designEntriesArray = configDoc["designResolutionEntries"];
    if (designEntriesArray.IsArray()) {
        for (int i = designEntriesArray.Size() - 1; i >= 0; --i) {
            const auto &currentDeviceEntry = designEntriesArray[i];

            if (currentDeviceEntry.IsObject()) {
                double currentResolutionBaseDimension = currentDeviceEntry[layoutBaseDimensionType.c_str()].GetDouble();

                if (frameBaseDimension > currentResolutionBaseDimension) {
                    int requiredEntryIndex = MIN(i + 1, designEntriesArray.Size() - 1);
                    const auto &requiredEntry = designEntriesArray[requiredEntryIndex];
                    double requiredBaseDimension = requiredEntry[layoutBaseDimensionType.c_str()].GetDouble();

                    //
                    double layoutWidth = requiredEntry["designWidth"].GetDouble();
                    double layoutHeight = requiredEntry["designHeight"].GetDouble();

                    this->setDesignLayoutSize({static_cast<float>(layoutWidth), static_cast<float>(layoutHeight)});

                    float designLayoutBaseDimension = layoutHeight;
                    ResolutionPolicy policy = ResolutionPolicy::FIXED_HEIGHT;

                    if (layoutBaseDimensionType.compare("width") == 0) {
                        designLayoutBaseDimension = layoutWidth;
                        //frameBaseDimension = frameSize.width;
                        policy = ResolutionPolicy::FIXED_WIDTH;
                    }

                    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(layoutWidth, layoutHeight, policy);
                    Director::getInstance()->setContentScaleFactor(requiredBaseDimension / designLayoutBaseDimension);

                    Size visibleSize = Director::getInstance()->getVisibleSize();
                    this->setVisibleOrigin({static_cast<float>((visibleSize.width - layoutWidth) / 2.0), static_cast<float>((visibleSize.height - layoutHeight) / 2.0)});
                    //

                    // load required entry and all the entries above
                    for (; requiredEntryIndex >= 0; --requiredEntryIndex) {
                        const auto &entryToLoad = designEntriesArray[requiredEntryIndex];

                        if (entryToLoad.IsObject()) {
                            for (auto it = entryToLoad["paths"].Begin(); it != entryToLoad["paths"].End(); ++it) {
                                string path = it->GetString();
                                addResourcePath(path);
                            }
                        }
                    }

                    // stop iterating all the rest entries
                    break;
                }
            }
        }
    }

    // load shared paths
    const auto &sharedPathsArray = configDoc["sharedPaths"];
    if (sharedPathsArray.IsArray()) {
        for (auto it = sharedPathsArray.Begin(); it != sharedPathsArray.End(); ++it) {
            string path = it->GetString();
            addResourcePath(path);
        }
    }

    delete[] configData;
}
