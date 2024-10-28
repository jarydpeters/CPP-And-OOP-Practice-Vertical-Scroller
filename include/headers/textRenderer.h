#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <../sdl/SDL.h>
#include <../sdl/SDL_ttf.h>
#include <string>

class TextRenderer
{
    public:

        /**
         * 
         */
        TextRenderer(TTF_Font* font);

        /**
         * Renders text centered horizontally and at a given vertical position
         *
         * \param renderer the rendering context
         * \param text the string to be rendered
         * \param verticalPosition the Y coordinate at which to render the text
         * \param color the color to render the text in
         * \param window
         * \returns void
         */
        void renderHorizontallyCenteredText(SDL_Renderer* renderer, const std::string& text, const int verticalPosition, const SDL_Color color, SDL_Window* window);

        /**
         * Renders text centered vertically and at a given horizontal position
         *
         * \param renderer the rendering context
         * \param text the string to be rendered
         * \param horizontalPosition the X coordinate at which to render the text
         * \param color the color to render the text in
         * \param window
         * \returns void
         */
        void renderVerticallyCenteredText(SDL_Renderer* renderer, const std::string& text, const int horizontalPosition, const SDL_Color color, SDL_Window* window);

        /**
         * Renders text centered vertically and horizontally
         *
         * \param renderer the rendering context
         * \param text the string to be rendered
         * \param color the color to render the text in
         * \param window
         * \returns void
         */
        void renderDoublyCenteredText(SDL_Renderer* renderer, const std::string& text, const SDL_Color color, SDL_Window* window);

        void changeFont(TTF_Font* newFont);

    private:

        TTF_Font* font;
        int windowWidth;
        int windowHeight;

        /**
         * frees surface and destroys texture
         * \param textSurface surface to be freed
         * \param textTexture texture to be destroyed
         * \returns void
         */
        void cleanupSurfaceAndTexture(SDL_Surface* textSurface, SDL_Texture* textTexture);

        /**
         * updates class parameters for window height and width
         * \param window window to measure dimensions of
         * \returns void
         */
        void ReadWindowDimensions(SDL_Window* window);

};


#endif // TEXT_RENDERER_H