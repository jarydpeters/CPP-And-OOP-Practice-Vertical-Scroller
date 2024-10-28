#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "../include/headers/textRenderer.h"

TextRenderer::TextRenderer(TTF_Font* font) : font(font)
{

}

void TextRenderer::renderHorizontallyCenteredText(SDL_Renderer *renderer, const std::string &text, const int verticalPosition, const SDL_Color color, SDL_Window *window)
{
    int textWidth;
    int textHeight;

    ReadWindowDimensions(window);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    // Calculate the position for centered text
    int textHorizontalPosition = (windowWidth - textWidth) / 2;

    // Create a surface and texture for the text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Set the destination rectangle
    SDL_Rect textRect = 
    { 
        textHorizontalPosition, 
        verticalPosition, 
        textWidth, 
        textHeight 
    };

    // Render the text
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    cleanupSurfaceAndTexture(textSurface, textTexture);
}

void TextRenderer::renderVerticallyCenteredText(SDL_Renderer* renderer, const std::string& text, const int horizontalPosition, const SDL_Color color, SDL_Window* window) 
{
    int textWidth;
    int textHeight;

    ReadWindowDimensions(window);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    // Calculate the position for centered text
    int textVerticalPosition = (windowHeight - textHeight) / 2;

    // Create a surface and texture for the text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Set the destination rectangle
    SDL_Rect textRect = 
    { 
        horizontalPosition, 
        textVerticalPosition, 
        textWidth, 
        textHeight 
    };

    // Render the text
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    cleanupSurfaceAndTexture(textSurface, textTexture);
}

void TextRenderer::renderDoublyCenteredText(SDL_Renderer* renderer, const std::string& text, const SDL_Color color, SDL_Window* window) 
{
    int textWidth;
    int textHeight;

    ReadWindowDimensions(window);

    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    // Calculate the position for centered text
    int textHorizontalPosition = (windowWidth - textWidth) / 2;
    int textVerticalPosition = (windowHeight - textHeight) / 2;

    // Create a surface and texture for the text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Set the destination rectangle
    SDL_Rect textRect = 
    { 
        textHorizontalPosition, 
        textVerticalPosition, 
        textWidth, 
        textHeight 
    };

    // Render the text
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    cleanupSurfaceAndTexture(textSurface, textTexture);
}

void TextRenderer::changeFont(TTF_Font* newFont)
{
    font = newFont;
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

