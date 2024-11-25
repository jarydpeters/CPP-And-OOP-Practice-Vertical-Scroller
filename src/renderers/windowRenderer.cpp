#include "windowRenderer.h"

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