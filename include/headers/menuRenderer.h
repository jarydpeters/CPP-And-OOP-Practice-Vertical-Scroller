//TODO MAKE MENURENDERER INHERIT FROM A NEW WINDOWRENDERER

#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <SDL_ttf.h>
#include <string>

#include "assetFilePaths.h"
#include "colorDefines.h"
#include "globalValues.h"
#include "textRenderer.h"
#include "textureRenderer.h"

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

constexpr int menuSelectionIconVerticalOffset = 6;

constexpr int mainMenuLogoVerticalOffset = 100;
constexpr int mainMenuLogoHorizontalOffset = 210;

class MenuRenderer
{
    public:

        const std::string settingsFilePath = "settings/settings.txt";

        /**
         * default constructor
         */
        MenuRenderer();

        /**
         * renders currently displayed menu based off of currentlyDisplayedMenu parameter
         *
         * \param currentlyDisplayedMenu menu to be displayed
         * \param menuTitleTextRenderer text renderer for menu title text
         * \param menuSubtextRenderer text renderer for menu subtitle text
         * \returns void
         */
        void renderCurrentlyDisplayedMenu(const int currentlyDisplayedMenu, TextRenderer menuTitleTextRenderer, TextRenderer menuSubtextRenderer);

        int getCurrentlyDisplayedMenu();

        SDL_Window* getTitleScreensWindow();
        void setTitleScreensWindow(SDL_Window* window);

        SDL_Renderer* getTitleScreensRenderer();
        void setTitleScreensRenderer(SDL_Renderer* renderer);

        TTF_Font* getMenuTitleTextFont();
        void setMenuTitleTextFont(TTF_Font* font);

        TTF_Font* getMenuSubtitleTextFont();
        void setMenuSubtitleTextFont(TTF_Font* font);

        SDL_Texture* getMenuSelectionIconTexture();

        bool getFullscreen();
        void setFullscreen(const bool newFullscreen);

        /**
         * controls menu operations based off of user's mouse and key actions
         *
         * \param event mouse or key event to be evaluated and acted upon
         * \returns void
         */
        void executeMenuActionBasedOnEvent(const SDL_Event event);

    private:

        TextureRenderer textureRenderer;

        SDL_Texture* menuSelectionIconTexture;
        SDL_Rect mainMenuSelectionRect;
        TextureRenderer::TextureWithRect menuSelectionIconTextureWithRect;

        SDL_Texture* mainMenuLogoTexture;
        SDL_Rect mainMenuLogoRect;
        TextureRenderer::TextureWithRect mainMenuLogoTextureWithRect;

        SDL_Window* titleScreensWindow;
        SDL_Renderer* titleScreensWindowRenderer;

        TTF_Font* menuTitleFont;
        TTF_Font* menuSubtitleFont;

        #define MAIN_MENU_CONTINUE_TEXT "CONTINUE"
        #define MAIN_MENU_NEW_GAME_TEXT "NEW GAME"
        #define MAIN_MENU_SETTINGS_TEXT "SETTINGS"
        #define MAIN_MENU_EXIT_TEXT "EXIT GAME"

        #define SETTINGS_MENU_TITLE_TEXT "SETTINGS"
        #define SETTINGS_MENU_FULLSCREEN_TEXT "FULL SCREEN"
        #define SETTINGS_MENU_MUSIC_VOLUME_TEXT "MUSIC VOLUME"
        #define SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT "SOUND EFFECTS VOLUME"
        #define SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT "RETURN TO MAIN MENU"

        #define SETTING_NOT_SELECTED_TEXT "[ ]"
        #define SETTING_SELECTED_TEXT "[X]"

        int currentlyDisplayedMenu = MAIN_MENU_INDEX;

        int currentlySelectedMainMenuOption = CONTINUE_INDEX;
        int currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;

        int menuTitleLogoVerticalPosition;

        int menuTextFirstVerticalPosition;
        int menuTextSecondVerticalPosition;
        int menuTextThirdVerticalPosition;
        int menuTextFourthVerticalPosition;

        int currentHorizontalMousePosition;
        int currentVerticalMousePosition;

        int currentMusicVolumeSetting;
        int currentSoundEffectVolumeSetting;

        bool fullscreen = false;

        std::map<int, int> menuOptionsPositionMap = 
        {
            {0, menuTextFirstVerticalPosition},
            {1, menuTextSecondVerticalPosition},
            {2, menuTextThirdVerticalPosition},
            {3, menuTextFourthVerticalPosition}
        };

        std::map<int, const char*> variableSettingSelectionMap = 
        {
            {0,  ".........."},
            {1,  "|........."},
            {2,  "||........"},
            {3,  "|||......."},
            {4,  "||||......"},
            {5,  "|||||....."},
            {6,  "||||||...."},
            {7,  "|||||||..."},
            {8,  "||||||||.."},
            {9,  "|||||||||."},
            {10, "||||||||||"}
        };

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

        /**
         * manipulates menu based off of keystroke event
         *
         * \param event keystroke event to be acted upon
         * \returns void
         */
        void evaluateKeystrokeEvent(const SDL_Event event);

        /**
         * manipulates menu based off of mouse motion event
         *
         * \returns void
         */
        void evaluteMouseMotionEvent();

        /**
         * manipulates menu based off of mouse button event
         *
         * \param event mouse button event to be acted upon
         * \returns void
         */
        void evaluteMouseButtonEvent(const SDL_Event event);

        /**
         * manipulates menu based off of mousewheel event
         *
         * \param event mousewheel event to be acted upon
         * \returns void
         */
        void evaluteMouseWheelEvent(const SDL_Event event);

        /**
         * adjusts UI positions for new resolution
         * 
         * \returns void
         */
        void updateUIPositions();

        /**
         * renders main menu logo sprite as well as main menu selection icon sprite
         * 
         * \returns void
         */
        void renderLogoAndMenuOptionSelectionSprites();

        void setCurrentMenu(const int newMenu, const int selectedMenuOption);
};

#endif // MENU_RENDERER_H