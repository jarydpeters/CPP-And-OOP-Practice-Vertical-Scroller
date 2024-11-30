#include "windowRenderer.h"

bool WindowRenderer::quitGame = false;
int WindowRenderer::currentScreen = MAIN_MENU_SCREEN;

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