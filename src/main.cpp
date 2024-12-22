#include <GL/glew.h>
#include <SDL.h>
#include <iostream>

#include "gameplayRenderer.h"
#include "mainMenuRenderer.h"
#include "openGLUtility.h"
#include "settingsMenuRenderer.h"
#include "sdlUtility.h"
#include "textRenderer.h"
#include "windowRenderer.h"

//FPS calculation variable
Uint32 frameCount = 0;
Uint32 lastFPSUpdateTime = SDL_GetTicks();

int main(int argc, char* argv[]) 
{
    SDL_Init(SDL_INIT_VIDEO);  // Initialize SDL2
    SDL_Window* mainWindow = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(mainWindow);

    initOpenGL(mainWindow);

    // Main loop
    SDL_Event event;
    while(!WindowRenderer::quitGame)    
    {
        // Poll events
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                WindowRenderer::quitGame = true;
            }
        }

        // Clear the screen and set background color to blue for debugging
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(mainWindow);
    }

    // Clean up
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}

// SdlUtility sdlUtility;

// //TODO: CAN WINDOWS AND RENDERERS BE MADE STATIC TO WINDOWRENDERER?

// //TODO: DO WINDOWS NEED TO BE UNIQUE PER SCREEN OR JUST ONE OVERALL?
// // Create the window for the title screen
// SDL_Window* mainWindow = sdlUtility.createAndVerifySDLWindowWithOpenGL(
//     "mainWindow", 
//     DEFAULT_HORIZONTAL_RESOLUTION, 
//     DEFAULT_VERTICAL_RESOLUTION, 
//     SDL_WINDOW_OPENGL);

// SDL_Renderer* mainWindowRenderer = sdlUtility.createAndVerifySDLRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

// //TODO: REMOVE ALL SDL RENDERERS
// //set up main menu 
// MainMenuRenderer mainMenuScreen = MainMenuRenderer(sdlUtility,
//     mainWindow, 
//     mainWindowRenderer,
//     FONT_PATH,
//     FONT_PATH,
//     TITLE_TEXT_POINT_SIZE,
//     SUBTITLE_TEXT_POINT_SIZE);

// SDL_Renderer* mainMenuScreenRenderer = mainMenuScreen.getTitleScreenRenderer();

// TextRenderer menuTitleScreenTextRenderer(mainMenuScreen.getMenuTitleTextFont());
// TextRenderer menuScreenSubtextRenderer(mainMenuScreen.getMenuSubtitleTextFont());

// //set up settings menu
// SettingsMenuRenderer settingsMenuScreen = SettingsMenuRenderer(sdlUtility,
//     mainWindow, 
//     mainWindowRenderer,
//     FONT_PATH,
//     FONT_PATH,
//     TITLE_TEXT_POINT_SIZE,
//     SUBTITLE_TEXT_POINT_SIZE);

// SDL_Renderer* settingsMenuScreenRenderer = settingsMenuScreen.getTitleScreenRenderer();

// TextRenderer settingsMenuScreenTitleTextRenderer(settingsMenuScreen.getMenuTitleTextFont());
// TextRenderer settingsMenuScreenSubtextRenderer(settingsMenuScreen.getMenuSubtitleTextFont());

// //set up main game
// GameplayRenderer gameplayScreen = GameplayRenderer(sdlUtility,
//     mainWindow, 
//     mainWindowRenderer,
//     FONT_PATH,
//     FONT_PATH,
//     TITLE_TEXT_POINT_SIZE,
//     SUBTITLE_TEXT_POINT_SIZE);

// TextRenderer gameplayScreenTitleTextRenderer(gameplayScreen.getMenuTitleTextFont());
// TextRenderer gameplayScreenSubtextRenderer(gameplayScreen.getMenuSubtitleTextFont());

//TODO: MOVE TO UTILITY FILE
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

