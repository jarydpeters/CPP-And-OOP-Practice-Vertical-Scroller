#include "sdlUtility.h"

SdlUtility::SdlUtility()
{
    TTF_Init();
}


void SdlUtility::cleanup(TTF_Font* font, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture)
{
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    TTF_Quit();
    SDL_Quit();
}

bool SdlUtility::successfulSDLInit()
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

SDL_Window* SdlUtility::createAndVerifySDLWindow(const char* windowName, const int horizontalSize, const int verticalSize, const Uint32 flags)
{
    SDL_Window* returnWindow = SDL_CreateWindow(
        windowName, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        horizontalSize, 
        verticalSize, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(returnWindow == nullptr) 
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    return returnWindow;
}

SDL_Renderer* SdlUtility::createAndVerifySDLRenderer(SDL_Window* rendererWindow, const int renderingDriverIndex, const Uint32 flags)
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

TTF_Font* SdlUtility::createAndVerifyTTFFont(const char* fontFile, const int fontPointSize, SDL_Window* windowToRenderFontOn, SDL_Renderer* windowRenderer)
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