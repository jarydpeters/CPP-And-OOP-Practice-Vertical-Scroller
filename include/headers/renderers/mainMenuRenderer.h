#ifndef MAIN_MENU_RENDERER_H
#define MAIN_MENU_RENDERER_H

#include "menuRenderer.h"

class MainMenuRenderer : public MenuRenderer
{
    public:

        /**
         * constructor
         */
        MainMenuRenderer(SDL_Window* win, SDL_Renderer* ren);

        /**
         * renders currently displayed menu based off of currentlyDisplayedMenu parameter
         *
         * \param currentlyDisplayedMenu menu to be displayed
         * \param menuTitleTextRenderer text renderer for menu title text
         * \param menuSubtextRenderer text renderer for menu subtitle text
         * \returns void
         */
        void renderCurrentlyDisplayedMenu(const int currentlyDisplayedMenu, 
            TextRenderer& menuTitleTextRenderer, 
            TextRenderer& menuSubtextRenderer) override;


        int getCurrentlyDisplayedMenu();

        SDL_Window* getTitleScreenWindow();
        void setTitleScreenWindow(SDL_Window* window);

        SDL_Renderer* getTitleScreenRenderer();
        void setTitleScreenRenderer(SDL_Renderer* renderer);

        TTF_Font* getMenuTitleTextFont();
        void setMenuTitleTextFont(TTF_Font* font);

        TTF_Font* getMenuSubtitleTextFont();
        void setMenuSubtitleTextFont(TTF_Font* font);

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
};

#endif // MAIN_MENU_RENDERER_H