#include <iostream>

#include "../include/sdl/SDL.h"
#include "../include/sdl/SDL_ttf.h"

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

    SDL_Window* mainWindow = SDL_CreateWindow("VertScroller", 100, 100, 500, 500, SDL_WINDOW_SHOWN);
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

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(pixelFont, "It's working!", white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mainWindowRenderer, surface);

    SDL_Rect textRect;
    textRect.x = 10;
    textRect.y = 10;
    textRect.w = surface->w;
    textRect.h = surface->h;

    SDL_FreeSurface(surface);

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(mainWindowRenderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(mainWindowRenderer);

        SDL_RenderCopy(mainWindowRenderer, texture, nullptr, &textRect);

        SDL_RenderPresent(mainWindowRenderer);
    }

    SDL_DestroyTexture(texture);
    TTF_CloseFont(pixelFont);
    SDL_DestroyRenderer(mainWindowRenderer);
    SDL_DestroyWindow(mainWindow);
    TTF_Quit();
    SDL_Quit();

    return 0;
}