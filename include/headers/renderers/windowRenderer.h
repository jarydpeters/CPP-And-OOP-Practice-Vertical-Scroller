#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H

#include <map>
#include <SDL.h>
#include <string>
#include <vector>

#include "colorDefines.h"
#include "sdlUtility.h"
#include "settingsManager.h"
#include "textureRenderer.h"

constexpr int DEFAULT_HORIZONTAL_RESOLUTION = 1280;
constexpr int DEFAULT_VERTICAL_RESOLUTION = 720;

constexpr int TITLE_TEXT_POINT_SIZE = 48;
constexpr int SUBTITLE_TEXT_POINT_SIZE = 24;

constexpr int FOUR_TIMES_SCALAR = 4;

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

        static int getCurrentFPS();
        static void setCurrentFPS(const int newCurrentFPS);

        static void renderFPS(SDL_Renderer* renderer, TTF_Font* menuSubtitleFont);
        
        void renderScanLines(SDL_Renderer* renderer);

        TTF_Font* getMenuTitleTextFont();
        void setMenuTitleTextFont(TTF_Font* font);

        TTF_Font* getMenuSubtitleTextFont();
        void setMenuSubtitleTextFont(TTF_Font* font);

        // void destroyTextures();

    protected:

        TextureRenderer::TextureWithRect scanlinesTextureWithRect;
        SDL_Texture* scanlinesTexture;
        SDL_Rect scanlinesRect;

        SettingsManager settingsManager;
        TextureRenderer textureRenderer;

        SDL_Window* getWindow();
        void setWindow(SDL_Window* win);

        SDL_Renderer* getRenderer();
        void setRenderer(SDL_Renderer* ren);

        int getCurrentHorizontalResolution();
        void setCurrentHorizontalResolution(const int horizontalResolution);

        int getCurrentVerticalResolution();
        void setCurrentVerticalResolution(const int verticalResolution);

        std::string usersMonitorResolution;

        std::map<int, const std::string> windowedResolutionSelectionMap =
        {
            {0, "< 1280 x  720 >"},
            {1, "< 1600 x  900 >"},
            {2, "< 1920 x 1080 >"},
        };

        static int menuTitleLogoVerticalPosition;

    private:

        struct Resolution
        {
            int currentHorizontalResolution;
            int currentVerticalResolution;

            // Constructor with default arguments as well as 
            Resolution(int horizontalResolution = DEFAULT_HORIZONTAL_RESOLUTION, int verticalResolution = DEFAULT_VERTICAL_RESOLUTION)
                : currentHorizontalResolution(horizontalResolution), currentVerticalResolution(verticalResolution)
            {}
        };

        static int currentFPS;
        static Resolution resolution;

        TTF_Font* menuTitleFont;
        TTF_Font* menuSubtitleFont;
        
        SDL_Window* window;
        SDL_Renderer* renderer;
};

#endif // WINDOW_RENDERER_H