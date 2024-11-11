#ifndef TEXTURE_RENDERER_H
#define TEXTURE_RENDERER_H

#include <iostream>
#include <SDL_image.h>

#include "globalValues.h"

class TextureRenderer
{
    public:  

        /**
         * default constructor
         */
        TextureRenderer();

        struct TextureWithRect
        {
            SDL_Texture* texture;
            SDL_Rect rectangle;
        };

        /**
         * Creates and returns a texture placed within a sized rectangle based off of a filepath
         *
         * \param horizontalPosition horizontal position from left side of screen to place texture at
         * \param verticalPosition vertical position from top side of screen to place texture at
         * \param textureFilePath file path to texture that is to be generated
         * \param windowToRenderTextureOn SDL_Window that the texture is to be rendered on
         * \param windowRenderer SDL_Window_Renderer that the texture is to be rendered with
         * \returns TextureWithRect of texture found at filepath
         */
        TextureWithRect createAndVerifyTexture(const int horizontalPosition, const int verticalPosition, const char* textureFilePath, SDL_Window* windowToRenderTextureOn, SDL_Renderer* windowRenderer);

    private:

        SDL_Texture* texture;
        SDL_Rect rectangle;   
};

#endif // TEXTURE_RENDERER_H