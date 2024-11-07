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

constexpr int MENU_TITLE_TEXT_VERTICAL_POSITION = 200;
constexpr int MENU_TEXT_FIRST_VERTICAL_POSITION = MENU_TITLE_TEXT_VERTICAL_POSITION + 100;
constexpr int MENU_TEXT_SECOND_VERTICAL_POSITION = MENU_TEXT_FIRST_VERTICAL_POSITION + 50;
constexpr int MENU_TEXT_THIRD_VERTICAL_POSITION = MENU_TEXT_SECOND_VERTICAL_POSITION + 50;
constexpr int MENU_TEXT_FOURTH_VERTICAL_POSITION = MENU_TEXT_THIRD_VERTICAL_POSITION + 50;

constexpr int CONTINUE_INDEX = 0;
constexpr int NEW_GAME_INDEX = 1;
constexpr int SETTINGS_INDEX = 2;
constexpr int EXIT_GAME_INDEX = 3;

constexpr int FULLSCREEN_INDEX = 0;
constexpr int MUSIC_VOLUME_INDEX = 1;
constexpr int SOUND_EFFECTS_VOLUME_INDEX = 2;
constexpr int RETURN_TO_MAIN_MENU_INDEX = 3;

constexpr int MAIN_MENU_INDEX = 0;
constexpr int SETTINGS_MENU_INDEX = 1;

constexpr int DEFAULT_HORIZONTAL_RESOLUTION = 1280;
constexpr int DEFAULT_VERTICAL_RESOLUTION = 720;


#define MAIN_MENU_TITLE_TEXT "VERT SCROLLER"
#define MAIN_MENU_CONTINUE_TEXT "CONTINUE"
#define MAIN_MENU_NEW_GAME_TEXT "NEW GAME"
#define MAIN_MENU_SETTINGS_TEXT "SETTINGS"
#define MAIN_MENU_EXIT_TEXT "QUIT"

#define SETTINGS_MENU_TITLE_TEXT "SETTINGS"
#define SETTINGS_MENU_FULLSCREEN_TEXT "FULL SCREEN"
#define SETTINGS_MENU_MUSIC_VOLUME_TEXT "MUSIC VOLUME"
#define SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT "SOUND EFFECTS VOLUME"
#define SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT "RETURN TO MAIN MENU"

#define SETTING_NOT_SELECTED_TEXT "[ ]"
#define SETTING_SELECTED_TEXT "[X]"

#define TITLE_IMAGE_PATH "assets/sprites/menuSelectionIcon.png"
#define FONT_PATH "assets/fonts/Pixellettersfull-BnJ5.ttf"

int currentlyDisplayedMenu = MAIN_MENU_INDEX;

int currentlySelectedMainMenuOption = CONTINUE_INDEX;
int currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;

int currentHorizontalResolution = DEFAULT_HORIZONTAL_RESOLUTION;
int currentVerticalResolution = DEFAULT_VERTICAL_RESOLUTION;

bool quitGame = false;
bool fullscreen = false;

SDL_Color white = {MAX_RGB_HEX, MAX_RGB_HEX, MAX_RGB_HEX, MAX_TRANSPARENCY_HEX};
SDL_Color black = {0, 0, 0, MAX_RGB_HEX};

SDL_Window* mainWindow;
SDL_Renderer* mainWindowRenderer;

SDL_Texture* mainMenuSelectionTexture;
SDL_Rect mainMenuSelectionRect;

TTF_Font* menuTextPixelFont;
TTF_Font* subtextPixelFont;

std::map<int, int> menuOptionsPositionMap;

TextureRenderer textureRenderer;
TextureRenderer::TextureWithRect menuSelectionTextureWithRect;

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

void initializeMenuOptionsMaps()
{
    menuOptionsPositionMap[CONTINUE_INDEX]  = MENU_TEXT_FIRST_VERTICAL_POSITION;
    menuOptionsPositionMap[NEW_GAME_INDEX]  = MENU_TEXT_SECOND_VERTICAL_POSITION;
    menuOptionsPositionMap[SETTINGS_INDEX]  = MENU_TEXT_THIRD_VERTICAL_POSITION;
    menuOptionsPositionMap[EXIT_GAME_INDEX] = MENU_TEXT_FOURTH_VERTICAL_POSITION;
}

