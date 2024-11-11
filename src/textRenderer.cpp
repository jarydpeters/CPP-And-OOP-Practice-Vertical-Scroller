#include "globalValues.h"
#include <SDL_ttf.h>
#include <string>

#include "textRenderer.h"

TextRenderer::TextRenderer(TTF_Font* font) : font(font)
{

}

void TextRenderer::renderText(SDL_Renderer* renderer, const std::string& text, const int textHorizontalPosition, const int textVerticalPosition, const SDL_Color color, SDL_Window* window) 
{
    int textWidth;
    int textHeight;

    ReadWindowDimensions(window);

    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = createTextRectangle(textHorizontalPosition, textVerticalPosition, textWidth, textHeight);

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    cleanupSurfaceAndTexture(textSurface, textTexture);
}

void TextRenderer::renderHorizontallyCenteredText(SDL_Renderer *renderer, const std::string &text, const int textVerticalPosition, const SDL_Color color, SDL_Window *window)
{
    int textWidth;
    int textHeight;

    ReadWindowDimensions(window);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    int textHorizontalPosition = (windowWidth - textWidth) / 2;
    SDL_Rect textRect = createTextRectangle(textHorizontalPosition, textVerticalPosition, textWidth, textHeight);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    cleanupSurfaceAndTexture(textSurface, textTexture);
}

void TextRenderer::renderVerticallyCenteredText(SDL_Renderer* renderer, const std::string& text, const int textHorizontalPosition, const SDL_Color color, SDL_Window* window) 
{
    int textWidth;
    int textHeight;

    ReadWindowDimensions(window);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    int textVerticalPosition = (windowHeight - textHeight) / 2;
    SDL_Rect textRect = createTextRectangle(textHorizontalPosition, textVerticalPosition, textWidth, textHeight);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    cleanupSurfaceAndTexture(textSurface, textTexture);
}

void TextRenderer::renderDoublyCenteredText(SDL_Renderer* renderer, const std::string& text, const SDL_Color color, SDL_Window* window) 
{
    int textWidth;
    int textHeight;

    ReadWindowDimensions(window);

    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    int textHorizontalPosition = (windowWidth - textWidth) / 2;
    int textVerticalPosition = (windowHeight - textHeight) / 2;
    SDL_Rect textRect = createTextRectangle(textHorizontalPosition, textVerticalPosition, textWidth, textHeight);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    cleanupSurfaceAndTexture(textSurface, textTexture);
}

void TextRenderer::changeFont(TTF_Font* newFont)
{
    font = newFont;
}

SDL_Rect TextRenderer::createTextRectangle(const int textHorizontalPosition, const int textVerticalPosition, const int textWidth, const int textHeight)
{
    SDL_Rect textRect = 
    { 
        textHorizontalPosition, 
        textVerticalPosition, 
        textWidth, 
        textHeight 
    };
    return textRect;
}

void TextRenderer::cleanupSurfaceAndTexture(SDL_Surface* textSurface, SDL_Texture* textTexture)
{
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void TextRenderer::ReadWindowDimensions(SDL_Window* window)
{
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}

