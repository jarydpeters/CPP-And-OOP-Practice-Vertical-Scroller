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

//fine tune hitbox of menu options
constexpr int HEIGHT_OF_MENU_OPTION_TEXT = SUBTITLE_TEXT_POINT_SIZE - 8;

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
    public:

        bool fullscreen = false;
        bool quitGame = false;

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

        /**
         * controls menu operations based off of user's mouse and key actions
         *
         * \param event mouse or key event to be evaluated and acted upon
         * \returns void
         */
        void executeMenuActionBasedOnEvent(const SDL_Event event);

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
         * toggles fullscreen and adjusts UI positions to keep proportions even
         * 
         * \returns void
         */
        void toggleFullScreen();

        /**
         * getter for currentlyDisplayedMenu
         *
         * \returns currentlyDisplayedMenu
         */
        int getCurrentlyDisplayedMenu();

        /**
         * setter for currently displayed menu
         * 
         * \param newMenu new menu to be displayed
         * \param selectedMenuOption which menu option is to be selected upon showing the new menu
         * \returns void
         */
        void setCurrentMenu(const int newMenu, const int selectedMenuOption);

        /**
         * getter for mainWindow
         *
         * \returns mainWindow
         */
        SDL_Window* getMainWindow();

        /**
         * setter for mainWindow
         *
         * \param window new window to be set
         * \returns void
         */
        void setMainWindow(SDL_Window* window);

        /**
         * getter for mainWindowRenderer
         *
         * \returns mainWindowRenderer
         */
        SDL_Renderer* getMainWindowRenderer();

        /**
         * setter for mainWindowRenderer
         *
         * \param renderer new renderer to be set
         * \returns void
         */
        void setMainWindowRenderer(SDL_Renderer* renderer);

        /**
         * getter for menuTitleFont
         *
         * \returns menuTitleFont
         */
        TTF_Font* getMenuTitleTextFont();

        /**
         * setter for menuTitleFont
         *
         * \param new new menuTitleFont to be set
         */
        void setMenuTitleTextFont(TTF_Font* font);

        /**
         * getter for menuSubtitleFont
         *
         * \returns menuSubtitleFont
         */
        TTF_Font* getMenuSubtitleTextFont();
        
        /**
         * setter for menuSubtitleFont
         *
         * \param menuSubtitleFont new font to be set
         */
        void setMenuSubtitleTextFont(TTF_Font* font);

        /**
         * getter for getMenuSelectionIconTexture
         *
         * \returns getMenuSelectionIconTexture
         */
        SDL_Texture* getMenuSelectionIconTexture();

    private:

        TextureRenderer textureRenderer;

        SDL_Texture* menuSelectionIconTexture;
        TextureRenderer::TextureWithRect menuSelectionIconTextureWithRect;

        SDL_Rect mainMenuSelectionRect;

        SDL_Window* mainWindow;
        SDL_Renderer* mainWindowRenderer;

        TTF_Font* menuTitleFont;
        TTF_Font* menuSubtitleFont;

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
        
        int currentHorizontalResolution = DEFAULT_HORIZONTAL_RESOLUTION;
        int currentVerticalResolution = DEFAULT_VERTICAL_RESOLUTION;

        int menuTitleTextVerticalPosition = currentVerticalResolution / 3.0;
        int menuTextFirstVerticalPosition = menuTitleTextVerticalPosition + 100;
        int menuTextSecondVerticalPosition = menuTextFirstVerticalPosition + 50;
        int menuTextThirdVerticalPosition = menuTextSecondVerticalPosition + 50;
        int menuTextFourthVerticalPosition = menuTextThirdVerticalPosition + 50;

        int currentlyDisplayedMenu = MAIN_MENU_INDEX;

        int currentlySelectedMainMenuOption = CONTINUE_INDEX;
        int currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;

        int horizontalMousePosition;
        int verticalMousePosition;

        std::map<int, int> menuOptionsPositionMap = 
        {
            {0, menuTextFirstVerticalPosition},
            {1, menuTextSecondVerticalPosition},
            {2, menuTextThirdVerticalPosition},
            {3, menuTextFourthVerticalPosition}
        };
};

#endif // MENU_RENDERER_H