#ifndef GAMEPLAY_RENDERER_H
#define GAMEPLAY_RENDERER_H

#include <iostream>
#include <glew.h>

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
        GameplayRenderer(SdlUtility sdlUtility,
            SDL_Window* win, 
            SDL_Renderer* ren,
            std::string titleFontPath,
            std::string subtitleFontPath,
            int titleTextPointSize,
            int subtitleTextPointSize);

        /**
         * 
         */
        void renderMainGame();

        /**
         * advances redballs position for next frame depending on user input
         */
        void executeGameplayActionBasedOnEvent(const SDL_Event event);

        void destroyTextures();

        SDL_Window* getMainGameWindow();
        void setMainGameWindow(SDL_Window* window);

        SDL_Renderer* getMainGameWindowRenderer();
        void setMainGameRenderer(SDL_Renderer* renderer);

        int getPlanesHorizontalPosition();
        void setPlanesHorizontalPosition(const int newHorizontalPosition);

        int getPlanesVerticalPosition();
        void setPlanesVerticalPosition(const int newVerticalPosition);

        int getRedballHorizontalPosition();
        void setRedballHorizontalPosition(const int horizontal);

        int getRedballVerticalPosition();
        void setRedballVerticalPosition(const int verticalPosition);

    private:

        TextureRenderer textureRenderer;

        TextureRenderer::TextureWithRect redballTextureWithRect;

        GLuint redballTexture = redballTextureWithRect.texture;
        SDL_Rect redballRect = redballTextureWithRect.rectangle;

        SDL_Window* mainGameWindow;
        SDL_Renderer* mainGameRenderer;

        int redballCurrentHorizontalPosition;
        int redballCurrentVerticalPosition;

        int currentHorizontalResolution;
        int currentVerticalResolution;

    
        /**
         * renders main player sprite during gameplay
         */
        void renderRedball();

};

#endif //GAMEPLAY_RENDERER_H