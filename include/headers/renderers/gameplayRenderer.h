#ifndef MAIN_GAME_RENDERER_H
#define MAIN_GAME_RENDERER_H

#include "assetFilePaths.h"
#include "colorDefines.h"
#include "textRenderer.h"
#include "textureRenderer.h"
#include "windowRenderer.h"

class GameplayRenderer : public WindowRenderer
{
    public:

        /**
         * constructor
         */
        GameplayRenderer(SDL_Window* win, SDL_Renderer* ren);

        /**
         * 
         */
        void renderMainGame();

        SDL_Window* getMainGameWindow();
        void setMainGameWindow(SDL_Window* window);

        SDL_Renderer* getMainGameWindowRenderer();
        void setMainGameRenderer(SDL_Renderer* renderer);

        int getPlanesHorizontalPosition();
        void setPlanesHorizontalPosition(const int newHorizontalPosition);

        int getPlanesVerticalPosition();
        void setPlanesVerticalPosition(const int newVerticalPosition);

    private:

        TextureRenderer textureRenderer;

        SDL_Window* mainGameWindow;
        SDL_Renderer* mainGameRenderer;

        int planesCurrentHorizontalPosition;
        int planesCurrentVerticalPosition;
};

#endif //MAIN_GAME_RENDERER_H