// int main(int argc, char* argv[])
// {    
    // if(!sdlUtility.successfulSDLInit())
    // {
    //     std::cout << "SDL Init Unsuccessful!" << std::endl;
    //     return -1;
    // }

    // if(!mainWindow) 
    // {
    //     std::cout << "mainWindow Init Unsuccessful!" << std::endl;
    //     return -1;
    // }
    
    // if(!mainWindowRenderer) 
    // {
    //     std::cout << "mainWindowRenderer Init Unsuccessful!" << std::endl;
    //     return -1;
    // }

    // SDL_Event event;

    //bool firstLoop = true;

    // while(!WindowRenderer::quitGame)
    // {
        // frameCount++;

        // // Clear screen using OpenGL
        // glClear(GL_COLOR_BUFFER_BIT);

        // // Use the shader program for rendering
        // //glUseProgram(shaderProgram);

        // Uint32 timeAtStartOfFrame = SDL_GetTicks();

        // switch(WindowRenderer::currentScreen)
        // {
        //     case(WindowRenderer::MAIN_MENU_SCREEN):
        //     {
        //         glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // blue debug background for main menu
        //         //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Dark background for main menu

        //         while (SDL_PollEvent(&event))
        //         {
        //             mainMenuScreen.executeMenuActionBasedOnEvent(event);
        //         }
                
        //         if(firstLoop)
        //         {
        //             mainMenuScreen.setFullscreen(mainMenuScreen.getFullscreen());
        //         }

        //         mainMenuScreen.renderCurrentScreen(menuTitleScreenTextRenderer, menuScreenSubtextRenderer);

        //         mainMenuScreen.destroyTextures();

        //         break;
        //     }
        //     case(WindowRenderer::SETTINGS_MENU_SCREEN):
        //     {
        //         glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // blue debug background for settings menu
        //         //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Dark background for main menu

        //         while (SDL_PollEvent(&event))
        //         {
        //             settingsMenuScreen.executeMenuActionBasedOnEvent(event);
        //         }
                
        //         if(firstLoop)
        //         {
        //             settingsMenuScreen.setFullscreen(settingsMenuScreen.getFullscreen());
        //         }

        //         settingsMenuScreen.renderCurrentScreen(settingsMenuScreenTitleTextRenderer, settingsMenuScreenSubtextRenderer);

        //         settingsMenuScreen.destroyTextures();

        //         break;
        //     }
        //     case(WindowRenderer::MAIN_GAME_SCREEN):
        //     {               
        //         glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // blue debug background for main game screen 
        //         //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Dark background for main menu                

        //         while (SDL_PollEvent(&event))
        //         {
        //             gameplayScreen.executeGameplayActionBasedOnEvent(event);
        //         }

        //         gameplayScreen.renderMainGame();

        //         gameplayScreen.destroyTextures();

        //         break;
        //     }
        //     case(WindowRenderer::CUTSCENE_SCREEN):
        //     {
        //         break;
        //     }
        //     case(WindowRenderer::UPGRADE_MENU_SCREEN):
        //     {
        //         break;
        //     }
        // }

        // SDL_GL_SwapWindow(mainWindow);

        // firstLoop = false;

        // Uint32 timeElapsedOverLoop = SDL_GetTicks() - timeAtStartOfFrame;

        // calculateFPS();

        // //TODO: MOVE TO UTILITY FILE
        // //TODO: SET UP WINDOW RENDERER TO RENDER FPS FOR DEBUG/AS OPTION
        // if(timeElapsedOverLoop < FRAME_DELAY)
        // {
        //     SDL_Delay(FRAME_DELAY - timeElapsedOverLoop);
        // }
    // }
// 
//     sdlUtility.cleanup(mainMenuScreen.getMenuSubtitleTextFont(), 
//         mainMenuScreen.getTitleScreenWindow(), 
//         mainMenuScreen.getTitleScreenRenderer(), 
//         mainMenuScreen.getMenuSelectionIconTexture());

//     return 0;
// }