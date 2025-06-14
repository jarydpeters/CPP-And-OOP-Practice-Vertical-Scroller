#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

#include <array>

#include "assetFilePaths.h"
#include "colorDefines.h"
#include "textRenderer.h"
#include "windowRenderer.h"

constexpr int MAIN_MENU_LOGO_HORIZONTAL_SIZE = 130;
constexpr int MAIN_MENU_LOGO_VERTICAL_SIZE = 46;
constexpr int MAIN_MENU_LOGO_VERTICAL_OFFSET = 100;
constexpr int MAIN_MENU_LOGO_HORIZONTAL_OFFSET = ((MAIN_MENU_LOGO_HORIZONTAL_SIZE / 2) * FOUR_TIMES_SCALAR);

constexpr int MAIN_MENU_INDEX = 0;
constexpr int SETTINGS_MENU_INDEX = 1;

constexpr int MENU_SELECTION_ICON_VERTICAL_OFFSET = 6;

constexpr int MENU_OPTION_INITIAL_OFFSET = 150;
constexpr int MENU_OPTION_SUBSEQUENT_OFFSET = 50;

enum MainMenuIndex {
    CONTINUE_INDEX = 0,
    NEW_GAME_INDEX,
    SETTINGS_INDEX,
    EXIT_GAME_INDEX,
    NUMBER_OF_MAIN_MENU_OPTIONS
};

enum SettingsMenuIndex 
{
    FULLSCREEN_INDEX = 0,
    DISPLAY_FPS_INDEX,
    DISPLAY_CRT_SCANLINES_INDEX,
    RESOLUTION_INDEX,
    MUSIC_VOLUME_INDEX,
    SOUND_EFFECTS_VOLUME_INDEX,
    RETURN_TO_MAIN_MENU_INDEX,
    NUMBER_OF_SETTINGS_OPTIONS
};

constexpr int NUMBER_OF_ALLOCATED_MENU_OPTIONS = 10;

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

        /**
         * adjusts UI positions for new resolution
         * 
         * \returns void
         */
        virtual void updateUIPositions() = 0;

    protected:

        std::array<int, NUMBER_OF_ALLOCATED_MENU_OPTIONS> menuOptionsVerticalPositions;
        std::array<int, NUMBER_OF_ALLOCATED_MENU_OPTIONS> menuTextVerticalUIUpperEdgePositions;
        std::array<int, NUMBER_OF_ALLOCATED_MENU_OPTIONS> menuTextVerticalUILowerEdgePositions;

        SDL_Texture* menuSelectionIconTexture;
        SDL_Rect menuSelectionIconRect;
        TextureRenderer::TextureWithRect menuSelectionIconTextureWithRect;

        SDL_Texture* mainMenuLogoTexture;
        SDL_Rect mainMenuLogoRect;
        TextureRenderer::TextureWithRect menuLogoTextureWithRect;

        int menuSelectionIconVerticalPosition;

        int currentHorizontalMousePosition;
        int currentVerticalMousePosition;

        int UISelectionMargin = 4;

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

        /**
         * 
         */
        int getCurrentMenuOption();


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
        void renderMainMenuLogo();

        /**
         * renders white bar menu selection icon on main/settings menu
         * 
         * \returns void
         */
        void renderMenuOptionSelectionSprite();

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

        /**
         * moves forward one menu option
         */
        virtual void advanceToNextMenuOption() = 0;
        
        /**
         * moves back one menu option
         */
        virtual void returnToPreviousMenuOption() = 0;

    private:

        static int currentlySelectedMenuOption;
};

#endif //MENU_RENDERER_H