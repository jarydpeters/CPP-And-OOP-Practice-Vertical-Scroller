#ifndef TEXTURE_RENDERER_H
#define TEXTURE_RENDERER_H

#include <glew.h>
#include <iostream>
#include <SDL_image.h>

#include "stb_image.h"

class TextureRenderer
{
    public:  

        /**
         * default constructor
         */
        TextureRenderer();

        struct TextureWithRect
        {
            GLuint  texture;
            SDL_Rect rectangle;
        };

        /**
         * 
         */
        TextureRenderer::TextureWithRect createAndVerifyOpenGLTexture(int xOffset, int yOffset, const char* imagePath);

        /**
         * 
         */
        void renderTexture(const TextureWithRect& textureWithRect);

    private:

        GLuint textureID;  // Store OpenGL texture ID at the class level
        SDL_Rect rectangle;   
};

#endif // TEXTURE_RENDERER_H