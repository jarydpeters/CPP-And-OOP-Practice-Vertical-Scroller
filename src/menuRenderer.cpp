#include "menuRenderer.h"

MenuRenderer::MenuRenderer()
{
    loadSavedSettings();
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
                titleScreensWindow, 
                titleScreensWindowRenderer);

            menuSelectionIconTexture = menuSelectionIconTextureWithRect.texture;
            mainMenuSelectionRect = menuSelectionIconTextureWithRect.rectangle;

            //render menu option selection rectangle first so text appears on top of it
            SDL_RenderCopy(titleScreensWindowRenderer, menuSelectionIconTexture, NULL, &mainMenuSelectionRect);

            menuTitleTextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, MAIN_MENU_TITLE_TEXT, menuTitleTextVerticalPosition, white, titleScreensWindow);

            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, 
                MAIN_MENU_CONTINUE_TEXT, 
                menuTextFirstVerticalPosition, 
                ((currentlySelectedMainMenuOption == CONTINUE_INDEX) ? black : white), 
                titleScreensWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, 
                MAIN_MENU_NEW_GAME_TEXT, 
                menuTextSecondVerticalPosition, 
                ((currentlySelectedMainMenuOption == NEW_GAME_INDEX) ? black : white), 
                titleScreensWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, 
                MAIN_MENU_SETTINGS_TEXT, 
                menuTextThirdVerticalPosition, 
                ((currentlySelectedMainMenuOption == SETTINGS_INDEX) ? black : white), 
                titleScreensWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, 
                MAIN_MENU_EXIT_TEXT, 
                menuTextFourthVerticalPosition, 
                ((currentlySelectedMainMenuOption == EXIT_GAME_INDEX) ? black : white), 
                titleScreensWindow);

            SDL_RenderPresent(titleScreensWindowRenderer);

            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            menuSelectionIconTextureWithRect = textureRenderer.createAndVerifyTexture(
                0, //place on far left side of screen
                (menuOptionsPositionMap[currentlySelectedSettingsMenuOption] - 6), //offset up to account for texture height
                MENU_SELECTION_ICON_IMAGE_PATH, 
                titleScreensWindow, 
                titleScreensWindowRenderer);

            SDL_Texture* settingsMenuSelectionTexture = menuSelectionIconTextureWithRect.texture;
            SDL_Rect settingsMenuSelectionRect = menuSelectionIconTextureWithRect.rectangle;

            //render menu option selection rectangle first so text appears on top of it
            SDL_RenderCopy(titleScreensWindowRenderer, settingsMenuSelectionTexture, NULL, &settingsMenuSelectionRect);

            menuTitleTextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, SETTINGS_MENU_TITLE_TEXT, menuTitleTextVerticalPosition, white, titleScreensWindow);

            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, 
                SETTINGS_MENU_FULLSCREEN_TEXT, 
                menuTextFirstVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == FULLSCREEN_INDEX) ? black : white), 
                titleScreensWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, 
                SETTINGS_MENU_MUSIC_VOLUME_TEXT, 
                menuTextSecondVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == MUSIC_VOLUME_INDEX) ? black : white), 
                titleScreensWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, 
                SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT, 
                menuTextThirdVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == SOUND_EFFECTS_VOLUME_INDEX) ? black : white), 
                titleScreensWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreensWindowRenderer, 
                SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT, 
                menuTextFourthVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == RETURN_TO_MAIN_MENU_INDEX) ? black : white), 
                titleScreensWindow);

            //render fullscreen toggle icon
            menuSubtextRenderer.renderText(titleScreensWindowRenderer, 
                (fullscreen ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), 
                (currentHorizontalResolution * (2.0 / 3.0 )), 
                menuTextFirstVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == FULLSCREEN_INDEX) ? black : white), 
                titleScreensWindow);

            //render music and sound effects volume selection icons
            menuSubtextRenderer.renderText(titleScreensWindowRenderer, 
                variableSettingSelectionMap[currentMusicVolumeSetting], 
                (currentHorizontalResolution * (2.0 / 3.0 )), 
                menuTextSecondVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == MUSIC_VOLUME_INDEX) ? black : white), 
                titleScreensWindow);

            menuSubtextRenderer.renderText(titleScreensWindowRenderer, 
                variableSettingSelectionMap[currentSoundEffectVolumeSetting], 
                (currentHorizontalResolution * (2.0 / 3.0 )), 
                menuTextThirdVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == SOUND_EFFECTS_VOLUME_INDEX) ? black : white), 
                titleScreensWindow);

            SDL_RenderPresent(titleScreensWindowRenderer);

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

