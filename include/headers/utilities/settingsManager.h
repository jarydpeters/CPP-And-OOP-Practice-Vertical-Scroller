#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <filesystem>
#include <fstream>
#include <iostream>

#include "assetFilePaths.h"

//TODO: MAKE GAME ENGINE FRAMERATE INDEPENDENT
//TODO: MAKE DYNAMIC TARGET THAT CAN BE CHANGED IN SETTINGS
constexpr double MILLISECONDS_PER_SECOND = 1000;
constexpr double TARGET_FRAMES_PER_SECOND = 60;
constexpr double FRAME_DELAY = MILLISECONDS_PER_SECOND / TARGET_FRAMES_PER_SECOND;

class SettingsManager
{
    public:

        /**
         * constructor
         */
        SettingsManager();

        /**
         * saves user's selected settings
         *
         * \returns void
         */
        void saveSettings();

        /**
         * loads user's previously selected settings
         *
         * \returns void
         */
        void loadSavedSettings();

        int getCurrentWindowedResolutionSetting();
        void setCurrentWindowedResolutionSetting(const int newWindowedResolution);

        int getCurrentMusicVolumeSetting();
        void setCurrentMusicVolumeSetting(const int newMusicVolumeSetting);

        int getCurrentSoundEffectVolumeSetting();
        void setCurrentSoundEffectVolumeSetting(const int newSoundEffectVolumeSetting);

        bool getFullscreen();
        void setFullscreen(const bool newFullscreen);

        bool getDisplayFPS();
        void setDisplayFPS(const bool newDisplayFPS);

        bool getDisplayCRTScanlines();
        void setDisplayCRTScanlines(const bool newCRTScanlines);

    private:

        static int currentWindowedResolutionSetting;
        static int currentMusicVolumeSetting;
        static int currentSoundEffectVolumeSetting;

        static bool fullscreen;
        static bool displayFPS;
        static bool displayCRTScanlines;
};


#endif //SETTINGS_MANAGER_H