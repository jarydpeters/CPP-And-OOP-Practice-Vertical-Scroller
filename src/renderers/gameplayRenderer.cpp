#include "gameplayRenderer.h"

GameplayRenderer::GameplayRenderer(SDL_Window* win, SDL_Renderer* ren)
    : WindowRenderer(win, ren)
{
    
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