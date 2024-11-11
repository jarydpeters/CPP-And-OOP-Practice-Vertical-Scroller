#include "menuRenderer.h"

MenuRenderer::MenuRenderer()
{
    updateUIPositions();
}

void MenuRenderer::renderCurrentlyDisplayedMenu(const int currentlyDisplayedMenu, TextRenderer menuTitleTextRenderer, TextRenderer menuSubtextRenderer)
{
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            menuSelectionIconTextureWithRect = textureRenderer.createAndVerifyTexture(
                0, //place on far left side of screen
                (menuOptionsPositionMap[currentlySelectedMainMenuOption] - 6), //offset up to account for texture height
                MENU_SELECTION_ICON_IMAGE_PATH, 
                mainWindow, 
                mainWindowRenderer);

            menuSelectionIconTexture = menuSelectionIconTextureWithRect.texture;
            mainMenuSelectionRect = menuSelectionIconTextureWithRect.rectangle;

            //render menu option selection rectangle first so text appears on top of it
            SDL_RenderCopy(mainWindowRenderer, menuSelectionIconTexture, NULL, &mainMenuSelectionRect);

            menuTitleTextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, MAIN_MENU_TITLE_TEXT, menuTitleTextVerticalPosition, white, mainWindow);

            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, 
                MAIN_MENU_CONTINUE_TEXT, 
                menuTextFirstVerticalPosition, 
                ((currentlySelectedMainMenuOption == CONTINUE_INDEX) ? black : white), 
                mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, 
                MAIN_MENU_NEW_GAME_TEXT, 
                menuTextSecondVerticalPosition, 
                ((currentlySelectedMainMenuOption == NEW_GAME_INDEX) ? black : white), 
                mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, 
                MAIN_MENU_SETTINGS_TEXT, 
                menuTextThirdVerticalPosition, 
                ((currentlySelectedMainMenuOption == SETTINGS_INDEX) ? black : white), 
                mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, 
                MAIN_MENU_EXIT_TEXT, 
                menuTextFourthVerticalPosition, 
                ((currentlySelectedMainMenuOption == EXIT_GAME_INDEX) ? black : white), 
                mainWindow);

            SDL_RenderPresent(mainWindowRenderer);

            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            menuSelectionIconTextureWithRect = textureRenderer.createAndVerifyTexture(
                0, //place on far left side of screen
                (menuOptionsPositionMap[currentlySelectedSettingsMenuOption] - 6), //offset up to account for texture height
                MENU_SELECTION_ICON_IMAGE_PATH, 
                mainWindow, 
                mainWindowRenderer);

            SDL_Texture* settingsMenuSelectionTexture = menuSelectionIconTextureWithRect.texture;
            SDL_Rect settingsMenuSelectionRect = menuSelectionIconTextureWithRect.rectangle;

            //render menu option selection rectangle first so text appears on top of it
            SDL_RenderCopy(mainWindowRenderer, settingsMenuSelectionTexture, NULL, &settingsMenuSelectionRect);

            menuTitleTextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, SETTINGS_MENU_TITLE_TEXT, menuTitleTextVerticalPosition, white, mainWindow);

            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, 
                SETTINGS_MENU_FULLSCREEN_TEXT, 
                menuTextFirstVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == FULLSCREEN_INDEX) ? black : white), 
                mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, 
                SETTINGS_MENU_MUSIC_VOLUME_TEXT, 
                menuTextSecondVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == MUSIC_VOLUME_INDEX) ? black : white), 
                mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, 
                SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT, 
                menuTextThirdVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == SOUND_EFFECTS_VOLUME_INDEX) ? black : white), 
                mainWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(mainWindowRenderer, 
                SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT, 
                menuTextFourthVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == RETURN_TO_MAIN_MENU_INDEX) ? black : white), 
                mainWindow);

            menuSubtextRenderer.renderText(mainWindowRenderer, 
                (fullscreen ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), 
                (currentHorizontalResolution * 2 / 3), 
                menuTextFirstVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == FULLSCREEN_INDEX) ? black : white), 
                mainWindow);

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
    switch(event.type)
    {
        case SDL_KEYDOWN:
        {
            evaluateKeystrokeEvent(event);
            break;
        }
        case SDL_MOUSEMOTION:
        {
            evaluteMouseMotionEvent();
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            evaluteMouseButtonEvent(event);
            break;
        }
        case SDL_MOUSEWHEEL:
        {
            evaluteMouseWheelEvent(event);
        }
    }
}

