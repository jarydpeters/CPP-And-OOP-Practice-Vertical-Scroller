#ifndef SDL_UTILITY_H
#define SDL_UTILITY_H

#include <iostream>
#include <SDL_ttf.h>

class SdlUtility
{
    public:

        /**
         * default constructor
         */
        SdlUtility();

        /**
         * closes and destroys given parameters as well as quitting TTF and SDL
         *
         * \param font font to be closed
         * \param window window to be destroyed
         * \param renderer renderer to be destroyed
         * \param texture texture to be destroyed
         * \returns void
         */
        void cleanup(TTF_Font* font, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture);

        /**
         * checks for a successful initialization of SDL and TTF
         *
         * \returns true upon successful initialization of SDL and TTF, false otherwise
         */
        bool successfulSDLInit();

        /**
         * creates a centered SDL_Window based off of given parameters
         *
         * \param windowName given name for created window
         * \param horizontalSize horizontal size of window in pixels
         * \param verticalSize vertical size of window in pixels
         * \param flags SDL flags to create window with
         * \returns SDL_Window that has been created with given parameters
         */
        SDL_Window* createAndVerifySDLWindow(const char* windowName, const int horizontalSize, const int verticalSize, const Uint32 flags);

        /**
         * creates an SDL_Renderer based off of given parameters
         *
         * \param rendererWindow SDL_Window to attach renderer to
         * \param renderingDriverIndex index of rendering driver. -1 designates the first available index
         * \param flags SDL flags to create renderer with
         * \returns SDL_Renderer that has been created with given parameters
         */
        SDL_Renderer* createAndVerifySDLRenderer(SDL_Window* rendererWindow, const int renderingDriverIndex, const Uint32 flags);

        /**
         * creates a TTF_Font based off of given parameters
         *
         * \param fontFile filepath font is to be found at
         * \param fontPointSize size of font to be created
         * \param windowToRenderFontOn SDL_Window that font is to be attached to
         * \param windowRenderer SDL_Renderer that font is to be rendered with
         * \returns TTF_Font that has been created with given parameters
         */
        TTF_Font* createAndVerifyTTFFont(const char* fontFile, const int fontPointSize, SDL_Window* windowToRenderFontOn, SDL_Renderer* windowRenderer);
};

#endif // SDL_UTILITY_H