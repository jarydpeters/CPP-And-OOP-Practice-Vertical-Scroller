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

//TODO: DO WINDOWS NEED TO BE UNIQUE PER SCREEN OR JUST ONE OVERALL?
// Create the window for the title screen
SDL_Window* mainWindow = sdlUtility.createAndVerifySDLWindow(
    "mainWindow", 
    DEFAULT_HORIZONTAL_RESOLUTION, 
    DEFAULT_VERTICAL_RESOLUTION, 
    SDL_WINDOW_OPENGL);

SDL_Renderer* mainWindowRenderer = sdlUtility.createAndVerifySDLRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

//set up main menu 
MainMenuRenderer mainMenuScreen = MainMenuRenderer(sdlUtility,
    mainWindow, 
    mainWindowRenderer,
    FONT_PATH,
    FONT_PATH,
    TITLE_TEXT_POINT_SIZE,
    SUBTITLE_TEXT_POINT_SIZE);

SDL_Renderer* mainMenuScreenRenderer = mainMenuScreen.getTitleScreenRenderer();

TextRenderer menuTitleScreenTextRenderer(mainMenuScreen.getMenuTitleTextFont());
TextRenderer menuScreenSubtextRenderer(mainMenuScreen.getMenuSubtitleTextFont());

//set up settings menu
SettingsMenuRenderer settingsMenuScreen = SettingsMenuRenderer(sdlUtility,
    mainWindow, 
    mainWindowRenderer,
    FONT_PATH,
    FONT_PATH,
    TITLE_TEXT_POINT_SIZE,
    SUBTITLE_TEXT_POINT_SIZE);

SDL_Renderer* settingsMenuScreenRenderer = settingsMenuScreen.getTitleScreenRenderer();

TextRenderer settingsMenuScreenTitleTextRenderer(settingsMenuScreen.getMenuTitleTextFont());
TextRenderer settingsMenuScreenSubtextRenderer(settingsMenuScreen.getMenuSubtitleTextFont());

//set up main game
GameplayRenderer gameplayScreen = GameplayRenderer(sdlUtility,
    mainWindow, 
    mainWindowRenderer,
    FONT_PATH,
    FONT_PATH,
    TITLE_TEXT_POINT_SIZE,
    SUBTITLE_TEXT_POINT_SIZE);

SDL_Renderer* gameplayScreenRenderer = gameplayScreen.getMainGameWindowRenderer();

TextRenderer gameplayScreenTitleTextRenderer(gameplayScreen.getMenuTitleTextFont());
TextRenderer gameplayScreenSubtextRenderer(gameplayScreen.getMenuSubtitleTextFont());

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

    if(!mainWindow) 
    {
        std::cout << "mainWindow Init Unsuccessful!" << std::endl;
        return -1;
    }
    
    if(!mainWindowRenderer) 
    {
        std::cout << "mainWindowRenderer Init Unsuccessful!" << std::endl;
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
                SDL_SetRenderDrawColor(mainMenuScreenRenderer, black.r, black.g, black.b, black.a);
                SDL_RenderClear(mainMenuScreenRenderer);

                while (SDL_PollEvent(&event))
                {
                    mainMenuScreen.executeMenuActionBasedOnEvent(event);
                }
                
                if(firstLoop)
                {
                    mainMenuScreen.setFullscreen(mainMenuScreen.getFullscreen());
                }

                mainMenuScreen.renderCurrentScreen(menuTitleScreenTextRenderer, menuScreenSubtextRenderer);

                mainMenuScreen.destroyTextures();

                break;
            }
            case(WindowRenderer::SETTINGS_MENU_SCREEN):
            {
                SDL_SetRenderDrawColor(settingsMenuScreenRenderer, black.r, black.g, black.b, black.a);
                SDL_RenderClear(settingsMenuScreenRenderer);

                while (SDL_PollEvent(&event))
                {
                    settingsMenuScreen.executeMenuActionBasedOnEvent(event);
                }
                
                if(firstLoop)
                {
                    settingsMenuScreen.setFullscreen(settingsMenuScreen.getFullscreen());
                }

                settingsMenuScreen.renderCurrentScreen(settingsMenuScreenTitleTextRenderer, settingsMenuScreenSubtextRenderer);

                settingsMenuScreen.destroyTextures();

                break;
            }
            case(WindowRenderer::MAIN_GAME_SCREEN):
            {
                SDL_SetRenderDrawColor(gameplayScreenRenderer, black.r, black.g, black.b, black.a);
                SDL_RenderClear(gameplayScreenRenderer);

                while (SDL_PollEvent(&event))
                {
                    mainMenuScreen.executeMenuActionBasedOnEvent(event);
                }

                mainMenuScreen.renderCurrentScreen(gameplayScreenTitleTextRenderer, gameplayScreenSubtextRenderer);

                mainMenuScreen.destroyTextures();

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

    sdlUtility.cleanup(mainMenuScreen.getMenuSubtitleTextFont(), 
        mainMenuScreen.getTitleScreenWindow(), 
        mainMenuScreen.getTitleScreenRenderer(), 
        mainMenuScreen.getMenuSelectionIconTexture());

    return 0;
}