void MenuRenderer::evaluateKeystrokeEvent(const SDL_Event event)
{
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            if(event.key.keysym.sym == SDLK_UP)
            {
                currentlySelectedMainMenuOption--;
                if(currentlySelectedMainMenuOption < CONTINUE_INDEX)
                {
                    currentlySelectedMainMenuOption = EXIT_GAME_INDEX;
                }
            }   
            if(event.key.keysym.sym == SDLK_DOWN)
            {
                currentlySelectedMainMenuOption++;
                if(currentlySelectedMainMenuOption > EXIT_GAME_INDEX)
                {
                    currentlySelectedMainMenuOption = CONTINUE_INDEX;
                }
            } 
            if(event.key.keysym.sym == SDLK_RETURN)
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
                        setCurrentMenu(SETTINGS_MENU_INDEX, RETURN_TO_MAIN_MENU_INDEX);
                        break;
                    }
                }
            } 
            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            if(event.key.keysym.sym == SDLK_UP)
            {
                currentlySelectedSettingsMenuOption--;
                if(currentlySelectedSettingsMenuOption < FULLSCREEN_INDEX)
                {
                    currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;
                }
            }   
            if(event.key.keysym.sym == SDLK_DOWN)
            {
                currentlySelectedSettingsMenuOption++;
                if(currentlySelectedSettingsMenuOption > RETURN_TO_MAIN_MENU_INDEX)
                {
                    currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;
                }
            } 
            if(event.key.keysym.sym == SDLK_RETURN)
            {
                switch(currentlySelectedSettingsMenuOption)
                {
                    case FULLSCREEN_INDEX:
                    {
                        setFullScreen(!fullscreen);
                        break;
                    }
                    case RETURN_TO_MAIN_MENU_INDEX:
                    {
                        setCurrentMenu(MAIN_MENU_INDEX, CONTINUE_INDEX);
                        break;
                    }
                }
            } 
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                setCurrentMenu(MAIN_MENU_INDEX, CONTINUE_INDEX);
            }   
            break;
        }
    }
}

void MenuRenderer::evaluteMouseMotionEvent()
{
    SDL_GetMouseState(&currentHorizontalMousePosition, &currentVerticalMousePosition);

    if((menuTextFirstVerticalPosition < currentVerticalMousePosition) && (currentVerticalMousePosition < (menuTextFirstVerticalPosition + HEIGHT_OF_MENU_OPTION_TEXT)))
    {
        if(currentlyDisplayedMenu == MAIN_MENU_INDEX)
        {
            currentlySelectedMainMenuOption = CONTINUE_INDEX;
        }
        else if(currentlyDisplayedMenu == SETTINGS_MENU_INDEX)
        {
            currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;
        }
    }
    else if((menuTextSecondVerticalPosition < currentVerticalMousePosition) && (currentVerticalMousePosition < (menuTextSecondVerticalPosition + HEIGHT_OF_MENU_OPTION_TEXT)))
    {
        if(currentlyDisplayedMenu == MAIN_MENU_INDEX)
        {
            currentlySelectedMainMenuOption = NEW_GAME_INDEX;
        }
        else if(currentlyDisplayedMenu == SETTINGS_MENU_INDEX)
        {
            currentlySelectedSettingsMenuOption = MUSIC_VOLUME_INDEX;
        }    
    }
    else if((menuTextThirdVerticalPosition < currentVerticalMousePosition) && (currentVerticalMousePosition < (menuTextThirdVerticalPosition + HEIGHT_OF_MENU_OPTION_TEXT)))
    {
        if(currentlyDisplayedMenu == MAIN_MENU_INDEX)
        {
            currentlySelectedMainMenuOption = SETTINGS_INDEX;
        }
        else if(currentlyDisplayedMenu == SETTINGS_MENU_INDEX)
        {
            currentlySelectedSettingsMenuOption = SOUND_EFFECTS_VOLUME_INDEX;
        }    
    }
    else if((menuTextFourthVerticalPosition < currentVerticalMousePosition) && (currentVerticalMousePosition < (menuTextFourthVerticalPosition + HEIGHT_OF_MENU_OPTION_TEXT)))
    {
        if(currentlyDisplayedMenu == MAIN_MENU_INDEX)
        {
            currentlySelectedMainMenuOption = EXIT_GAME_INDEX;
        }
        else if(currentlyDisplayedMenu == SETTINGS_MENU_INDEX)
        {
            currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;
        }    
    }
}

