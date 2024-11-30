#include "globalValues.h"

bool quitGame = false;

int currentHorizontalResolution = DEFAULT_HORIZONTAL_RESOLUTION;
int currentVerticalResolution = DEFAULT_VERTICAL_RESOLUTION;
int currentScreen = MAIN_MENU_SCREEN;

int menuTitleLogoVerticalPosition = currentVerticalResolution / 3.0;

int menuTextFirstVerticalPosition = menuTitleLogoVerticalPosition + (150);
int menuTextSecondVerticalPosition = menuTextFirstVerticalPosition + (50);
int menuTextThirdVerticalPosition = menuTextSecondVerticalPosition + (50);
int menuTextFourthVerticalPosition = menuTextThirdVerticalPosition + (50);
int menuTextFifthVerticalPosition = menuTextFourthVerticalPosition + (50);

std::map<int, int> menuOptionsPositionMap = 
{
    {0, menuTextFirstVerticalPosition},
    {1, menuTextSecondVerticalPosition},
    {2, menuTextThirdVerticalPosition},
    {3, menuTextFourthVerticalPosition},
    {4, menuTextFifthVerticalPosition}
};