//TODO: separate settings to a SettingsManager class
void MenuRenderer::saveSettings()
{
    std::ofstream outFile(settingsFilePath);
    if(outFile.is_open())
    {
        outFile << "fullscreen: " << fullscreen << std::endl;
        outFile << "music volume: " << currentMusicVolumeSetting << std::endl;
        outFile << "sound effects volume: " << currentSoundEffectVolumeSetting << std::endl;
        
        outFile.close();
    }
    else
    {
        printf("Unable to open file!");
    }
}

//TODO: separate settings to a SettingsManager class
void MenuRenderer::loadSavedSettings()
{
    std::ifstream inFile(settingsFilePath);
    if(inFile.is_open())
    {
        std::string line;

        // Read the file line by line
        while (std::getline(inFile, line))
        {
            std::stringstream stringStream(line);
            std::string settingName;
            std::string settingValue;

            // Get the setting name (before the colon)
            if (std::getline(stringStream, settingName, ':'))
            {
                // Trim leading/trailing spaces from the setting name and value
                settingName.erase(0, settingName.find_first_not_of(" \t"));
                settingName.erase(settingName.find_last_not_of(" \t") + 1);

                // Get the setting value (after the colon)
                if (std::getline(stringStream, settingValue))
                {
                    // trim leading space
                    settingValue.erase(0, settingValue.find_first_not_of(" \t"));

                    // Compare the setting name and assign the value
                    if (settingName == "fullscreen")
                    {
                        fullscreen = std::stoi(settingValue);  // Convert string to integer
                    }
                    else if(settingName == "music volume")
                    {
                        currentMusicVolumeSetting = std::stoi(settingValue);
                    }
                    else if(settingName == "sound effects volume")
                    {
                        currentSoundEffectVolumeSetting = std::stoi(settingValue);
                    }
                    else
                    {
                        std::cout << "Unknown setting: " << settingName << std::endl;
                    }
                }
            }
        }
        inFile.close();
    }
    else
    {
        printf("Unable to open file!");
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
            else if(event.key.keysym.sym == SDLK_DOWN)
            {
                currentlySelectedMainMenuOption++;
                if(currentlySelectedMainMenuOption > EXIT_GAME_INDEX)
                {
                    currentlySelectedMainMenuOption = CONTINUE_INDEX;
                }
            } 
            else if(event.key.keysym.sym == SDLK_RETURN)
            {
                switch(currentlySelectedMainMenuOption)
                {
                    case CONTINUE_INDEX:
                    {
                        currentScreen = MAIN_GAME_SCREEN;
                        break;
                    }
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
            else if(event.key.keysym.sym == SDLK_DOWN)
            {
                currentlySelectedSettingsMenuOption++;
                if(currentlySelectedSettingsMenuOption > RETURN_TO_MAIN_MENU_INDEX)
                {
                    currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;
                }
            } 
            else if(event.key.keysym.sym == SDLK_LEFT)
            {
                //TODO: ADD MOUSE CONTROLS FOR MUSIC VOLUME
                switch(currentlySelectedSettingsMenuOption)
                {
                    case MUSIC_VOLUME_INDEX:
                    {
                        if(currentMusicVolumeSetting > 0)
                        {
                            currentMusicVolumeSetting--;
                        }
                        break;
                    }
                    case SOUND_EFFECTS_VOLUME_INDEX:
                    {
                        if(currentSoundEffectVolumeSetting > 0)
                        {
                            currentSoundEffectVolumeSetting--;
                        }                        
                        break;
                    }
                }
            }
            else if(event.key.keysym.sym == SDLK_RIGHT)
            {
                //TODO: ADD MOUSE CONTROLS FOR SOUND EFFECTS VOLUME
                switch(currentlySelectedSettingsMenuOption)
                {
                    case MUSIC_VOLUME_INDEX:
                    {
                        if(currentMusicVolumeSetting < 10)
                        {
                            currentMusicVolumeSetting++;
                        }
                        break;
                    }
                    case SOUND_EFFECTS_VOLUME_INDEX:
                    {
                        if(currentSoundEffectVolumeSetting < 10)
                        {
                            currentSoundEffectVolumeSetting++;
                        }                        
                        break;
                    }
                }
            }
            else if(event.key.keysym.sym == SDLK_RETURN)
            {
                switch(currentlySelectedSettingsMenuOption)
                {
                    case FULLSCREEN_INDEX:
                    {
                        setFullscreen(!fullscreen);
                        break;
                    }
                    case RETURN_TO_MAIN_MENU_INDEX:
                    {
                        saveSettings();
                        setCurrentMenu(MAIN_MENU_INDEX, CONTINUE_INDEX);
                        break;
                    }
                }
            } 
            else if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                setCurrentMenu(MAIN_MENU_INDEX, CONTINUE_INDEX);
            }   
            break;
        }
    }
}

