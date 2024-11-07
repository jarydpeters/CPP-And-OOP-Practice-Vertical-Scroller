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

constexpr int MENU_TITLE_TEXT_VERTICAL_POSITION = 200;
constexpr int MENU_TEXT_FIRST_VERTICAL_POSITION = MENU_TITLE_TEXT_VERTICAL_POSITION + 100;
constexpr int MENU_TEXT_SECOND_VERTICAL_POSITION = MENU_TEXT_FIRST_VERTICAL_POSITION + 50;
constexpr int MENU_TEXT_THIRD_VERTICAL_POSITION = MENU_TEXT_SECOND_VERTICAL_POSITION + 50;
constexpr int MENU_TEXT_FOURTH_VERTICAL_POSITION = MENU_TEXT_THIRD_VERTICAL_POSITION + 50;

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

//TODO: FINISH FUNCTION COMMENTS
        /**
         * 
         *
         * \param 
         * \returns 
         */
        void executeMenuActionBasedOnEvent(const SDL_Event event);

        /**
         * 
         *
         * \param 
         * \returns 
         */
        int getCurrentlyDisplayedMenu();

        /**
         * 
         *
         * \param 
         * \returns 
         */
        SDL_Window* getMainWindow();

        /**
         * 
         *
         * \param 
         * \returns 
         */
        void setMainWindow(SDL_Window* window);

        /**
         * 
         *
         * \param 
         * \returns 
         */
        SDL_Renderer* getMainWindowRenderer();

        /**
         * 
         *
         * \param 
         * \returns 
         */
        void setMainWindowRenderer(SDL_Renderer* renderer);

        /**
         * 
         *
         * \param 
         * \returns 
         */
        TTF_Font* getMenuTitleTextFont();

        /**
         * 
         *
         * \param 
         * \returns 
         */
        void setMenuTitleTextFont(TTF_Font* font);

        /**
         * 
         *
         * \param 
         * \returns 
         */
        TTF_Font* getMenuSubtitleTextFont();
        
        /**
         * 
         *
         * \param 
         * \returns 
         */
        void setMenuSubtitleTextFont(TTF_Font* font);

        /**
         * 
         *
         * \param 
         * \returns 
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

        int currentlyDisplayedMenu = MAIN_MENU_INDEX;

        int currentlySelectedMainMenuOption = CONTINUE_INDEX;
        int currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;

        int currentHorizontalResolution = DEFAULT_HORIZONTAL_RESOLUTION;
        int currentVerticalResolution = DEFAULT_VERTICAL_RESOLUTION;

        std::map<int, int> menuOptionsPositionMap = 
        {
            {0, MENU_TEXT_FIRST_VERTICAL_POSITION},
            {1, MENU_TEXT_SECOND_VERTICAL_POSITION},
            {2, MENU_TEXT_THIRD_VERTICAL_POSITION},
            {3, MENU_TEXT_FOURTH_VERTICAL_POSITION}
        };
};

#endif // MENU_RENDERER_H