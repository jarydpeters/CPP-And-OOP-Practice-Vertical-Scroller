#ifndef GLOBAL_VALUES_H
#define GLOBAL_VALUES_H

#include <SDL.h>

//TODO: MAKE GAME ENGINE FRAMERATE INDEPENDENT
//TODO: MAKE DYNAMIC TARGET THAT CAN BE CHANGED IN SETTINGS
constexpr double MILLISECONDS_PER_SECOND = 1000;
constexpr double TARGET_FRAMES_PER_SECOND = 60;
constexpr double FRAME_DELAY = MILLISECONDS_PER_SECOND / TARGET_FRAMES_PER_SECOND;

constexpr int DEFAULT_HORIZONTAL_RESOLUTION = 1280;
constexpr int DEFAULT_VERTICAL_RESOLUTION = 720;

constexpr int TITLE_TEXT_POINT_SIZE = 48;
constexpr int SUBTITLE_TEXT_POINT_SIZE = 24;

constexpr int MAIN_MENU_SCREEN = 0;
constexpr int SETTINGS_MENU_SCREEN = 1;
constexpr int MAIN_GAME_SCREEN = 2;
constexpr int CUTSCENE_SCREEN = 3;
constexpr int UPGRADE_MENU_SCREEN = 4;

extern bool quitGame;

extern int currentHorizontalResolution;
extern int currentVerticalResolution;
extern int currentScreen;

#endif //GLOBAL_VALUES_H