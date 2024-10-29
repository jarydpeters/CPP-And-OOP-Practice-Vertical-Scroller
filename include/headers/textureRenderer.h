#ifndef TEXTURE_RENDERER_H
#define TEXTURE_RENDERER_H

#include <SDL.h>
#include <SDL_image.h>

class TextureRenderer
{
    public:  

        TextureRenderer();

        struct TextureWithRect
        {
            SDL_Texture* texture;
            SDL_Rect rectangle;
        };

        TextureWithRect createAndVerifyTexture(const int horizontalPosition, const int verticalPosition, const char* textureFilePath, SDL_Window* windowToRenderTextureOn, SDL_Renderer* windowRenderer);

    private:

        SDL_Texture* texture;
        SDL_Rect rectangle;   
};

#endif // TEXTURE_RENDERER_H