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
         * renders currently displayed menu based off of currentlyDisplayedMenu parameter
         *
         * \param currentlyDisplayedMenu menu to be displayed
         * \param menuTitleTextRenderer text renderer for menu title text
         * \param menuSubtextRenderer text renderer for menu subtitle text
         * \returns void
         */
        void renderCurrentlyDisplayedMenu(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) override;

        SDL_Window* getTitleScreenWindow() override;
        void setTitleScreenWindow(SDL_Window* window) override;

        SDL_Renderer* getTitleScreenRenderer() override;
        void setTitleScreenRenderer(SDL_Renderer* renderer) override;

        TTF_Font* getMenuTitleTextFont() override;
        void setMenuTitleTextFont(TTF_Font* font) override;

        TTF_Font* getMenuSubtitleTextFont() override;
        void setMenuSubtitleTextFont(TTF_Font* font) override;

    private:

        #define MAIN_MENU_CONTINUE_TEXT "CONTINUE"
        #define MAIN_MENU_NEW_GAME_TEXT "NEW GAME"
        #define MAIN_MENU_SETTINGS_TEXT "SETTINGS"
        #define MAIN_MENU_EXIT_TEXT "EXIT GAME"

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
};

#endif // MAIN_MENU_RENDERER_H