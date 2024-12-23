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

        #define SETTING_NOT_SELECTED_TEXT "[ ]"
        #define SETTING_SELECTED_TEXT "[X]"

        #define WIDTH_OF_RESOLUTION_OPTION_TEXT 110

        std::map<int, const std::string> settingsMenuOptionsText =
        {
            {0, "FULLSCREEN"},
            {1, "DISPLAY FPS"},
            {2, "CRT SCANLINES"},
            {3, "RESOLUTION"},
            {4, "MUSIC VOLUME"},
            {5, "SOUND EFFECTS VOLUME"},
            {6, "RETURN TO MAIN MENU"}
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
         * gets resolution setting's "<" location for clickable UI
         */
        int getResolutionSettingLeftSideHorizontalPlacement();

        /**
         * moves forward one menu option
         */
        void advanceToNextMenuOption() override;

        /**
         * moves back one menu option
         */
        void returnToPreviousMenuOption() override;
};

#endif // SETTINGS_MENU_RENDERER_H