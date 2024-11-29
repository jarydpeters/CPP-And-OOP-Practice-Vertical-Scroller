#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

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

        virtual void renderCurrentScreen(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) = 0;

        SDL_Texture* getMenuSelectionIconTexture();

        bool getFullscreen();

        int getcurrentScreen();

        SDL_Window* getTitleScreenWindow();
        void setTitleScreenWindow(SDL_Window* window);

        SDL_Renderer* getTitleScreenRenderer();
        void setTitleScreenRenderer(SDL_Renderer* renderer);

        TTF_Font* getMenuTitleTextFont();
        void setMenuTitleTextFont(TTF_Font* font);

        TTF_Font* getMenuSubtitleTextFont();
        void setMenuSubtitleTextFont(TTF_Font* font);

    protected:

        SettingsManager settingsManager;
        TextureRenderer textureRenderer;

        SDL_Texture* menuSelectionIconTexture;
        SDL_Rect menuSelectionIconRect;
        TextureRenderer::TextureWithRect menuSelectionIconTextureWithRect;

        SDL_Texture* mainMenuLogoTexture;
        SDL_Rect mainMenuLogoRect;
        TextureRenderer::TextureWithRect menuLogoTextureWithRect;

        SDL_Window* menuScreenWindow;
        SDL_Renderer* menuScreenWindowRenderer;

        TTF_Font* menuTitleFont;
        TTF_Font* menuSubtitleFont;

        int menuSelectionIconVerticalPosition;

        int currentHorizontalMousePosition;
        int currentVerticalMousePosition;

        int UISelectionMargin = 4;

        //fine tune hitbox of menu options
        int menuTextFirstVerticalUIUpperEdgePosition;
        int menuTextSecondVerticalUIUpperEdgePosition;
        int menuTextThirdVerticalUIUpperEdgePosition;
        int menuTextFourthVerticalUIUpperEdgePosition;
        int menuTextFifthVerticalUIUpperEdgePosition;

        int menuTextFirstVerticalUILowerEdgePosition;
        int menuTextSecondVerticalUILowerEdgePosition;
        int menuTextThirdVerticalUILowerEdgePosition;
        int menuTextFourthVerticalUILowerEdgePosition;
        int menuTextFifthVerticalUILowerEdgePosition;

        /**
         * switches the currently displayed menu and the selected menu option
         * 
         * \param newMenu menu to switch display to
         * 
         * \return void
         */
        void setCurrentMenu(const int newMenu);

        /**
         * switches the currently displayed menu and the selected menu option
         * 
         * \param selectedMenuOption menu option to have selected upon entering the new menu
         * 
         * \return void
         */
        void setCurrentMenuOption(const int selectedMenuOption);

        int getCurrentMenuOption();

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
         * renders Red Ball Express logo at top of main/settings menu
         * 
         * \returns void
         */
        void RenderMainMenuLogo();

        /**
         * renders white bar menu selection icon on main/settings menu
         * 
         * \returns void
         */
        void RenderMenuOptionSelectionSprite();

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

    private:

        int currentlySelectedMenuOption = CONTINUE_INDEX;
};

#endif //MENU_RENDERER_H