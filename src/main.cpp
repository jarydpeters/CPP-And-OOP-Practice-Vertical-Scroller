#include "commonDefines.h"
#include "menuRenderer.h"
#include "sdlUtility.h"
#include "textRenderer.h"

MenuRenderer menuRenderer;
SdlUtility sdlUtility;

int main(int argc, char* argv[])
{
    if(!sdlUtility.successfulSDLInit())
    {
        return -1;
    }

    menuRenderer.setMainWindow(sdlUtility.createAndVerifySDLWindow(
        "mainWindow", 
        DEFAULT_HORIZONTAL_RESOLUTION, 
        DEFAULT_VERTICAL_RESOLUTION, 
        SDL_WINDOW_OPENGL));

    SDL_SetWindowResizable(menuRenderer.getMainWindow(), SDL_bool::SDL_FALSE);

    menuRenderer.setMainWindowRenderer(sdlUtility.createAndVerifySDLRenderer(menuRenderer.getMainWindow(), -1, SDL_RENDERER_ACCELERATED));
    menuRenderer.setMenuTitleTextFont(sdlUtility.createAndVerifyTTFFont(FONT_PATH, TITLE_TEXT_POINT_SIZE, menuRenderer.getMainWindow(), menuRenderer.getMainWindowRenderer()));
    menuRenderer.setMenuSubtitleTextFont(sdlUtility.createAndVerifyTTFFont(FONT_PATH, SUBTITLE_TEXT_POINT_SIZE, menuRenderer.getMainWindow(), menuRenderer.getMainWindowRenderer()));

    TextRenderer menuTitleTextRenderer(menuRenderer.getMenuTitleTextFont());
    TextRenderer menuSubtextRenderer(menuRenderer.getMenuSubtitleTextFont());

    SDL_Event event;

    while(!menuRenderer.quitGame)
    {
        SDL_SetRenderDrawColor(menuRenderer.getMainWindowRenderer(), black.r, black.g, black.b, black.a);
        SDL_RenderClear(menuRenderer.getMainWindowRenderer());

        while (SDL_PollEvent(&event))
        {
            menuRenderer.executeMenuActionBasedOnEvent(event);
        }
        
        menuRenderer.renderCurrentlyDisplayedMenu(menuRenderer.getCurrentlyDisplayedMenu(), menuTitleTextRenderer, menuSubtextRenderer);
    }

    sdlUtility.cleanup(menuRenderer.getMenuSubtitleTextFont(), menuRenderer.getMainWindow(), menuRenderer.getMainWindowRenderer(), menuRenderer.getMenuSelectionIconTexture());

    return 0;
}