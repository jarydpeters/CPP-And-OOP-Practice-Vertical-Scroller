#include <SDL.h>
#include <iostream>

int main(int argc, char*argv[])
{
    SDL_CreateWindow("VertScroller", 100, 100, 500, 500, 0);

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
    }

    return 0;
}