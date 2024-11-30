#include "gameplayRenderer.h"
#include "mainMenuRenderer.h"
#include "settingsMenuRenderer.h"
#include "sdlUtility.h"
#include "textRenderer.h"
#include "windowRenderer.h"

//FPS calculation variable
Uint32 frameCount = 0;
Uint32 lastFPSUpdateTime = SDL_GetTicks();

SdlUtility sdlUtility;

//TODO: CAN WINDOWS AND RENDERERS BE MADE STATIC TO WINDOWRENDERER?

// Create the window for the title screen
SDL_Window* menuScreenWindow = sdlUtility.createAndVerifySDLWindow(
    "menuScreenWindow", 
    DEFAULT_HORIZONTAL_RESOLUTION, 
    DEFAULT_VERTICAL_RESOLUTION, 
    SDL_WINDOW_OPENGL);

SDL_Renderer* menuScreenWindowRenderer = sdlUtility.createAndVerifySDLRenderer(menuScreenWindow, -1, SDL_RENDERER_ACCELERATED);

//set up main menu 
MainMenuRenderer mainMenu = MainMenuRenderer(sdlUtility,
    menuScreenWindow, 
    menuScreenWindowRenderer,
    FONT_PATH,
    FONT_PATH,
    TITLE_TEXT_POINT_SIZE,
    SUBTITLE_TEXT_POINT_SIZE);

SDL_Renderer* mainMenuRenderer = mainMenu.getTitleScreenRenderer();

//set up settings menu
SettingsMenuRenderer settingsMenu = SettingsMenuRenderer(sdlUtility,
    menuScreenWindow, 
    menuScreenWindowRenderer,
    FONT_PATH,
    FONT_PATH,
    TITLE_TEXT_POINT_SIZE,
    SUBTITLE_TEXT_POINT_SIZE);

SDL_Renderer* settingsMenuRenderer = settingsMenu.getTitleScreenRenderer();

TextRenderer menuTitleTextRenderer(mainMenu.getMenuTitleTextFont());
TextRenderer menuSubtextRenderer(mainMenu.getMenuSubtitleTextFont());

TextRenderer settingsMenuTitleTextRenderer(settingsMenu.getMenuTitleTextFont());
TextRenderer settingsMenuSubtextRenderer(settingsMenu.getMenuSubtitleTextFont());

void calculateFPS()
{
    Uint32 currentTime = SDL_GetTicks();
    if(currentTime - lastFPSUpdateTime >= 1000)  // One second has passed since last FPS calculation
    {
        WindowRenderer::setCurrentFPS(frameCount);

        frameCount = 0;
        lastFPSUpdateTime = currentTime;
    }
}

int main(int argc, char* argv[])
{    
    if(!sdlUtility.successfulSDLInit())
    {
        std::cout << "SDL Init Unsuccessful!" << std::endl;
        return -1;
    }

    if(!menuScreenWindow) 
    {
        std::cout << "menuScreenWindow Init Unsuccessful!" << std::endl;
        return -1;
    }
    
    if(!menuScreenWindowRenderer) 
    {
        std::cout << "menuScreenWindowRenderer Init Unsuccessful!" << std::endl;
        return -1;
    }

    SDL_Event event;

    bool firstLoop = true;

    while(!WindowRenderer::quitGame)
    {
        frameCount++;

        Uint32 timeAtStartOfFrame = SDL_GetTicks();

        switch(WindowRenderer::currentScreen)
        {
            case(WindowRenderer::MAIN_MENU_SCREEN):
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

                mainMenu.renderCurrentScreen(menuTitleTextRenderer, menuSubtextRenderer);

                mainMenu.destroyTextures();

                break;
            }
            case(WindowRenderer::SETTINGS_MENU_SCREEN):
            {
                SDL_SetRenderDrawColor(settingsMenuRenderer, black.r, black.g, black.b, black.a);
                SDL_RenderClear(settingsMenuRenderer);

                while (SDL_PollEvent(&event))
                {
                    settingsMenu.executeMenuActionBasedOnEvent(event);
                }
                
                if(firstLoop)
                {
                    settingsMenu.setFullscreen(settingsMenu.getFullscreen());
                }

                settingsMenu.renderCurrentScreen(settingsMenuTitleTextRenderer, settingsMenuSubtextRenderer);

                settingsMenu.destroyTextures();

                break;
            }
            case(WindowRenderer::MAIN_GAME_SCREEN):
            {
                WindowRenderer::quitGame = true;

                break;
            }
            case(WindowRenderer::CUTSCENE_SCREEN):
            {
                break;
            }
            case(WindowRenderer::UPGRADE_MENU_SCREEN):
            {
                break;
            }
        }
        firstLoop = false;

        Uint32 timeElapsedOverLoop = SDL_GetTicks() - timeAtStartOfFrame;

        calculateFPS();

        //TODO: SET UP WINDOW RENDERER TO RENDER FPS FOR DEBUG/AS OPTION
        if(timeElapsedOverLoop < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - timeElapsedOverLoop);
        }
    }

    sdlUtility.cleanup(mainMenu.getMenuSubtitleTextFont(), 
        mainMenu.getTitleScreenWindow(), 
        mainMenu.getTitleScreenRenderer(), 
        mainMenu.getMenuSelectionIconTexture());

    return 0;
}