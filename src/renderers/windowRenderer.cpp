#include <iostream>
#include <SDL_ttf.h>

#include "windowRenderer.h"

bool WindowRenderer::quitGame = false;
int WindowRenderer::currentScreen = MAIN_MENU_SCREEN;

bool WindowRenderer::displayFPS = true;
int WindowRenderer::currentFPS = 0;
WindowRenderer::Resolution WindowRenderer::resolution = WindowRenderer::Resolution(DEFAULT_HORIZONTAL_RESOLUTION, DEFAULT_VERTICAL_RESOLUTION);

int WindowRenderer::menuTitleLogoVerticalPosition;

WindowRenderer::WindowRenderer(SDL_Window* win, SDL_Renderer* ren)
{
    window = win;
    renderer = ren;
}

SDL_Window* WindowRenderer::getWindow()
{
    return window;
}

void WindowRenderer::setWindow(SDL_Window* win)
{
    window = win;
}

SDL_Renderer* WindowRenderer::getRenderer()
{
    return renderer;
}

void WindowRenderer::setRenderer(SDL_Renderer* ren)
{
    renderer = ren;
}

bool WindowRenderer::getDisplayFPS()
{
    return displayFPS;
}

void WindowRenderer::setDisplayFPS(const bool newDisplayFPS)
{
    displayFPS = newDisplayFPS;
}

int WindowRenderer::getCurrentFPS()
{
    return currentFPS;
}

void WindowRenderer::setCurrentFPS(const int newCurrentFPS)
{
    currentFPS = newCurrentFPS;
}

int WindowRenderer::getCurrentHorizontalResolution()
{
    return resolution.currentHorizontalResolution;
}

void WindowRenderer::setCurrentHorizontalResolution(const int horizontalResolution)
{
    resolution.currentHorizontalResolution = horizontalResolution;
}

int WindowRenderer::getCurrentVerticalResolution()
{
    return resolution.currentVerticalResolution;
}

void WindowRenderer::setCurrentVerticalResolution(const int verticalResolution)
{
    resolution.currentVerticalResolution = verticalResolution;
}

void WindowRenderer::renderFPS(SDL_Renderer* renderer, TTF_Font* menuSubtitleFont)
{
    if (displayFPS)
    {
        // Create a string with the current FPS value
        std::string fpsText = std::to_string(getCurrentFPS());

        // Create a surface from the FPS text using SDL_ttf
        SDL_Surface* textSurface = TTF_RenderText_Solid(menuSubtitleFont, fpsText.c_str(), white);

        if(textSurface == nullptr)
        {
            std::cout << "Error creating text surface: " << TTF_GetError() << std::endl;
            return;
        }

        // Create a texture from the surface
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if(textTexture == nullptr)
        {
            std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(textSurface); // Clean up the surface
            return;
        }

        // Set the destination rectangle for rendering (top-left corner)
        SDL_Rect renderQuad = {10, 10, textSurface->w, textSurface->h};

        // Render the text to the screen
        SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

        // Clean up the texture and surface
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }
}

void WindowRenderer::renderScanLines(SDL_Renderer* renderer)
{    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50);  // Dark gray scanlines
    
    for (int y = 1; y < getCurrentVerticalResolution(); y += 2)  // Every other line
    {
        SDL_RenderDrawLine(renderer, 0, y, getCurrentHorizontalResolution(), y);
    }
}

TTF_Font* WindowRenderer::getMenuTitleTextFont()
{
    return menuTitleFont;
}

void WindowRenderer::setMenuTitleTextFont(TTF_Font* font)
{
    menuTitleFont = font;
}

TTF_Font* WindowRenderer::getMenuSubtitleTextFont()
{
    return menuSubtitleFont;
}

void WindowRenderer::setMenuSubtitleTextFont(TTF_Font* font)
{
    menuSubtitleFont = font;
}

// void WindowRenderer::destroyTextures()
// {
//     // Destroy old textures to prevent memory leaks
//     if(scanlinesTexture != nullptr) 
//     {
//         SDL_DestroyTexture(scanlinesTexture);
//         scanlinesTexture = nullptr;  // Prevent dangling pointer
//     }
// }
