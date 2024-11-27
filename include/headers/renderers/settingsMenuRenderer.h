#ifndef SETTINGS_MENU_RENDERER_H
#define SETTINGS_MENU_RENDERER_H

#include "menuRenderer.h"

class SettingsMenuRenderer : public MenuRenderer
{

    public:

        /**
         * constructor
         */
        SettingsMenuRenderer(SdlUtility sdlUtility,
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

        #define SETTINGS_MENU_TITLE_TEXT "SETTINGS"
        #define SETTINGS_MENU_FULLSCREEN_TEXT "FULL SCREEN"
        #define SETTINGS_MENU_RESOLUTION_TEXT "RESOLUTION"
        #define SETTINGS_MENU_MUSIC_VOLUME_TEXT "MUSIC VOLUME"
        #define SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT "SOUND EFFECTS VOLUME"
        #define SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT "RETURN TO MAIN MENU"

        #define SETTING_NOT_SELECTED_TEXT "[ ]"
        #define SETTING_SELECTED_TEXT "[X]"

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
         * renders main menu logo sprite as well as main menu selection icon sprite
         * 
         * \returns void
         */
        void renderLogoAndMenuOptionSelectionSprites() override;
};

#endif // SETTINGS_MENU_RENDERER_H