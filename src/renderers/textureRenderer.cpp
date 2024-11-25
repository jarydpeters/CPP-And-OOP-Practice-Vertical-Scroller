#include "textureRenderer.h"

TextureRenderer::TextureRenderer()
    : texture(nullptr), rectangle{0, 0, 0, 0}
{

}

TextureRenderer::TextureWithRect TextureRenderer::createAndVerifyTexture(const int horizontalPosition, const int verticalPosition, const char* textureFilePath, SDL_Window* windowToRenderTextureOn, SDL_Renderer* windowRenderer)
{
    TextureRenderer::TextureWithRect textureWithRect = 
    {
        nullptr,
        { 0, 0, 0, 0}
    };

    SDL_Texture* returnTexture = IMG_LoadTexture(windowRenderer, textureFilePath);
    if(returnTexture == nullptr) 
    {
        std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(windowRenderer);
        SDL_DestroyWindow(windowToRenderTextureOn);
        SDL_Quit();
    }

    textureWithRect.texture = returnTexture;

    int textureWidth;
    int textureHeight;
    SDL_QueryTexture(returnTexture, NULL, NULL, &textureWidth, &textureHeight);
    SDL_Rect textureRect =
    {
        horizontalPosition,
        verticalPosition,
        textureWidth,
        textureHeight 
    };

    textureWithRect.rectangle = textureRect;

    return textureWithRect;
}