#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "assetFilePaths.h"
#include "commonDefines.h"
#include "menuRenderer.h"
#include "textRenderer.h"

MenuRenderer menuRenderer;

void cleanup(TTF_Font* font, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture)
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    TTF_Quit();
    SDL_Quit();
}

bool successfulSDLInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else if(TTF_Init() < 0) 
    {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    else
    {
        return true;
    }
}

SDL_Window* createAndVerifySDLWindow(const char* windowName, const bool horizontalCentering, const bool verticalCentering, const int horizontalSize, const int verticalSize, const Uint32 flags)
{
    SDL_Window* returnWindow = SDL_CreateWindow(
        windowName, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        DEFAULT_HORIZONTAL_RESOLUTION, 
        DEFAULT_VERTICAL_RESOLUTION, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(returnWindow == nullptr) 
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    return returnWindow;
}

SDL_Renderer* createAndVerifySDLRenderer(SDL_Window* rendererWindow, const int renderingDriverIndex, const Uint32 flags)
{
    SDL_Renderer* returnRenderer = SDL_CreateRenderer(rendererWindow, renderingDriverIndex, flags);
    if(returnRenderer == nullptr) 
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(rendererWindow);
        SDL_Quit();
    }
    return returnRenderer;
}

TTF_Font* createAndVerifyTTFFont(const char* fontFile, const int fontPointSize, SDL_Window* windowToRenderFontOn, SDL_Renderer* windowRenderer)
{
    TTF_Font* returnFont = TTF_OpenFont(fontFile, fontPointSize);
    if(returnFont == nullptr) 
    {
        std::cerr << "Font could not be opened! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(windowRenderer);
        SDL_DestroyWindow(windowToRenderFontOn);
        SDL_Quit();
    }
    return returnFont;
}

int main(int argc, char* argv[])
{
    if(!successfulSDLInit())
    {
        return -1;
    }

    menuRenderer.mainWindow = createAndVerifySDLWindow(
        "mainWindow", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        DEFAULT_HORIZONTAL_RESOLUTION, 
        DEFAULT_VERTICAL_RESOLUTION, 
        SDL_WINDOW_OPENGL);

    SDL_SetWindowResizable(menuRenderer.mainWindow, SDL_bool::SDL_FALSE);

    menuRenderer.mainWindowRenderer = createAndVerifySDLRenderer(menuRenderer.mainWindow, -1, SDL_RENDERER_ACCELERATED);

    menuRenderer.menuTextPixelFont = createAndVerifyTTFFont(FONT_PATH, 48, menuRenderer.mainWindow, menuRenderer.mainWindowRenderer);
    menuRenderer.subtextPixelFont = createAndVerifyTTFFont(FONT_PATH, 24, menuRenderer.mainWindow, menuRenderer.mainWindowRenderer);

    TextRenderer menuTextRenderer(menuRenderer.menuTextPixelFont);
    TextRenderer menuSubtextRenderer(menuRenderer.subtextPixelFont);

    menuRenderer.initializeMenuOptionsMaps();

    SDL_Event event;

    while(!menuRenderer.quitGame)
    {
        SDL_SetRenderDrawColor(menuRenderer.mainWindowRenderer, black.r, black.g, black.b, black.a);
        SDL_RenderClear(menuRenderer.mainWindowRenderer);

        while (SDL_PollEvent(&event))
        {
            menuRenderer.executeMenuActionBasedOnEvent(event);
        }

        menuRenderer.renderCurrentlyDisplayedMenu(menuRenderer.currentlyDisplayedMenu, menuTextRenderer, menuSubtextRenderer);
    }

    cleanup(menuRenderer.subtextPixelFont, menuRenderer.mainWindow, menuRenderer.mainWindowRenderer, menuRenderer.mainMenuSelectionTexture);

    return 0;
}