void MenuRenderer::evaluteMouseMotionEvent()
{
    //TODO: CHANGE MOUSE CLICK HITBOX FOR BETTER UX
    SDL_GetMouseState(&currentHorizontalMousePosition, &currentVerticalMousePosition);

    int UISelectionMargin = 4;

    //fine tune hitbox of menu options
    int menuTextFirtVerticalUIUpperEdgePosition = menuTextFirstVerticalPosition - UISelectionMargin;
    int menuTextSecondVerticalUIUpperEdgePosition = menuTextSecondVerticalPosition - UISelectionMargin;
    int menuTextThirdVerticalUIUpperEdgePosition = menuTextThirdVerticalPosition - UISelectionMargin;
    int menuTextFourthVerticalUIUpperEdgePosition = menuTextFourthVerticalPosition - UISelectionMargin;

    int menuTextFirtVerticalUILowerEdgePosition = menuTextFirstVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    int menuTextSecondVerticalUILowerEdgePosition = menuTextSecondVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    int menuTextThirdVerticalUILowerEdgePosition = menuTextThirdVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    int menuTextFourthVerticalUILowerEdgePosition = menuTextFourthVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;

    if((menuTextFirtVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFirtVerticalUILowerEdgePosition))
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
    else if((menuTextSecondVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextSecondVerticalUILowerEdgePosition))
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
    else if((menuTextThirdVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextThirdVerticalUILowerEdgePosition))
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
    else if((menuTextFourthVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFourthVerticalUILowerEdgePosition))
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
                    //select sound effects volume as highlighted option as that is where user's mouse will be upon entering settings menu
                    setCurrentMenu(SETTINGS_MENU_INDEX, SOUND_EFFECTS_VOLUME_INDEX);
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
                    setFullscreen(!fullscreen);
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
                    saveSettings(); 
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

void MenuRenderer::setFullscreen(const bool newFullscreen)
{
    //grab current resolution so mouse position can be kept proportionally the same
    int previousHorizontalResolution = currentHorizontalResolution;
    int previousVerticalResolution = currentVerticalResolution;

    fullscreen = newFullscreen;
    SDL_SetWindowFullscreen(titleScreensWindow, (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
    SDL_GetWindowSize(titleScreensWindow, &currentHorizontalResolution, &currentVerticalResolution);

    //determine where to place the mouse cursor within the new window so it's in the same spot as it was before proportionally
    int newMouseHorziontalPositionProportionalToPreviousResolution = (currentHorizontalMousePosition * currentHorizontalResolution) / previousHorizontalResolution;
    int newMouseVerticalPositionProportionalToPreviousResolution = (currentVerticalMousePosition * currentVerticalResolution) / previousVerticalResolution;

    SDL_WarpMouseInWindow(titleScreensWindow, newMouseHorziontalPositionProportionalToPreviousResolution, newMouseVerticalPositionProportionalToPreviousResolution);

    //update UI vertical position for new resolution
    updateUIPositions();

    menuOptionsPositionMap = 
    {
        {0, menuTextFirstVerticalPosition},
        {1, menuTextSecondVerticalPosition},
        {2, menuTextThirdVerticalPosition},
        {3, menuTextFourthVerticalPosition}
    };
}

bool MenuRenderer::getFullscreen()
{
    return fullscreen;
}

void MenuRenderer::updateUIPositions()
{
    menuTitleTextVerticalPosition = currentVerticalResolution / 3.0;
    menuTextFirstVerticalPosition = menuTitleTextVerticalPosition + (currentVerticalResolution / 8);
    menuTextSecondVerticalPosition = menuTextFirstVerticalPosition + (currentVerticalResolution / 16);
    menuTextThirdVerticalPosition = menuTextSecondVerticalPosition + (currentVerticalResolution / 16);
    menuTextFourthVerticalPosition = menuTextThirdVerticalPosition + (currentVerticalResolution / 16);

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
    if(newMenu == MAIN_MENU_INDEX)
    {
        currentlySelectedMainMenuOption = selectedMenuOption;
    }
    else if(newMenu == SETTINGS_MENU_INDEX)
    {
        currentlySelectedSettingsMenuOption = selectedMenuOption;
    }
    currentlyDisplayedMenu = newMenu;
}

SDL_Window* MenuRenderer::getTitleScreensWindow()
{
    return titleScreensWindow;
}

void MenuRenderer::setTitleScreensWindow(SDL_Window* window)
{
    titleScreensWindow = window;
}

SDL_Renderer* MenuRenderer::getTitleScreensRenderer()
{
    return titleScreensWindowRenderer;
}

void MenuRenderer::setTitleScreensRenderer(SDL_Renderer* renderer)
{
    titleScreensWindowRenderer = renderer;
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