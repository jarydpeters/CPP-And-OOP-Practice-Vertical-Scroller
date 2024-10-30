#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "textRenderer.h"
#include "textureRenderer.h"

constexpr int MAX_RGB_HEX = 0xFF;
constexpr int MAX_TRANSPARENCY_HEX = 0xFF;
constexpr int MAIN_TITLE_VERTICAL_POSITION = 200;

#define MAIN_TITLE "VertScroller"
#define TITLE_IMAGE_PATH "assets/sprites/menuSelectionIcon.png"
#define FONT_PATH "assets/fonts/Pixellettersfull-BnJ5.ttf"

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
    SDL_Window* returnWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
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

    SDL_Window* mainWindow = createAndVerifySDLWindow(MAIN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    SDL_Renderer* mainWindowRenderer = createAndVerifySDLRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* pixelFont = createAndVerifyTTFFont(FONT_PATH, 24, mainWindow, mainWindowRenderer);

    TextRenderer textRenderer(pixelFont);
    TextureRenderer textureRenderer;

    TextureRenderer::TextureWithRect mainTitleTextureWithRect = textureRenderer.createAndVerifyTexture(100, 100, TITLE_IMAGE_PATH, mainWindow, mainWindowRenderer);
    SDL_Texture* mainTitleTexture = mainTitleTextureWithRect.texture;
    SDL_Rect mainTitleRect = mainTitleTextureWithRect.rectangle;

    SDL_Color white = {MAX_RGB_HEX, MAX_RGB_HEX, MAX_RGB_HEX, MAX_TRANSPARENCY_HEX};
    SDL_Color black = {0, 0, 0, MAX_RGB_HEX};
    SDL_Event event;

    bool quit = false;
    while(!quit)
    {
        SDL_SetRenderDrawColor(mainWindowRenderer, black.r, black.g, black.b, black.a);
        SDL_RenderClear(mainWindowRenderer);

        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
            if(event.type == SDL_QUIT) 
            {
                quit = true;
            }
        }
        textRenderer.renderHorizontallyCenteredText(mainWindowRenderer, "Horizontally Centered Text", MAIN_TITLE_VERTICAL_POSITION, white, mainWindow);
        textRenderer.renderVerticallyCenteredText(mainWindowRenderer, "Vertically Centered Text", 200, white, mainWindow);
        textRenderer.renderText(mainWindowRenderer, "Placed Text", 300, 300, white, mainWindow);

        SDL_RenderCopy(mainWindowRenderer, mainTitleTexture, NULL, &mainTitleRect);

        SDL_RenderPresent(mainWindowRenderer);
    }

    cleanup(pixelFont, mainWindow, mainWindowRenderer, mainTitleTexture);

    return 0;
}