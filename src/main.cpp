#include <iostream>

#include "../include/sdl/SDL.h"
#include "../include/sdl/SDL_ttf.h"
#include "../include/headers/textRenderer.h"

constexpr int maxRGBHex = 0xFF;
constexpr int mainTitleVerticalPostion = 200;

void cleanup(TTF_Font* font, SDL_Window* window, SDL_Renderer* renderer)
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if(TTF_Init() < 0) 
    {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Window* mainWindow = SDL_CreateWindow("VertScroller", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    if(mainWindow == nullptr) 
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* mainWindowRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if(mainWindowRenderer == nullptr) 
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return -1;
    }

    TTF_Font* pixelFont = TTF_OpenFont("assets/fonts/Pixellettersfull-BnJ5.ttf", 24);
    if(pixelFont == nullptr) 
    {
        std::cerr << "Font could not be opened! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(mainWindowRenderer);
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return -1;
    }

    SDL_Color white = {maxRGBHex, maxRGBHex, maxRGBHex, maxRGBHex};
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
            else if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                textRenderer.renderHorizontallyCenteredText(mainWindowRenderer, "It's Working!", mainTitleVerticalPostion, white, mainWindow);
            }
        }
        textRenderer.renderHorizontallyCenteredText(mainWindowRenderer, "It's Working!", mainTitleVerticalPostion, white, mainWindow);
        SDL_RenderPresent(mainWindowRenderer);
    }

    cleanup(pixelFont, mainWindow, mainWindowRenderer);

    return 0;
}