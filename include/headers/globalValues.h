#ifndef GLOBAL_VALUES_H
#define GLOBAL_VALUES_H

#include <SDL.h>

constexpr int DEFAULT_HORIZONTAL_RESOLUTION = 1280;
constexpr int DEFAULT_VERTICAL_RESOLUTION = 720;

constexpr int TITLE_TEXT_POINT_SIZE = 48;
constexpr int SUBTITLE_TEXT_POINT_SIZE = 24;

constexpr int TITLE_MENU_SCREEN = 0;
constexpr int MAIN_GAME_SCREEN = 1;
constexpr int CUTSCENE_SCREEN = 2;
constexpr int UPGRADE_MENU_SCREEN = 3;

extern bool quitGame;

extern int currentHorizontalResolution;
extern int currentVerticalResolution;
extern int currentScreen;

#endif //GLOBAL_VALUES_H