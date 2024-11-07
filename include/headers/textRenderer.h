#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

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
         * \param renderer the rendering context
         * \param text the string to be rendered
         * \param textHorizontalPosition the X coordinate at which to render the text
         * \param textVerticalPosition the Y coordinate at which to render the text
         * \param color the color to render the text in
         * \param window
         * \returns void
         */
        void renderText(SDL_Renderer* renderer, const std::string& text, const int textHorizontalPosition, const int textVerticalPosition, const SDL_Color color, SDL_Window* window);

        /**
         * Renders text centered Horizontaly and at a given vertical position
         *
         * \param renderer the rendering context
         * \param text the string to be rendered
         * \param textVerticalPosition the Y coordinate at which to render the text
         * \param color the color to render the text in
         * \param window
         * \returns void
         */
        void renderHorizontallyCenteredText(SDL_Renderer* renderer, const std::string& text, const int textVerticalPosition, const SDL_Color color, SDL_Window* window);

        /**
         * Renders text centered Verticaly and at a given horizontal position
         *
         * \param renderer the rendering context
         * \param text the string to be rendered
         * \param textHorizontalPosition the X coordinate at which to render the text
         * \param color the color to render the text in
         * \param window
         * \returns void
         */
        void renderVerticallyCenteredText(SDL_Renderer* renderer, const std::string& text, const int textHorizontalPosition, const SDL_Color color, SDL_Window* window);

        /**
         * Renders text centered Verticaly and Horizontaly
         *
         * \param renderer the rendering context
         * \param text the string to be rendered
         * \param color the color to render the text in
         * \param window
         * \returns void
         */
        void renderDoublyCenteredText(SDL_Renderer* renderer, const std::string& text, const SDL_Color color, SDL_Window* window);

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
         * \param textHorizontalPosition horizontal position of text
         * \param textVerticalPosition vertical position of text
         * \param textWidth width of text
         * \param textHeight height of text
         * \returns SDL_Rect of text created from the given position and size
         */
        SDL_Rect createTextRectangle(const int textHorizontalPosition, const int textVerticalPosition, const int textWidth, const int textHeight);

        /**
         * frees surface and destroys texture
         * 
         * \param textSurface surface to be freed
         * \param textTexture texture to be destroyed
         * \returns void
         */
        void cleanupSurfaceAndTexture(SDL_Surface* textSurface, SDL_Texture* textTexture);

        /**
         * updates class parameters for window height and width
         * 
         * \param window window to measure dimensions of
         * \returns void
         */
        void ReadWindowDimensions(SDL_Window* window);
};

#endif // TEXT_RENDERER_H