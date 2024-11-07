//TODO MAKE MENURENDERER INHERIT FROM A NEW WINDOWRENDERER

#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "assetFilePaths.h"
#include "colorDefines.h"
#include "commonDefines.h"
#include "textRenderer.h"
#include "textureRenderer.h"

constexpr int MENU_TITLE_TEXT_VERTICAL_POSITION = 200;
constexpr int MENU_TEXT_FIRST_VERTICAL_POSITION = MENU_TITLE_TEXT_VERTICAL_POSITION + 100;
constexpr int MENU_TEXT_SECOND_VERTICAL_POSITION = MENU_TEXT_FIRST_VERTICAL_POSITION + 50;
constexpr int MENU_TEXT_THIRD_VERTICAL_POSITION = MENU_TEXT_SECOND_VERTICAL_POSITION + 50;
constexpr int MENU_TEXT_FOURTH_VERTICAL_POSITION = MENU_TEXT_THIRD_VERTICAL_POSITION + 50;

constexpr int CONTINUE_INDEX = 0;
constexpr int NEW_GAME_INDEX = 1;
constexpr int SETTINGS_INDEX = 2;
constexpr int EXIT_GAME_INDEX = 3;

constexpr int FULLSCREEN_INDEX = 0;
constexpr int MUSIC_VOLUME_INDEX = 1;
constexpr int SOUND_EFFECTS_VOLUME_INDEX = 2;
constexpr int RETURN_TO_MAIN_MENU_INDEX = 3;

constexpr int MAIN_MENU_INDEX = 0;
constexpr int SETTINGS_MENU_INDEX = 1;

class MenuRenderer
{
    #define MAIN_MENU_TITLE_TEXT "VERT SCROLLER"
    #define MAIN_MENU_CONTINUE_TEXT "CONTINUE"
    #define MAIN_MENU_NEW_GAME_TEXT "NEW GAME"
    #define MAIN_MENU_SETTINGS_TEXT "SETTINGS"
    #define MAIN_MENU_EXIT_TEXT "QUIT"

    #define SETTINGS_MENU_TITLE_TEXT "SETTINGS"
    #define SETTINGS_MENU_FULLSCREEN_TEXT "FULL SCREEN"
    #define SETTINGS_MENU_MUSIC_VOLUME_TEXT "MUSIC VOLUME"
    #define SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT "SOUND EFFECTS VOLUME"
    #define SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT "RETURN TO MAIN MENU"

    #define SETTING_NOT_SELECTED_TEXT "[ ]"
    #define SETTING_SELECTED_TEXT "[X]"

    public:

        bool fullscreen = false;
        bool quitGame = false;

        int currentlyDisplayedMenu = MAIN_MENU_INDEX;

        int currentlySelectedMainMenuOption = CONTINUE_INDEX;
        int currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;

        int currentHorizontalResolution = DEFAULT_HORIZONTAL_RESOLUTION;
        int currentVerticalResolution = DEFAULT_VERTICAL_RESOLUTION;

        std::map<int, int> menuOptionsPositionMap;

        TextureRenderer textureRenderer;

        TextureRenderer::TextureWithRect menuSelectionTextureWithRect;

        SDL_Texture* mainMenuSelectionTexture;
        SDL_Rect mainMenuSelectionRect;

        SDL_Window* mainWindow;
        SDL_Renderer* mainWindowRenderer;

        TTF_Font* menuTextPixelFont;
        TTF_Font* subtextPixelFont;

        MenuRenderer();

        /**
         * 
         *
         * \param 
         * \returns 
         */
        void initializeMenuOptionsMaps();

        /**
         * 
         *
         * \param 
         * \returns 
         */
        void renderCurrentlyDisplayedMenu(int currentlyDisplayedMenu, TextRenderer menuTextRenderer, TextRenderer menuSubtextRenderer);

        /**
         * 
         *
         * \param 
         * \returns 
         */
        void executeMenuActionBasedOnEvent(SDL_Event event);
};

#endif // MENU_RENDERER_H