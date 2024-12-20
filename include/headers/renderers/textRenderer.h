#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <glew.h>
#include <iostream>
#include <SDL_ttf.h>
#include <string>

#include "openGLUtility.h"
#include "windowRenderer.h"

class TextRenderer
{
    public:

        /**
         * constructor
         * \param font font to initialize textRenderer with. Can be changed with changeFont
         */
        TextRenderer(TTF_Font* font);

        /**
         * Renders text centered at a given horizontal and vertical position
         *
         * \param text the string to be rendered
         * \param textHorizontalPosition the X coordinate at which to render the text
         * \param textVerticalPosition the Y coordinate at which to render the text
         * \param color the color to render the text in
         * \param window
         * \returns void
         */
        void renderTextWithOpenGL(const std::string& text, const int textHorizontalPosition, const int textVerticalPosition, const SDL_Color color, SDL_Window* window);

        /**
         * 
         */
        void renderText(const std::string& text, const int textHorizontalPosition, const int textVerticalPosition, const SDL_Color color, SDL_Window* window);

        /**
         * 
         */
        void renderHorizontallyCenteredText(const std::string& text, const int textVerticalPosition, const SDL_Color color, SDL_Window* window);
        
        /**
         * 
         */
        void renderVerticallyCenteredText(const std::string& text, const int textHorizontalPosition, const SDL_Color color, SDL_Window* window);
        
        /**
         * 
         */
        void renderDoublyCenteredText(const std::string& text, const SDL_Color color, SDL_Window* window);

        /**
         * changes font of created TextRenderer
         * \param newFont new font to be used
         * \returns void
         */
        void changeFont(TTF_Font* newFont);

    private:

        TTF_Font* font;
        
        int windowWidth;
        int windowHeight;

        /**
         * creates an SDL_Rect of size and position of given text paramters
         * 
         * \param surface surface to generate texture from
         * \returns GLuint of texture created from the given position and size
         */
        GLuint createOpenGLTextureFromSurface(SDL_Surface* surface);

        /**
         * frees surface and destroys texture
         * 
         * \param surface surface to be freed
         * \param textureID texture to be destroyed
         * \returns void
         */
        void cleanupSurfaceAndOpenGLTexture(SDL_Surface* surface, GLuint textureID);

        /**
         * updates class parameters for window height and width
         * 
         * \param window window to measure dimensions of
         * \returns void
         */
        void ReadWindowDimensions(SDL_Window* window);

        /**
         * 
         */
        SDL_Rect createTextRectangle(const int textHorizontalPosition, const int textVerticalPosition, const int textWidth, const int textHeight);
};

#endif // TEXT_RENDERER_H