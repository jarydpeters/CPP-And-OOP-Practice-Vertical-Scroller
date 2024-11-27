#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

#include <map>
#include <SDL_ttf.h>

#include "assetFilePaths.h"
#include "colorDefines.h"
#include "globalValues.h"
#include "sdlUtility.h"
#include "settingsManager.h"
#include "textRenderer.h"
#include "textureRenderer.h"
#include "windowRenderer.h"

constexpr int FOUR_TIMES_SCALAR = 4;

constexpr int MAIN_MENU_LOGO_HORIZONTAL_SIZE = 130;
constexpr int MAIN_MENU_LOGO_VERTICAL_SIZE = 46;
constexpr int MAIN_MENU_LOGO_VERTICAL_OFFSET = 100;
constexpr int MAIN_MENU_LOGO_HORIZONTAL_OFFSET = ((MAIN_MENU_LOGO_HORIZONTAL_SIZE / 2) * FOUR_TIMES_SCALAR);

constexpr int MAIN_MENU_INDEX = 0;
constexpr int SETTINGS_MENU_INDEX = 1;

constexpr int MENU_SELECTION_ICON_VERTICAL_OFFSET = 6;

constexpr int CONTINUE_INDEX = 0;
constexpr int NEW_GAME_INDEX = 1;
constexpr int SETTINGS_INDEX = 2;
constexpr int EXIT_GAME_INDEX = 3;

constexpr int FULLSCREEN_INDEX = 0;
constexpr int RESOLUTION_INDEX = 1;
constexpr int MUSIC_VOLUME_INDEX = 2;
constexpr int SOUND_EFFECTS_VOLUME_INDEX = 3;
constexpr int RETURN_TO_MAIN_MENU_INDEX = 4;

class MenuRenderer : public WindowRenderer 
{
    public:

        /**
         * constructor
         */
        MenuRenderer(SDL_Window* win, SDL_Renderer* ren);

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

        //overloads setFullscreen from settingsManager.cpp
        void setFullscreen(const bool newFullscreen);

        virtual void renderCurrentlyDisplayedMenu(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) = 0;

        SDL_Texture* getMenuSelectionIconTexture();

        bool getFullscreen();

        int getCurrentlyDisplayedMenu();

    protected:

        SettingsManager settingsManager;
        TextureRenderer textureRenderer;

        SDL_Texture* menuSelectionIconTexture;
        SDL_Rect mainMenuSelectionRect;
        TextureRenderer::TextureWithRect menuSelectionIconTextureWithRect;

        SDL_Texture* mainMenuLogoTexture;
        SDL_Rect mainMenuLogoRect;
        TextureRenderer::TextureWithRect mainMenuLogoTextureWithRect;

        SDL_Window* menuScreenWindow;
        SDL_Renderer* menuScreenWindowRenderer;

        TTF_Font* menuTitleFont;
        TTF_Font* menuSubtitleFont;

        int currentlyDisplayedMenu = MAIN_MENU_INDEX;

        int currentlySelectedMainMenuOption = CONTINUE_INDEX;
        int currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;

        int menuTextFirstVerticalPosition;
        int menuTextSecondVerticalPosition;
        int menuTextThirdVerticalPosition;
        int menuTextFourthVerticalPosition;
        int menuTextFifthVerticalPosition;

        int menuTitleLogoVerticalPosition;
        int menuSelectionIconVerticalPosition;

        int currentHorizontalMousePosition;
        int currentVerticalMousePosition;

        int UISelectionMargin = 4;

        //fine tune hitbox of menu options
        int menuTextFirtVerticalUIUpperEdgePosition = menuTextFirstVerticalPosition - UISelectionMargin;
        int menuTextSecondVerticalUIUpperEdgePosition = menuTextSecondVerticalPosition - UISelectionMargin;
        int menuTextThirdVerticalUIUpperEdgePosition = menuTextThirdVerticalPosition - UISelectionMargin;
        int menuTextFourthVerticalUIUpperEdgePosition = menuTextFourthVerticalPosition - UISelectionMargin;
        int menuTextFifthVerticalUIUpperEdgePosition = menuTextFifthVerticalPosition - UISelectionMargin;

        int menuTextFirtVerticalUILowerEdgePosition = menuTextFirstVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
        int menuTextSecondVerticalUILowerEdgePosition = menuTextSecondVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
        int menuTextThirdVerticalUILowerEdgePosition = menuTextThirdVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
        int menuTextFourthVerticalUILowerEdgePosition = menuTextFourthVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
        int menuTextFifthVerticalUILowerEdgePosition = menuTextFifthVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;


        std::map<int, int> menuOptionsPositionMap = 
        {
            {0, menuTextFirstVerticalPosition},
            {1, menuTextSecondVerticalPosition},
            {2, menuTextThirdVerticalPosition},
            {3, menuTextFourthVerticalPosition},
            {4, menuTextFifthVerticalPosition}
        };

        /**
         * renders main menu logo sprite as well as main menu selection icon sprite
         * 
         * \returns void
         */
        void renderLogoAndMenuOptionSelectionSprites();

        /**
         * switches the currently displayed menu and the selected menu option
         * 
         * \param newMenu menu to switch display to
         * \param selectedMenuOption menu option to have selected upon entering the new menu
         * 
         * \return void
         */
        void setCurrentMenu(const int newMenu, const int selectedMenuOption);

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
         * manipulates menu based off of keystroke event
         *
         * \param event keystroke event to be acted upon
         * \returns void
         */
        virtual void evaluateKeystrokeEvent(const SDL_Event event) = 0;

        /**
         * manipulates menu based off of mouse motion event
         *
         * \returns void
         */
        virtual void evaluateMouseMotionEvent() = 0;

        /**
         * manipulates menu based off of mouse button event
         *
         * \param event mouse button event to be acted upon
         * \returns void
         */
        virtual void evaluateMouseButtonEvent(const SDL_Event event) = 0;

        /**
         * manipulates menu based off of mousewheel event
         *
         * \param event mousewheel event to be acted upon
         * \returns void
         */
        virtual void evaluateMouseWheelEvent(const SDL_Event event) = 0;

        virtual SDL_Window* getTitleScreenWindow() = 0;
        virtual void setTitleScreenWindow(SDL_Window* window) = 0;

        virtual SDL_Renderer* getTitleScreenRenderer() = 0;
        virtual void setTitleScreenRenderer(SDL_Renderer* renderer) = 0;

        virtual TTF_Font* getMenuTitleTextFont() = 0;
        virtual void setMenuTitleTextFont(TTF_Font* font) = 0;

        virtual TTF_Font* getMenuSubtitleTextFont() = 0;
        virtual void setMenuSubtitleTextFont(TTF_Font* font) = 0;
};

#endif //MENU_RENDERER_H