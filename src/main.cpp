#include <iostream>
#include <map>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "textRenderer.h"
#include "textureRenderer.h"

constexpr int MAX_RGB_HEX = 0xFF;
constexpr int MAX_TRANSPARENCY_HEX = 0xFF;

constexpr int MAIN_TITLE_TEXT_VERTICAL_POSITION = 200;
constexpr int CONTINUE_TEXT_VERTICAL_POSITION = MAIN_TITLE_TEXT_VERTICAL_POSITION + 100;
constexpr int NEW_GAME_TEXT_VERTICAL_POSITION = CONTINUE_TEXT_VERTICAL_POSITION + 50;
constexpr int SETTINGS_TEXT_VERTICAL_POSITION = NEW_GAME_TEXT_VERTICAL_POSITION + 50;
constexpr int EXIT_TEXT_VERTICAL_POSITION = SETTINGS_TEXT_VERTICAL_POSITION + 50;

constexpr int CONTINUE_INDEX = 0;
constexpr int NEW_GAME_INDEX = 1;
constexpr int SETTINGS_INDEX = 2;
constexpr int EXIT_GAME_INDEX = 3;

constexpr int MAIN_MENU_INDEX = 0;
constexpr int SETTINGS_MENU_INDEX = 1;

#define MAIN_TITLE_TEXT "VERT SCROLLER"
#define CONTINUE_TEXT "CONTINUE"
#define NEW_GAME_TEXT "NEW GAME"
#define SETTINGS_TEXT "SETTINGS"
#define EXIT_TEXT "QUIT"

#define SETTINGS_MENU_TITLE_TEXT "SETTINGS"

#define TITLE_IMAGE_PATH "assets/sprites/menuSelectionIcon.png"
#define FONT_PATH "assets/fonts/Pixellettersfull-BnJ5.ttf"

// void cleanup(TTF_Font* font, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture)
// {
//     TTF_CloseFont(font);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_DestroyTexture(texture);
//     TTF_Quit();
//     SDL_Quit();
// }

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

    std::map<int, int> mainMenuOptionsMap;

    mainMenuOptionsMap[CONTINUE_INDEX] = CONTINUE_TEXT_VERTICAL_POSITION;
    mainMenuOptionsMap[NEW_GAME_INDEX] = NEW_GAME_TEXT_VERTICAL_POSITION;
    mainMenuOptionsMap[SETTINGS_INDEX] = SETTINGS_TEXT_VERTICAL_POSITION;
    mainMenuOptionsMap[EXIT_GAME_INDEX] = EXIT_TEXT_VERTICAL_POSITION;

    SDL_Window* mainWindow = createAndVerifySDLWindow(MAIN_TITLE_TEXT, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    SDL_Renderer* mainWindowRenderer = createAndVerifySDLRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* menuTextPixelFont = createAndVerifyTTFFont(FONT_PATH, 48, mainWindow, mainWindowRenderer);
    TTF_Font* subtextPixelFont = createAndVerifyTTFFont(FONT_PATH, 24, mainWindow, mainWindowRenderer);
    TextRenderer menuTextRenderer(menuTextPixelFont);
    TextRenderer menuSubtextRenderer(subtextPixelFont);

    TextureRenderer textureRenderer;
    TextureRenderer::TextureWithRect mainTitleMenuSelectionTextureWithRect;
    int currentlySelectedMainMenuOption = CONTINUE_INDEX;
    int currentlyDisplayedMenu = MAIN_MENU_INDEX;

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
            if(event.type == SDL_QUIT) 
            {
                quit = true;
            }
            switch(currentlyDisplayedMenu)
            {
                case MAIN_MENU_INDEX:
                {
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
                    {
                        currentlySelectedMainMenuOption--;
                        if(currentlySelectedMainMenuOption < CONTINUE_INDEX)
                        {
                            currentlySelectedMainMenuOption = EXIT_GAME_INDEX;
                        }
                    }   
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
                    {
                        currentlySelectedMainMenuOption++;
                        if(currentlySelectedMainMenuOption > EXIT_GAME_INDEX)
                        {
                            currentlySelectedMainMenuOption = CONTINUE_INDEX;
                        }
                    } 
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                    {
                        switch(currentlySelectedMainMenuOption)
                        {
                            case EXIT_GAME_INDEX:
                            {
                                quit = true;
                                break;
                            }
                            case SETTINGS_INDEX:
                            {
                                currentlyDisplayedMenu = SETTINGS_MENU_INDEX;
                                break;
                            }
                        }
                    } 

                    break;
                }
                case SETTINGS_MENU_INDEX:
                {
                    break;
                }
            }
        }

        switch(currentlyDisplayedMenu)
        {
            case MAIN_MENU_INDEX:
            {
                mainTitleMenuSelectionTextureWithRect = textureRenderer.createAndVerifyTexture(100, mainMenuOptionsMap[currentlySelectedMainMenuOption], TITLE_IMAGE_PATH, mainWindow, mainWindowRenderer);
                SDL_Texture* mainMenuSelectionTexture = mainTitleMenuSelectionTextureWithRect.texture;
                SDL_Rect mainMenuSelectionRect = mainTitleMenuSelectionTextureWithRect.rectangle;

                menuTextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_TITLE_TEXT, MAIN_TITLE_TEXT_VERTICAL_POSITION, white, mainWindow);

                menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, CONTINUE_TEXT, CONTINUE_TEXT_VERTICAL_POSITION, white, mainWindow);
                menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, NEW_GAME_TEXT, NEW_GAME_TEXT_VERTICAL_POSITION, white, mainWindow);
                menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_TEXT, SETTINGS_TEXT_VERTICAL_POSITION, white, mainWindow);
                menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, EXIT_TEXT,     EXIT_TEXT_VERTICAL_POSITION,     white, mainWindow);

                SDL_RenderCopy(mainWindowRenderer, mainMenuSelectionTexture, NULL, &mainMenuSelectionRect);
                SDL_RenderPresent(mainWindowRenderer);

                break;
            }
            case SETTINGS_MENU_INDEX:
            {
                // settingsMenuSelectionTextureWithRect = textureRenderer.createAndVerifyTexture(100, settingsMenuOptionsMap[currentlySelectedSettingsMenuOption], TITLE_IMAGE_PATH, mainWindow, mainWindowRenderer);
                SDL_Texture* settingsMenuSelectionTexture = mainTitleMenuSelectionTextureWithRect.texture;
                SDL_Rect settingsMenuSelectionRect = mainTitleMenuSelectionTextureWithRect.rectangle;

                menuTextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_TITLE_TEXT, MAIN_TITLE_TEXT_VERTICAL_POSITION, white, mainWindow);

                SDL_RenderCopy(mainWindowRenderer, settingsMenuSelectionTexture, NULL, &settingsMenuSelectionRect);
                SDL_RenderPresent(mainWindowRenderer);

                break;
            }
        }
    }

    //cleanup(subtextPixelFont, mainWindow, mainWindowRenderer, mainMenuSelectionTexture);

    return 0;
}