void MenuRenderer::evaluteMouseButtonEvent(const SDL_Event event)
{
    printf("\nevaluteMouseButtonEvent: currentlyDisplayedMenu: %u", currentlyDisplayedMenu);
    //TODO: CHANGE MOUSE CLICK HITBOX TO INCLUDE HORIZONTAL BOUNDARIES OF TEXT
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            switch(currentlySelectedMainMenuOption)
            {
                case CONTINUE_INDEX:
                {
                    break;
                }
                case NEW_GAME_INDEX:
                {
                    break;
                }
                case SETTINGS_INDEX:
                {
                    setCurrentMenu(SETTINGS_MENU_INDEX, RETURN_TO_MAIN_MENU_INDEX);
                    break;
                }
                case EXIT_GAME_INDEX:
                {
                    quitGame = true;
                    break;
                }
            }
            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            switch(currentlySelectedSettingsMenuOption)
            {
                case FULLSCREEN_INDEX:
                {
                    setFullScreen(!fullscreen);
                    break;
                }
                case MUSIC_VOLUME_INDEX:
                {
                    break;
                }
                case SOUND_EFFECTS_VOLUME_INDEX:
                {
                    break;
                }
                case RETURN_TO_MAIN_MENU_INDEX:
                {
                    //select exit game as highlighted option as that is where user's mouse will be upon exiting settings menu
                    setCurrentMenu(MAIN_MENU_INDEX, EXIT_GAME_INDEX);
                    break;
                }            
            }
            break;
        }
    }
}

void MenuRenderer::evaluteMouseWheelEvent(const SDL_Event event)
{
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            //scroll up
            if(event.wheel.y < 0)
            {
                currentlySelectedMainMenuOption++;
                if(currentlySelectedMainMenuOption > RETURN_TO_MAIN_MENU_INDEX)
                {
                    currentlySelectedMainMenuOption = FULLSCREEN_INDEX;
                }
                break;
            }
            //scroll down
            else if(event.wheel.y > 0)
            {
                currentlySelectedMainMenuOption--;
                if(currentlySelectedMainMenuOption < FULLSCREEN_INDEX)
                {
                    currentlySelectedMainMenuOption = RETURN_TO_MAIN_MENU_INDEX;
                }
                break;
            }
        }
        case SETTINGS_MENU_INDEX:
        {
            //scroll up
            if(event.wheel.y < 0)
            {
                currentlySelectedSettingsMenuOption++;
                if(currentlySelectedSettingsMenuOption > RETURN_TO_MAIN_MENU_INDEX)
                {
                    currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;
                }
                break;
            }
            //scroll down
            else if(event.wheel.y > 0)
            {
                currentlySelectedSettingsMenuOption--;
                if(currentlySelectedSettingsMenuOption < FULLSCREEN_INDEX)
                {
                    currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;
                }
                break;
            }
        }
    }
}

void MenuRenderer::setFullScreen(const bool newFullscreen)
{
    //grab current resolution so mouse position can be kept proportionally the same
    int previousHorizontalResolution = currentHorizontalResolution;
    int previousVerticalResolution = currentVerticalResolution;

    fullscreen = newFullscreen;
    SDL_SetWindowFullscreen(mainWindow, (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
    SDL_GetWindowSize(mainWindow, &currentHorizontalResolution, &currentVerticalResolution);

    //determine where to place the mouse cursor within the new window so it's in the same spot as it was before proportionally
    int newMouseHorziontalPositionProportionalToPreviousResolution = (currentHorizontalMousePosition * currentHorizontalResolution) / previousHorizontalResolution;
    int newMouseVerticalPositionProportionalToPreviousResolution = (currentVerticalMousePosition * currentVerticalResolution) / previousVerticalResolution;

    SDL_WarpMouseInWindow(mainWindow, newMouseHorziontalPositionProportionalToPreviousResolution, newMouseVerticalPositionProportionalToPreviousResolution);

    //update UI vertical position for new resolution
    updateUIPositions();

    menuOptionsPositionMap = 
    {
        {0, menuTextFirstVerticalPosition},
        {1, menuTextSecondVerticalPosition},
        {2, menuTextThirdVerticalPosition},
        {3, menuTextFourthVerticalPosition}
    };

    //TODO: SAVE SETTINGS BETWEEN POWER CYCLES
}

void MenuRenderer::updateUIPositions()
{
    menuTitleTextVerticalPosition = currentVerticalResolution / 3.0;
    menuTextFirstVerticalPosition = menuTitleTextVerticalPosition + (currentVerticalResolution / 10);
    menuTextSecondVerticalPosition = menuTextFirstVerticalPosition + (currentVerticalResolution / 20);
    menuTextThirdVerticalPosition = menuTextSecondVerticalPosition + (currentVerticalResolution / 20);
    menuTextFourthVerticalPosition = menuTextThirdVerticalPosition + (currentVerticalResolution / 20);

    menuOptionsPositionMap = 
    {
        {0, menuTextFirstVerticalPosition},
        {1, menuTextSecondVerticalPosition},
        {2, menuTextThirdVerticalPosition},
        {3, menuTextFourthVerticalPosition}
    };
}

int MenuRenderer::getCurrentlyDisplayedMenu()
{
    return currentlyDisplayedMenu;
}

void MenuRenderer::setCurrentMenu(const int newMenu, const int selectedMenuOption)
{
    currentlySelectedMainMenuOption = selectedMenuOption;
    currentlyDisplayedMenu = newMenu;
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