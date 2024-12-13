#include "gameplayRenderer.h"

GameplayRenderer::GameplayRenderer(SdlUtility sdlUtility,
            SDL_Window* win, 
            SDL_Renderer* ren,
            std::string titleFontPath,
            std::string subtitleFontPath,
            int titleTextPointSize,
            int subtitleTextPointSize)
    : WindowRenderer(win, ren)
{
    SDL_SetWindowResizable(getWindow(), SDL_bool::SDL_FALSE);

    TTF_Font* titleFont = sdlUtility.createAndVerifyTTFFont(FONT_PATH, 
        TITLE_TEXT_POINT_SIZE, 
        getWindow(), 
        getRenderer());

    TTF_Font* subtitleFont = sdlUtility.createAndVerifyTTFFont(FONT_PATH, 
        SUBTITLE_TEXT_POINT_SIZE, 
        getWindow(), 
        getRenderer());

    setMenuTitleTextFont(titleFont);
    setMenuSubtitleTextFont(subtitleFont);

    settingsManager.loadSavedSettings();
}

void GameplayRenderer::renderMainGame()
{

}

SDL_Window* GameplayRenderer::getMainGameWindow()
{
    return mainGameWindow;
}

void GameplayRenderer::setMainGameWindow(SDL_Window* window)
{
    mainGameWindow = window;
}

SDL_Renderer* GameplayRenderer::getMainGameWindowRenderer()
{
    return mainGameRenderer;
}

void GameplayRenderer::setMainGameRenderer(SDL_Renderer* renderer)
{
    mainGameRenderer = renderer;
}