void renderCurrentlyDisplayedMenu(int currentlyDisplayedMenu, TextRenderer menuTextRenderer, TextRenderer menuSubtextRenderer)
{
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            menuSelectionTextureWithRect = textureRenderer.createAndVerifyTexture(
                ((currentHorizontalResolution / 2) - 100), //set in middle of screen and then offset left to sit on left side of menu options
                (menuOptionsPositionMap[currentlySelectedMainMenuOption] - 10), //offset up to account for texture height
                TITLE_IMAGE_PATH, 
                mainWindow, 
                mainWindowRenderer);

            mainMenuSelectionTexture = menuSelectionTextureWithRect.texture;
            mainMenuSelectionRect = menuSelectionTextureWithRect.rectangle;

            menuTextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_TITLE_TEXT, MENU_TITLE_TEXT_VERTICAL_POSITION, white, mainWindow);

            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_CONTINUE_TEXT, MENU_TEXT_FIRST_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_NEW_GAME_TEXT, MENU_TEXT_SECOND_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_SETTINGS_TEXT, MENU_TEXT_THIRD_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_EXIT_TEXT, MENU_TEXT_FOURTH_VERTICAL_POSITION, white, mainWindow);

            SDL_RenderCopy(mainWindowRenderer, mainMenuSelectionTexture, NULL, &mainMenuSelectionRect);
            SDL_RenderPresent(mainWindowRenderer);

            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            menuSelectionTextureWithRect = textureRenderer.createAndVerifyTexture(
                ((currentHorizontalResolution / 2) - 200), //set in middle of screen and then offset left to sit on left side of menu options
                (menuOptionsPositionMap[currentlySelectedSettingsMenuOption] - 10), //offset up to account for texture height
                TITLE_IMAGE_PATH, 
                mainWindow, 
                mainWindowRenderer);

            SDL_Texture* settingsMenuSelectionTexture = menuSelectionTextureWithRect.texture;
            SDL_Rect settingsMenuSelectionRect = menuSelectionTextureWithRect.rectangle;

            menuTextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_TITLE_TEXT, MENU_TITLE_TEXT_VERTICAL_POSITION, white, mainWindow);

            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_FULLSCREEN_TEXT, MENU_TEXT_FIRST_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_MUSIC_VOLUME_TEXT, MENU_TEXT_SECOND_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT, MENU_TEXT_THIRD_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT, MENU_TEXT_FOURTH_VERTICAL_POSITION, white, mainWindow);

            //TODO: MAKE OPTION ENABLED BUTTON DYNAMIC TO WINDOW SIZE
            SDL_GetWindowSize(mainWindow, &currentHorizontalResolution, &currentVerticalResolution);

            menuSubtextRenderer.renderText(mainWindowRenderer, (fullscreen ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), (currentHorizontalResolution * 2 / 3), MENU_TEXT_FIRST_VERTICAL_POSITION, white, mainWindow);

            SDL_RenderCopy(mainWindowRenderer, settingsMenuSelectionTexture, NULL, &settingsMenuSelectionRect);
            SDL_RenderPresent(mainWindowRenderer);

            break;
        }
    }
}

void executeActionBasedOnEvent(SDL_Event event)
{
    if(event.type == SDL_QUIT) 
    {
        quitGame = true;
    }
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            //TODO: add mouse controls
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
                        quitGame = true;
                        break;
                    }
                    case SETTINGS_INDEX:
                    {
                        currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;
                        currentlyDisplayedMenu = SETTINGS_MENU_INDEX;
                        break;
                    }
                }
            } 
            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            //TODO: add mouse controls
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
            {
                currentlySelectedSettingsMenuOption--;
                if(currentlySelectedSettingsMenuOption < FULLSCREEN_INDEX)
                {
                    currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;
                }
            }   
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
            {
                currentlySelectedSettingsMenuOption++;
                if(currentlySelectedSettingsMenuOption > RETURN_TO_MAIN_MENU_INDEX)
                {
                    currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;
                }
            } 
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                switch(currentlySelectedSettingsMenuOption)
                {
                    case FULLSCREEN_INDEX:
                    {
                        fullscreen = !fullscreen;
                        SDL_SetWindowFullscreen(mainWindow, (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
                        break;
                    }
                    case RETURN_TO_MAIN_MENU_INDEX:
                    {
                        currentlySelectedMainMenuOption = CONTINUE_INDEX;
                        currentlyDisplayedMenu = MAIN_MENU_INDEX;
                        break;
                    }
                }
            } 
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                currentlySelectedMainMenuOption = CONTINUE_INDEX;
                currentlyDisplayedMenu = MAIN_MENU_INDEX;
            }   
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    if(!successfulSDLInit())
    {
        return -1;
    }

    mainWindow = createAndVerifySDLWindow(
        MAIN_MENU_TITLE_TEXT, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        DEFAULT_HORIZONTAL_RESOLUTION, 
        DEFAULT_VERTICAL_RESOLUTION, 
        SDL_WINDOW_OPENGL);

    SDL_SetWindowResizable(mainWindow, SDL_bool::SDL_FALSE);

    mainWindowRenderer = createAndVerifySDLRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    menuTextPixelFont = createAndVerifyTTFFont(FONT_PATH, 48, mainWindow, mainWindowRenderer);
    subtextPixelFont = createAndVerifyTTFFont(FONT_PATH, 24, mainWindow, mainWindowRenderer);

    TextRenderer menuTextRenderer(menuTextPixelFont);
    TextRenderer menuSubtextRenderer(subtextPixelFont);

    initializeMenuOptionsMaps();

    SDL_Event event;

    while(!quitGame)
    {
        SDL_SetRenderDrawColor(mainWindowRenderer, black.r, black.g, black.b, black.a);
        SDL_RenderClear(mainWindowRenderer);

        while (SDL_PollEvent(&event))
        {
            executeActionBasedOnEvent(event);
        }

        renderCurrentlyDisplayedMenu(currentlyDisplayedMenu, menuTextRenderer, menuSubtextRenderer);
    }

    cleanup(subtextPixelFont, mainWindow, mainWindowRenderer, mainMenuSelectionTexture);

    return 0;
}