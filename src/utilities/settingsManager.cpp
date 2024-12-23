#include "settingsManager.h"

int SettingsManager::currentWindowedResolutionSetting;
int SettingsManager::currentMusicVolumeSetting;
int SettingsManager::currentSoundEffectVolumeSetting;

bool SettingsManager::fullscreen;
bool SettingsManager::displayFPS;
bool SettingsManager::displayCRTScanlines;

SettingsManager::SettingsManager()
{

}

void SettingsManager::saveSettings()
{
    std::ofstream outFile(settingsFilePath);
    if(outFile.is_open())
    {
        outFile << "full screen: " << fullscreen << std::endl;
        outFile << "display FPS: " << displayFPS << std::endl;
        outFile << "display CRT scanlines: " << displayCRTScanlines << std::endl;
        outFile << "resolution: " << currentWindowedResolutionSetting << std::endl;
        outFile << "music volume: " << currentMusicVolumeSetting << std::endl;
        outFile << "sound effects volume: " << currentSoundEffectVolumeSetting << std::endl;
        
        outFile.close();
    }
    else
    {
        printf("Unable to open file!");
    }
}

void SettingsManager::loadSavedSettings()
{
    std::ifstream inFile(settingsFilePath);
    if(inFile.is_open())
    {
        std::string line;

        // Read the file line by line
        while(std::getline(inFile, line))
        {
            std::stringstream stringStream(line);
            std::string settingName;
            std::string settingValue;

            // Get the setting name (before the colon)
            if(std::getline(stringStream, settingName, ':'))
            {
                // Trim leading/trailing spaces from the setting name and value
                settingName.erase(0, settingName.find_first_not_of(" \t"));
                settingName.erase(settingName.find_last_not_of(" \t") + 1);

                // Get the setting value (after the colon)
                if(std::getline(stringStream, settingValue))
                {
                    // trim leading space
                    settingValue.erase(0, settingValue.find_first_not_of(" \t"));

                    // Compare the setting name and assign the value
                    if(settingName == "full screen")
                    {
                        fullscreen = std::stoi(settingValue);
                    }
                    else if(settingName == "display FPS")
                    {
                        displayFPS = std::stoi(settingValue);
                    }
                    else if(settingName == "display CRT scanlines")
                    {
                        displayCRTScanlines = std::stoi(settingValue);
                    }
                    else if(settingName == "resolution")
                    {
                        currentWindowedResolutionSetting = std::stoi(settingValue);
                    }
                    else if(settingName == "music volume")
                    {
                        currentMusicVolumeSetting = std::stoi(settingValue);
                    }
                    else if(settingName == "sound effects volume")
                    {
                        currentSoundEffectVolumeSetting = std::stoi(settingValue);
                    }
                }
            }
        }
        inFile.close();
    }
    else
    {
        printf("Unable to open file!");
    }
}

int SettingsManager::getCurrentWindowedResolutionSetting()
{
    return currentWindowedResolutionSetting;
}

void SettingsManager::setCurrentWindowedResolutionSetting(const int newWindowedResolution)
{
    currentWindowedResolutionSetting = newWindowedResolution;

    if(getCurrentWindowedResolutionSetting() < 0)
    {
        setCurrentWindowedResolutionSetting(2);
    }
    else if(getCurrentWindowedResolutionSetting() > 2)
    {
        setCurrentWindowedResolutionSetting(0);
    }
}

int SettingsManager::getCurrentMusicVolumeSetting()
{
    return currentMusicVolumeSetting;
}

void SettingsManager::setCurrentMusicVolumeSetting(const int newMusicVolumeSetting)
{
    currentMusicVolumeSetting = newMusicVolumeSetting;
}

int SettingsManager::getCurrentSoundEffectVolumeSetting()
{
    return currentSoundEffectVolumeSetting;
}

void SettingsManager::setCurrentSoundEffectVolumeSetting(const int newSoundEffectVolumeSetting)
{
    currentSoundEffectVolumeSetting = newSoundEffectVolumeSetting;
}

bool SettingsManager::getFullscreen()
{
    return fullscreen;
}

void SettingsManager::setFullscreen(const bool newFullscreen)
{
    fullscreen = newFullscreen;
}

bool SettingsManager::getDisplayFPS()
{
    return displayFPS;
}

void SettingsManager::setDisplayFPS(const bool newDisplayFPS)
{
    displayFPS = newDisplayFPS;
}

bool SettingsManager::getDisplayCRTScanlines()
{
    return displayCRTScanlines;
}

void SettingsManager::setDisplayCRTScanlines(const bool newCRTScanlines)
{
    displayCRTScanlines = newCRTScanlines;
}