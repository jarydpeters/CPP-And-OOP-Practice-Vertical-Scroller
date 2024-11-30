#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <filesystem>
#include <fstream>
#include <iostream>

#include "assetFilePaths.h"

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

    private:

        int currentWindowedResolutionSetting;
        int currentMusicVolumeSetting;
        int currentSoundEffectVolumeSetting;

        bool fullscreen;
};


#endif //SETTINGS_MANAGER_H