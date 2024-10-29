#include <iostream>
#include <string>

#include "../include/sdl/SDL.h"
#include "../include/sdl/SDL_ttf.h"
#include "../include/headers/textRenderer.h"

constexpr int maxRGBHex = 0xFF;
constexpr int maxTransparencyHex = 0xFF;
constexpr int mainTitleVerticalPostion = 200;

void cleanup(TTF_Font* font, SDL_Window* window, SDL_Renderer* renderer)
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

SDL_Window* createAndVerifySDLWindow(const std::string windowName, const bool horizontalCentering, const bool verticalCentering, const int horizontalSize, const int verticalSize, const Uint32 flags)
{
    SDL_Window* returnWindow = SDL_CreateWindow("VertScroller", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
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

    SDL_Window* mainWindow = createAndVerifySDLWindow("VertScroller", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    SDL_Renderer* mainWindowRenderer = createAndVerifySDLRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* pixelFont = createAndVerifyTTFFont("assets/fonts/Pixellettersfull-BnJ5.ttf", 24, mainWindow, mainWindowRenderer);

    SDL_Color white = {maxRGBHex, maxRGBHex, maxRGBHex, maxTransparencyHex};
    SDL_Color black = {0, 0, 0, maxRGBHex};
    SDL_Event event;

    TextRenderer textRenderer(pixelFont);

    bool quit = false;
    while (!quit)
    {
        SDL_SetRenderDrawColor(mainWindowRenderer, black.r, black.g, black.b, black.a);
        SDL_RenderClear(mainWindowRenderer);

        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
            else if(event.type == SDL_QUIT) 
            {
                quit = true;
            }
        }
        textRenderer.renderHorizontallyCenteredText(mainWindowRenderer, "Horizontally Centered Text", mainTitleVerticalPostion, white, mainWindow);
        textRenderer.renderVerticallyCenteredText(mainWindowRenderer, "Vertically Centered Text", 200, white, mainWindow);
        textRenderer.renderText(mainWindowRenderer, "Placed Text", 300, 300, white, mainWindow);

        SDL_RenderPresent(mainWindowRenderer);
    }

    cleanup(pixelFont, mainWindow, mainWindowRenderer);

    return 0;
}