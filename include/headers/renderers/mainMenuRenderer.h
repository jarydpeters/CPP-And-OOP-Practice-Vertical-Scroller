#ifndef MAIN_MENU_RENDERER_H
#define MAIN_MENU_RENDERER_H

#include "menuRenderer.h"

class MainMenuRenderer : public MenuRenderer
{
    public:

        /**
         * constructor
         * 
         */
        MainMenuRenderer(SdlUtility sdlUtility,
            SDL_Window* win, 
            SDL_Renderer* ren,
            std::string titleFontPath,
            std::string subtitleFontPath,
            int titleTextPointSize,
            int subtitleTextPointSize);

        /**
         * renders currently displayed menu based off of currentScreen parameter
         *
         * \param menuTitleTextRenderer text renderer for menu title text
         * \param menuSubtextRenderer text renderer for menu subtitle text
         * \returns void
         */
        void renderCurrentScreen(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) override;

        /**
         * adjusts UI positions for new resolution
         */
        void updateUIPositions() override;

    private:

        #define MAIN_MENU_CONTINUE_TEXT "CONTINUE"
        #define MAIN_MENU_NEW_GAME_TEXT "NEW GAME"
        #define MAIN_MENU_SETTINGS_TEXT "SETTINGS"
        #define MAIN_MENU_EXIT_TEXT "EXIT GAME"

        std::map<int, const std::string> mainMenuOptionsText =
        {
            {0, "CONTINUE"},
            {1, "NEW GAME"},
            {2, "SETTINGS"},
            {3, "EXIT GAME"},
        };

        /**
         * manipulates menu based off of keystroke event
         *
         * \param event keystroke event to be acted upon
         * \returns void
         */
        void evaluateKeystrokeEvent(const SDL_Event event) override;

        /**
         * manipulates menu based off of mouse motion event
         *
         * \returns void
         */
        void evaluateMouseMotionEvent() override;

        /**
         * manipulates menu based off of mouse button event
         *
         * \param event mouse button event to be acted upon
         * \returns void
         */
        void evaluateMouseButtonEvent(const SDL_Event event) override;

        /**
         * manipulates menu based off of mousewheel event
         *
         * \param event mousewheel event to be acted upon
         * \returns void
         */
        void evaluateMouseWheelEvent(const SDL_Event event) override;

        /**
         * moves forward one menu option
         */
        void advanceToNextMenuOption() override;

        /**
         * moves back one menu option
         */
        void returnToPreviousMenuOption() override;
};

#endif // MAIN_MENU_RENDERER_H