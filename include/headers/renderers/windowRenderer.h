#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H

#endif // WINDOW_RENDERER_H

#include "globalValues.h"

class WindowRenderer
{
    public:

    /**
     * 
     */
    WindowRenderer(SDL_Window* win, SDL_Renderer* ren);

    protected:

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Window* getWindow();
    void setWindow(SDL_Window* win);

    SDL_Renderer* getRenderer();
    void setRenderer(SDL_Renderer* ren);

    private:

};