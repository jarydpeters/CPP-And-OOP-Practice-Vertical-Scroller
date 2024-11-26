#include "globalValues.h"
#include "mainGameRenderer.h"
#include "menuRenderer.h"
#include "sdlUtility.h"
#include "textRenderer.h"

int main(int argc, char* argv[])
{    
    SdlUtility sdlUtility;

    if(!sdlUtility.successfulSDLInit())
    {
        std::cout << "SDL Init Unsuccessful!" << std::endl;
        return -1;
    }

    // Create the window for the title screen
    SDL_Window* titleScreenWindow = sdlUtility.createAndVerifySDLWindow(
        "titleScreenWindow", 
        DEFAULT_HORIZONTAL_RESOLUTION, 
        DEFAULT_VERTICAL_RESOLUTION, 
        SDL_WINDOW_OPENGL);

    if (!titleScreenWindow) 
    {
        std::cout << "titleScreenWindow Init Unsuccessful!" << std::endl;
        return -1;
    }

    // Create the renderer for the title screens window
    SDL_Renderer* titleScreenWindowRenderer = sdlUtility.createAndVerifySDLRenderer(titleScreenWindow, -1, SDL_RENDERER_ACCELERATED);
    
    if (!titleScreenWindowRenderer) 
    {
        std::cout << "titleScreenWindowRenderer Init Unsuccessful!" << std::endl;
        return -1;
    }

    MenuRenderer mainMenu = MenuRenderer(titleScreenWindow, titleScreenWindowRenderer);

    SDL_SetWindowResizable(mainMenu.getTitleScreenWindow(), SDL_bool::SDL_FALSE);

    mainMenu.setMenuTitleTextFont(sdlUtility.createAndVerifyTTFFont(FONT_PATH, 
        TITLE_TEXT_POINT_SIZE, 
        mainMenu.getTitleScreenWindow(), 
        mainMenu.getTitleScreenRenderer()));

    mainMenu.setMenuSubtitleTextFont(sdlUtility.createAndVerifyTTFFont(FONT_PATH, 
        SUBTITLE_TEXT_POINT_SIZE, 
        mainMenu.getTitleScreenWindow(), 
        mainMenu.getTitleScreenRenderer()));

    TextRenderer menuTitleTextRenderer(mainMenu.getMenuTitleTextFont());
    TextRenderer menuSubtextRenderer(mainMenu.getMenuSubtitleTextFont());

    SDL_Renderer* mainMenuRenderer = mainMenu.getTitleScreenRenderer();

    SDL_Event event;

    bool firstLoop = true;

    while(!quitGame)
    {
        Uint32 timeAtStartOfFrame = SDL_GetTicks();

        switch(currentScreen)
        {
            case(TITLE_MENU_SCREEN):
            {
                SDL_SetRenderDrawColor(mainMenuRenderer, black.r, black.g, black.b, black.a);
                SDL_RenderClear(mainMenuRenderer);

                while (SDL_PollEvent(&event))
                {
                    mainMenu.executeMenuActionBasedOnEvent(event);
                }
                
                if(firstLoop)
                {
                    mainMenu.setFullscreen(mainMenu.getFullscreen());
                }

                mainMenu.renderCurrentlyDisplayedMenu(mainMenu.getCurrentlyDisplayedMenu(), menuTitleTextRenderer, menuSubtextRenderer);
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

        Uint32 timeElapsedOverLoop = SDL_GetTicks() - timeAtStartOfFrame;

        //TODO: SET UP WINDOW RENDERER TO RENDER FPS FOR DEBUG/AS OPTION
        if(timeElapsedOverLoop < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - timeElapsedOverLoop);
        }

        mainMenu.destroyTextures();
    }

    sdlUtility.cleanup(mainMenu.getMenuSubtitleTextFont(), 
        mainMenu.getTitleScreenWindow(), 
        mainMenu.getTitleScreenRenderer(), 
        mainMenu.getMenuSelectionIconTexture());

    return 0;
}