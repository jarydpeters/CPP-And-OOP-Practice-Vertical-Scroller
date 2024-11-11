#include "globalValues.h"
#include "mainGameRenderer.h"
#include "menuRenderer.h"
#include "sdlUtility.h"
#include "textRenderer.h"

//TODO: LIMIT FRAMERATE
//TODO: MAKE GAME ENGINE FRAMERATE INDEPENDENT

int main(int argc, char* argv[])
{
    MainGameRenderer mainGameRenderer;
    MenuRenderer menuRenderer;
    SdlUtility sdlUtility;

    bool firstLoop = true;

    if(!sdlUtility.successfulSDLInit())
    {
        return -1;
    }

    menuRenderer.setTitleScreensWindow(sdlUtility.createAndVerifySDLWindow(
        "titleScreensWindow", 
        DEFAULT_HORIZONTAL_RESOLUTION, 
        DEFAULT_VERTICAL_RESOLUTION, 
        SDL_WINDOW_OPENGL));

    SDL_SetWindowResizable(menuRenderer.getTitleScreensWindow(), SDL_bool::SDL_FALSE);

    menuRenderer.setTitleScreensRenderer(sdlUtility.createAndVerifySDLRenderer(menuRenderer.getTitleScreensWindow(), -1, SDL_RENDERER_ACCELERATED));
    menuRenderer.setMenuTitleTextFont(sdlUtility.createAndVerifyTTFFont(FONT_PATH, TITLE_TEXT_POINT_SIZE, menuRenderer.getTitleScreensWindow(), menuRenderer.getTitleScreensRenderer()));
    menuRenderer.setMenuSubtitleTextFont(sdlUtility.createAndVerifyTTFFont(FONT_PATH, SUBTITLE_TEXT_POINT_SIZE, menuRenderer.getTitleScreensWindow(), menuRenderer.getTitleScreensRenderer()));

    TextRenderer menuTitleTextRenderer(menuRenderer.getMenuTitleTextFont());
    TextRenderer menuSubtextRenderer(menuRenderer.getMenuSubtitleTextFont());

    SDL_Event event;

    while(!quitGame)
    {
        switch(currentScreen)
        {
            case(TITLE_MENU_SCREEN):
            {
                SDL_SetRenderDrawColor(menuRenderer.getTitleScreensRenderer(), black.r, black.g, black.b, black.a);
                SDL_RenderClear(menuRenderer.getTitleScreensRenderer());

                while (SDL_PollEvent(&event))
                {
                    menuRenderer.executeMenuActionBasedOnEvent(event);
                }
                
                if(firstLoop)
                {
                    menuRenderer.setFullscreen(menuRenderer.getFullscreen());
                }

                menuRenderer.renderCurrentlyDisplayedMenu(menuRenderer.getCurrentlyDisplayedMenu(), menuTitleTextRenderer, menuSubtextRenderer);

                break;
            }
            case MAIN_GAME_SCREEN:
            {
                quitGame = true;
                break;
            }
            case CUTSCENE_SCREEN:
            {
                break;
            }
            case UPGRADE_MENU_SCREEN:
            {
                break;
            }
        }
        firstLoop = false;
    }

    sdlUtility.cleanup(menuRenderer.getMenuSubtitleTextFont(), menuRenderer.getTitleScreensWindow(), menuRenderer.getTitleScreensRenderer(), menuRenderer.getMenuSelectionIconTexture());

    return 0;

}