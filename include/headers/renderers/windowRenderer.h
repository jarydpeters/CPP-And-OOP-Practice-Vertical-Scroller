#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H

#endif // WINDOW_RENDERER_H

#include <string>
#include <vector>

#include "globalValues.h"

class WindowRenderer
{
    public:

        /**
         * 
         */
        WindowRenderer(SDL_Window* win, SDL_Renderer* ren);

    protected:

        SDL_Window* window;
        SDL_Renderer* renderer;

        SDL_Window* getWindow();
        void setWindow(SDL_Window* win);

        SDL_Renderer* getRenderer();
        void setRenderer(SDL_Renderer* ren);

        std::string usersMonitorResolution;

        struct Resolution
        {
            int currentHorizontalResolution;
            int currentVerticalResolution;

            // Constructor with default arguments as well as 
            Resolution(int horizontalResolution = DEFAULT_HORIZONTAL_RESOLUTION, int verticalResolution = DEFAULT_VERTICAL_RESOLUTION)
                : currentHorizontalResolution(horizontalResolution), currentVerticalResolution(verticalResolution)
            {}
        };

        Resolution resolution;

        std::map<int, const std::string> windowedResolutionSelectionMap =
        {
            {0, "< 1280 x  720 >"},
            {1, "< 1600 x  900 >"},
            {2, "< 1920 x 1080 >"},
        };

        int menuTitleLogoVerticalPosition;

        int menuTextFirstVerticalPosition;
        int menuTextSecondVerticalPosition;
        int menuTextThirdVerticalPosition;
        int menuTextFourthVerticalPosition;
        int menuTextFifthVerticalPosition;

        std::vector<int> menuOptionsPositionVector = 
        {
            menuTextFirstVerticalPosition,
            menuTextSecondVerticalPosition,
            menuTextThirdVerticalPosition,
            menuTextFourthVerticalPosition,
            menuTextFifthVerticalPosition
        };

    private:

};