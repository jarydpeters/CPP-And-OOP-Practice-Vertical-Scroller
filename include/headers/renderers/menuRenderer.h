#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

#include <map>
#include <SDL_ttf.h>

#include "assetFilePaths.h"
#include "colorDefines.h"
#include "globalValues.h"
#include "settingsManager.h"
#include "textRenderer.h"
#include "textureRenderer.h"
#include "windowRenderer.h"

constexpr int FOUR_TIMES_SCALAR = 4;

constexpr int CONTINUE_INDEX = 0;
constexpr int NEW_GAME_INDEX = 1;
constexpr int SETTINGS_INDEX = 2;
constexpr int EXIT_GAME_INDEX = 3;

constexpr int FULLSCREEN_INDEX = 0;
constexpr int RESOLUTION_INDEX = 1;
constexpr int MUSIC_VOLUME_INDEX = 2;
constexpr int SOUND_EFFECTS_VOLUME_INDEX = 3;
constexpr int RETURN_TO_MAIN_MENU_INDEX = 4;

constexpr int MAIN_MENU_INDEX = 0;
constexpr int SETTINGS_MENU_INDEX = 1;

constexpr int MENU_SELECTION_ICON_VERTICAL_OFFSET = 6;

constexpr int MAIN_MENU_LOGO_HORIZONTAL_SIZE = 130;
constexpr int MAIN_MENU_LOGO_VERTICAL_SIZE = 46;
constexpr int MAIN_MENU_LOGO_VERTICAL_OFFSET = 100;
constexpr int MAIN_MENU_LOGO_HORIZONTAL_OFFSET = ((MAIN_MENU_LOGO_HORIZONTAL_SIZE / 2) * FOUR_TIMES_SCALAR);

class MenuRenderer : public WindowRenderer
{
    public:

        /**
         * constructor
         */
        MenuRenderer(SDL_Window* win, SDL_Renderer* ren);

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

        SDL_Window* getTitleScreenWindow();
        void setTitleScreenWindow(SDL_Window* window);

        SDL_Renderer* getTitleScreenRenderer();
        void setTitleScreenRenderer(SDL_Renderer* renderer);

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

        /**
         * destoys texture to prevent a memory leak
         * 
         * \returns void
         */
        void destroyTextures();

    private:

        SettingsManager settingsManager;
        TextureRenderer textureRenderer;

        SDL_Texture* menuSelectionIconTexture;
        SDL_Rect mainMenuSelectionRect;
        TextureRenderer::TextureWithRect menuSelectionIconTextureWithRect;

        SDL_Texture* mainMenuLogoTexture;
        SDL_Rect mainMenuLogoRect;
        TextureRenderer::TextureWithRect mainMenuLogoTextureWithRect;

        SDL_Window* titleScreenWindow;
        SDL_Renderer* titleScreenWindowRenderer;

        TTF_Font* menuTitleFont;
        TTF_Font* menuSubtitleFont;

        #define MAIN_MENU_CONTINUE_TEXT "CONTINUE"
        #define MAIN_MENU_NEW_GAME_TEXT "NEW GAME"
        #define MAIN_MENU_SETTINGS_TEXT "SETTINGS"
        #define MAIN_MENU_EXIT_TEXT "EXIT GAME"

        #define SETTINGS_MENU_TITLE_TEXT "SETTINGS"
        #define SETTINGS_MENU_FULLSCREEN_TEXT "FULL SCREEN"
        #define SETTINGS_MENU_RESOLUTION_TEXT "RESOLUTION"
        #define SETTINGS_MENU_MUSIC_VOLUME_TEXT "MUSIC VOLUME"
        #define SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT "SOUND EFFECTS VOLUME"
        #define SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT "RETURN TO MAIN MENU"

        #define SETTING_NOT_SELECTED_TEXT "[ ]"
        #define SETTING_SELECTED_TEXT "[X]"

        int currentlyDisplayedMenu = MAIN_MENU_INDEX;

        int currentlySelectedMainMenuOption = CONTINUE_INDEX;
        int currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;

        int menuTitleLogoVerticalPosition;
        int menuSelectionIconVerticalPosition;

        int menuTextFirstVerticalPosition;
        int menuTextSecondVerticalPosition;
        int menuTextThirdVerticalPosition;
        int menuTextFourthVerticalPosition;
        int menuTextFifthVerticalPosition;

        int currentHorizontalMousePosition;
        int currentVerticalMousePosition;

        std::string usersMonitorResolution;

        std::map<int, int> menuOptionsPositionMap = 
        {
            {0, menuTextFirstVerticalPosition},
            {1, menuTextSecondVerticalPosition},
            {2, menuTextThirdVerticalPosition},
            {3, menuTextFourthVerticalPosition},
            {4, menuTextFifthVerticalPosition}
        };

        std::map<int, const std::string> windowedResolutionSelectionMap =
        {
            {0, "< 1280 x  720 >"},
            {1, "< 1600 x  900 >"},
            {2, "< 1920 x 1080 >"},
        };

        std::map<int, const std::string> variableSettingSelectionMap = 
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
         * updates window size based off of new resolution
         * 
         * \returns void
         */
        void updateResolution();

        /**
         * renders main menu logo sprite as well as main menu selection icon sprite
         * 
         * \returns void
         */
        void renderLogoAndMenuOptionSelectionSprites();

        void setCurrentMenu(const int newMenu, const int selectedMenuOption);
};

#endif // MENU_RENDERER_H