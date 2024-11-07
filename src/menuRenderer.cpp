#include "menuRenderer.h"

MenuRenderer::MenuRenderer()
{

}

void MenuRenderer::renderCurrentlyDisplayedMenu(const int currentlyDisplayedMenu, TextRenderer menuTitleTextRenderer, TextRenderer menuSubtextRenderer)
{
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            menuSelectionIconTextureWithRect = textureRenderer.createAndVerifyTexture(
                ((currentHorizontalResolution / 2) - 100), //set in middle of screen and then offset left to sit on left side of menu options
                (menuOptionsPositionMap[currentlySelectedMainMenuOption] - 10), //offset up to account for texture height
                TITLE_IMAGE_PATH, 
                mainWindow, 
                mainWindowRenderer);

            menuSelectionIconTexture = menuSelectionIconTextureWithRect.texture;
            mainMenuSelectionRect = menuSelectionIconTextureWithRect.rectangle;

            menuTitleTextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_TITLE_TEXT, MENU_TITLE_TEXT_VERTICAL_POSITION, white, mainWindow);

            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_CONTINUE_TEXT, MENU_TEXT_FIRST_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_NEW_GAME_TEXT, MENU_TEXT_SECOND_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_SETTINGS_TEXT, MENU_TEXT_THIRD_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_EXIT_TEXT, MENU_TEXT_FOURTH_VERTICAL_POSITION, white, mainWindow);

            SDL_RenderCopy(mainWindowRenderer, menuSelectionIconTexture, NULL, &mainMenuSelectionRect);
            SDL_RenderPresent(mainWindowRenderer);

            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            menuSelectionIconTextureWithRect = textureRenderer.createAndVerifyTexture(
                ((currentHorizontalResolution / 2) - 200), //set in middle of screen and then offset left to sit on left side of menu options
                (menuOptionsPositionMap[currentlySelectedSettingsMenuOption] - 10), //offset up to account for texture height
                TITLE_IMAGE_PATH, 
                mainWindow, 
                mainWindowRenderer);

            SDL_Texture* settingsMenuSelectionTexture = menuSelectionIconTextureWithRect.texture;
            SDL_Rect settingsMenuSelectionRect = menuSelectionIconTextureWithRect.rectangle;

            menuTitleTextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_TITLE_TEXT, MENU_TITLE_TEXT_VERTICAL_POSITION, white, mainWindow);

            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_FULLSCREEN_TEXT, MENU_TEXT_FIRST_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_MUSIC_VOLUME_TEXT, MENU_TEXT_SECOND_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT, MENU_TEXT_THIRD_VERTICAL_POSITION, white, mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT, MENU_TEXT_FOURTH_VERTICAL_POSITION, white, mainWindow);

            //TODO: MAKE OPTION ENABLED BUTTON DYNAMIC TO WINDOW SIZE
            SDL_GetWindowSize(mainWindow, &currentHorizontalResolution, &currentVerticalResolution);

            menuSubtextRenderer.renderText(mainWindowRenderer, (fullscreen ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), (currentHorizontalResolution * 2 / 3), MENU_TEXT_FIRST_VERTICAL_POSITION, white, mainWindow);

            SDL_RenderCopy(mainWindowRenderer, settingsMenuSelectionTexture, NULL, &settingsMenuSelectionRect);
            SDL_RenderPresent(mainWindowRenderer);

            break;
        }
    }
}

void MenuRenderer::executeMenuActionBasedOnEvent(const SDL_Event event)
{
    if(event.type == SDL_QUIT) 
    {
        quitGame = true;
    }
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            //TODO: add mouse controls
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
            {
                currentlySelectedMainMenuOption--;
                if(currentlySelectedMainMenuOption < CONTINUE_INDEX)
                {
                    currentlySelectedMainMenuOption = EXIT_GAME_INDEX;
                }
            }   
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
            {
                currentlySelectedMainMenuOption++;
                if(currentlySelectedMainMenuOption > EXIT_GAME_INDEX)
                {
                    currentlySelectedMainMenuOption = CONTINUE_INDEX;
                }
            } 
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                switch(currentlySelectedMainMenuOption)
                {
                    case EXIT_GAME_INDEX:
                    {
                        quitGame = true;
                        break;
                    }
                    case SETTINGS_INDEX:
                    {
                        currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;
                        currentlyDisplayedMenu = SETTINGS_MENU_INDEX;
                        break;
                    }
                }
            } 
            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            //TODO: add mouse controls
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
            {
                currentlySelectedSettingsMenuOption--;
                if(currentlySelectedSettingsMenuOption < FULLSCREEN_INDEX)
                {
                    currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;
                }
            }   
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
            {
                currentlySelectedSettingsMenuOption++;
                if(currentlySelectedSettingsMenuOption > RETURN_TO_MAIN_MENU_INDEX)
                {
                    currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;
                }
            } 
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                switch(currentlySelectedSettingsMenuOption)
                {
                    case FULLSCREEN_INDEX:
                    {
                        fullscreen = !fullscreen;
                        SDL_SetWindowFullscreen(mainWindow, (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
                        break;
                    }
                    case RETURN_TO_MAIN_MENU_INDEX:
                    {
                        currentlySelectedMainMenuOption = CONTINUE_INDEX;
                        currentlyDisplayedMenu = MAIN_MENU_INDEX;
                        break;
                    }
                }
            } 
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                currentlySelectedMainMenuOption = CONTINUE_INDEX;
                currentlyDisplayedMenu = MAIN_MENU_INDEX;
            }   
            break;
        }
    }
}

int MenuRenderer::getCurrentlyDisplayedMenu()
{
    return currentlyDisplayedMenu;
}

SDL_Window* MenuRenderer::getMainWindow()
{
    return mainWindow;
}

void MenuRenderer::setMainWindow(SDL_Window* window)
{
    mainWindow = window;
}

SDL_Renderer* MenuRenderer::getMainWindowRenderer()
{
    return mainWindowRenderer;
}

void MenuRenderer::setMainWindowRenderer(SDL_Renderer* renderer)
{
    mainWindowRenderer = renderer;
}

TTF_Font* MenuRenderer::getMenuTitleTextFont()
{
    return menuTitleFont;
}

void MenuRenderer::setMenuTitleTextFont(TTF_Font* font)
{
    menuTitleFont = font;
}

TTF_Font* MenuRenderer::getMenuSubtitleTextFont()
{
    return menuSubtitleFont;
}

void MenuRenderer::setMenuSubtitleTextFont(TTF_Font* font)
{
    menuSubtitleFont = font;
}

SDL_Texture* MenuRenderer::getMenuSelectionIconTexture()
{
    return menuSelectionIconTexture;
}