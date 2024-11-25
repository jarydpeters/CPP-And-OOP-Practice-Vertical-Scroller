#include "mainGameRenderer.h"

MainGameRenderer::MainGameRenderer()
{
    
}

void MainGameRenderer::renderMainGame()
{

}

SDL_Window* MainGameRenderer::getMainGameWindow()
{
    return mainGameWindow;
}

void MainGameRenderer::setMainGameWindow(SDL_Window* window)
{
    mainGameWindow = window;
}

SDL_Renderer* MainGameRenderer::getMainGameWindowRenderer()
{
    return mainGameRenderer;
}

void MainGameRenderer::setMainGameRenderer(SDL_Renderer* renderer)
{
    mainGameRenderer = renderer;
}