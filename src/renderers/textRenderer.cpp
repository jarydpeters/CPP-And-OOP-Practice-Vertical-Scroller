#include <SDL_ttf.h>
#include <string>

#include "textRenderer.h"

TextRenderer::TextRenderer(TTF_Font* font) : font(font)
{

}

void TextRenderer::renderTextWithOpenGL(const std::string& text, const int textHorizontalPosition, const int textVerticalPosition, const SDL_Color color, SDL_Window* window)
{
    // Get window dimensions
    ReadWindowDimensions(window);
    
    // Get text width and height
    int textWidth, textHeight;
    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);
    
    // Create the SDL surface from the text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (textSurface == nullptr)
    {
        std::cout << "Error creating text surface: " << TTF_GetError() << std::endl;
        return;
    }

    // Generate OpenGL texture from surface
    GLuint textTexture = createOpenGLTextureFromSurface(textSurface);

    // Define the rectangle for OpenGL rendering
    SDL_Rect textRect = createTextRectangle(textHorizontalPosition, textVerticalPosition, textWidth, textHeight);

    // Render the texture with OpenGL
    renderQuadWithTexture(textTexture, textRect);

    // Cleanup
    cleanupSurfaceAndOpenGLTexture(textSurface, textTexture);
}

// Helper function to generate an OpenGL texture from SDL surface
GLuint TextRenderer::createOpenGLTextureFromSurface(SDL_Surface* surface)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the surface data into OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    return textureID;
}

void TextRenderer::renderText(const std::string& text, const int textHorizontalPosition, const int textVerticalPosition, const SDL_Color color, SDL_Window* window) 
{
    renderTextWithOpenGL(text, textHorizontalPosition, textVerticalPosition, color, window);
}

void TextRenderer::renderHorizontallyCenteredText(const std::string& text, const int textVerticalPosition, const SDL_Color color, SDL_Window* window)
{
    ReadWindowDimensions(window);
    int textWidth, textHeight;
    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);
    int textHorizontalPosition = (windowWidth - textWidth) / 2;

    renderTextWithOpenGL(text, textHorizontalPosition, textVerticalPosition, color, window);
}

void TextRenderer::renderVerticallyCenteredText(const std::string& text, const int textHorizontalPosition, const SDL_Color color, SDL_Window* window) 
{
    ReadWindowDimensions(window);
    int textWidth, textHeight;
    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);
    int textVerticalPosition = (windowHeight - textHeight) / 2;

    renderTextWithOpenGL(text, textHorizontalPosition, textVerticalPosition, color, window);
}

void TextRenderer::renderDoublyCenteredText(const std::string& text, const SDL_Color color, SDL_Window* window) 
{
    ReadWindowDimensions(window);
    int textWidth, textHeight;
    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);
    int textHorizontalPosition = (windowWidth - textWidth) / 2;
    int textVerticalPosition = (windowHeight - textHeight) / 2;

    renderTextWithOpenGL(text, textHorizontalPosition, textVerticalPosition, color, window);
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

void TextRenderer::ReadWindowDimensions(SDL_Window* window)
{
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}

void TextRenderer::cleanupSurfaceAndOpenGLTexture(SDL_Surface* surface, GLuint textureID)
{
    SDL_FreeSurface(surface);
    glDeleteTextures(1, &textureID);
}

