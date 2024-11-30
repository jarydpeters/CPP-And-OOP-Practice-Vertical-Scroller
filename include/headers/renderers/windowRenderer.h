#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H

#include <map>
#include <SDL.h>
#include <string>
#include <vector>

#include "colorDefines.h"

constexpr int DEFAULT_HORIZONTAL_RESOLUTION = 1280;
constexpr int DEFAULT_VERTICAL_RESOLUTION = 720;

constexpr int TITLE_TEXT_POINT_SIZE = 48;
constexpr int SUBTITLE_TEXT_POINT_SIZE = 24;

class WindowRenderer
{
    public:

        enum ScreenType 
        {
            MAIN_MENU_SCREEN,
            SETTINGS_MENU_SCREEN,
            MAIN_GAME_SCREEN,
            CUTSCENE_SCREEN,
            UPGRADE_MENU_SCREEN,
            NUMBER_OF_SCREEN_TYPES
        };

        static bool quitGame;
        static int currentScreen;

        /**
         * 
         */
        WindowRenderer(SDL_Window* win, SDL_Renderer* ren);

        static bool getDisplayFPS();
        static void setDisplayFPS(const bool newDisplayFPS);

        static int getCurrentFPS();
        static void setCurrentFPS(const int newCurrentFPS);

        static void renderFPS(SDL_Renderer* renderer, TTF_Font* menuSubtitleFont);

        TTF_Font* getMenuTitleTextFont();
        void setMenuTitleTextFont(TTF_Font* font);

        TTF_Font* getMenuSubtitleTextFont();
        void setMenuSubtitleTextFont(TTF_Font* font);

    protected:

        SDL_Window* getWindow();
        void setWindow(SDL_Window* win);

        SDL_Renderer* getRenderer();
        void setRenderer(SDL_Renderer* ren);

        std::string usersMonitorResolution;

        struct Resolution
        {
            int currentHorizontalResolution;
            int currentVerticalResolution;

            // Constructor with default arguments as well as 
            Resolution(int horizontalResolution = DEFAULT_HORIZONTAL_RESOLUTION, int verticalResolution = DEFAULT_VERTICAL_RESOLUTION)
                : currentHorizontalResolution(horizontalResolution), currentVerticalResolution(verticalResolution)
            {}
        };

        Resolution resolution;

        std::map<int, const std::string> windowedResolutionSelectionMap =
        {
            {0, "< 1280 x  720 >"},
            {1, "< 1600 x  900 >"},
            {2, "< 1920 x 1080 >"},
        };

        int menuTitleLogoVerticalPosition;

        int menuTextFirstVerticalPosition;
        int menuTextSecondVerticalPosition;
        int menuTextThirdVerticalPosition;
        int menuTextFourthVerticalPosition;
        int menuTextFifthVerticalPosition;

        std::vector<int> menuOptionsPositionVector = 
        {
            menuTextFirstVerticalPosition,
            menuTextSecondVerticalPosition,
            menuTextThirdVerticalPosition,
            menuTextFourthVerticalPosition,
            menuTextFifthVerticalPosition
        };

    private:

        //TODO: MAKE SETTING
        static bool displayFPS;
        static int currentFPS;

        TTF_Font* menuTitleFont;
        TTF_Font* menuSubtitleFont;
        
        SDL_Window* window;
        SDL_Renderer* renderer;

};

#endif // WINDOW_RENDERER_H