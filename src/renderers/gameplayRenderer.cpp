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

    setRedballHorizontalPosition(getCurrentHorizontalResolution() / 2.0);
    setRedballVerticalPosition((getCurrentVerticalResolution() * 9.0) / 10.0);
}

void GameplayRenderer::renderMainGame()
{
    SDL_GetWindowSize(getWindow(), &currentHorizontalResolution, &currentVerticalResolution);

    WindowRenderer::renderFPS(getRenderer(), getMenuSubtitleTextFont());
    //TODO: make setting
    WindowRenderer::renderScanLines(getWindow(), getRenderer(), true);

    renderRedball();

    SDL_RenderPresent(getRenderer());
}

void GameplayRenderer::renderRedball()
{
    redballTextureWithRect = textureRenderer.createAndVerifyTexture(
        100,//redballCurrentHorizontalPosition,
        100,//redballCurrentVerticalPosition,
        REDBALL_GAMEPLAY_SPRITE_PATH,
        getWindow(),
        getRenderer());

    redballTexture = redballTextureWithRect.texture;
    redballRect = redballTextureWithRect.rectangle;

    //set no interpolation scaling mode
    SDL_SetTextureScaleMode(redballTexture, SDL_ScaleModeNearest);

    redballRect.w *= FOUR_TIMES_SCALAR;
    redballRect.h *= FOUR_TIMES_SCALAR;

    SDL_RenderCopy(getRenderer(), redballTexture, NULL, &redballRect);

    if (redballTexture == nullptr) 
    {
    std::cout << "Failed to load redball texture" << std::endl;
    return;
    }

}

void GameplayRenderer::executeGameplayActionBasedOnEvent(const SDL_Event event)
{

}

void GameplayRenderer::destroyTextures()
{
    // // Destroy old textures to prevent memory leaks
    // if(mainMenuLogoTexture != nullptr) 
    // {
    //     SDL_DestroyTexture(mainMenuLogoTexture);
    //     mainMenuLogoTexture = nullptr;  // Prevent dangling pointer
    // }
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

int GameplayRenderer::getRedballHorizontalPosition()
{
    return redballCurrentHorizontalPosition;
}

void GameplayRenderer::setRedballHorizontalPosition(const int horizontalPosition)
{
    redballCurrentHorizontalPosition = horizontalPosition;
}

int GameplayRenderer::getRedballVerticalPosition()
{
    return redballCurrentVerticalPosition;
}

void GameplayRenderer::setRedballVerticalPosition(const int verticalPosition)
{
    redballCurrentVerticalPosition = verticalPosition;
}