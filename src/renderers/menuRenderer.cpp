#include "menuRenderer.h"

MenuRenderer::MenuRenderer(SDL_Window* win, SDL_Renderer* ren)
    : WindowRenderer(win, ren)
{
    //set member variables to inherited values from windowRenderer
    titleScreenWindow = getWindow();
    titleScreenWindowRenderer = getRenderer();

    settingsManager.loadSavedSettings();
    updateResolution();
}

void MenuRenderer::renderCurrentlyDisplayedMenu(const int currentlyDisplayedMenu, TextRenderer menuTitleTextRenderer, TextRenderer menuSubtextRenderer)
{
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            renderLogoAndMenuOptionSelectionSprites();

            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreenWindowRenderer, 
                MAIN_MENU_CONTINUE_TEXT, 
                menuTextFirstVerticalPosition, 
                ((currentlySelectedMainMenuOption == CONTINUE_INDEX) ? black : white), 
                titleScreenWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreenWindowRenderer, 
                MAIN_MENU_NEW_GAME_TEXT, 
                menuTextSecondVerticalPosition, 
                ((currentlySelectedMainMenuOption == NEW_GAME_INDEX) ? black : white), 
                titleScreenWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreenWindowRenderer, 
                MAIN_MENU_SETTINGS_TEXT, 
                menuTextThirdVerticalPosition, 
                ((currentlySelectedMainMenuOption == SETTINGS_INDEX) ? black : white), 
                titleScreenWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreenWindowRenderer, 
                MAIN_MENU_EXIT_TEXT, 
                menuTextFourthVerticalPosition, 
                ((currentlySelectedMainMenuOption == EXIT_GAME_INDEX) ? black : white), 
                titleScreenWindow);

            SDL_RenderPresent(titleScreenWindowRenderer);

            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            renderLogoAndMenuOptionSelectionSprites();

            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreenWindowRenderer, 
                SETTINGS_MENU_FULLSCREEN_TEXT, 
                menuTextFirstVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == FULLSCREEN_INDEX) ? black : white), 
                titleScreenWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreenWindowRenderer, 
                SETTINGS_MENU_RESOLUTION_TEXT, 
                menuTextSecondVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == RESOLUTION_INDEX) ? black : white), 
                titleScreenWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreenWindowRenderer, 
                SETTINGS_MENU_MUSIC_VOLUME_TEXT, 
                menuTextThirdVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == MUSIC_VOLUME_INDEX) ? black : white), 
                titleScreenWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreenWindowRenderer, 
                SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT, 
                menuTextFourthVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == SOUND_EFFECTS_VOLUME_INDEX) ? black : white), 
                titleScreenWindow);
            menuSubtextRenderer.renderHorizontallyCenteredText(titleScreenWindowRenderer, 
                SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT, 
                menuTextFifthVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == RETURN_TO_MAIN_MENU_INDEX) ? black : white), 
                titleScreenWindow);

            //render fullscreen toggle icon
            menuSubtextRenderer.renderText(titleScreenWindowRenderer, 
                (settingsManager.getFullscreen() ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), 
                (currentHorizontalResolution * (2.0 / 3.0)), 
                menuTextFirstVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == FULLSCREEN_INDEX) ? black : white), 
                titleScreenWindow);

            //render resolution selection icon
            menuSubtextRenderer.renderText(titleScreenWindowRenderer, 
                (settingsManager.getFullscreen() ? usersMonitorResolution : windowedResolutionSelectionMap[settingsManager.getCurrentWindowedResolutionSetting()]), //TODO: RESOLUTION CHANGE IN FULLSCREEN SUPPORT
                (currentHorizontalResolution * (2.0 / 3.0)), 
                menuTextSecondVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == RESOLUTION_INDEX) ? black : white), 
                titleScreenWindow);

            //render music and sound effects volume selection icons
            menuSubtextRenderer.renderText(titleScreenWindowRenderer, 
                variableSettingSelectionMap[settingsManager.getCurrentMusicVolumeSetting()], 
                (currentHorizontalResolution * (2.0 / 3.0)), 
                menuTextThirdVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == MUSIC_VOLUME_INDEX) ? black : white), 
                titleScreenWindow);

            menuSubtextRenderer.renderText(titleScreenWindowRenderer, 
                variableSettingSelectionMap[settingsManager.getCurrentSoundEffectVolumeSetting()], 
                (currentHorizontalResolution * (2.0 / 3.0)), 
                menuTextFourthVerticalPosition, 
                ((currentlySelectedSettingsMenuOption == SOUND_EFFECTS_VOLUME_INDEX) ? black : white), 
                titleScreenWindow);

            SDL_RenderPresent(titleScreenWindowRenderer);

            break;
        }
    }
}

void MenuRenderer::renderLogoAndMenuOptionSelectionSprites()
{
    //render main logo
    mainMenuLogoTextureWithRect = textureRenderer.createAndVerifyTexture(
        ((currentHorizontalResolution / 2) - MAIN_MENU_LOGO_HORIZONTAL_OFFSET), //place in horizontal center of screen
        (menuTitleLogoVerticalPosition - MAIN_MENU_LOGO_VERTICAL_OFFSET),
        MENU_LOGO_IMAGE_PATH,
        titleScreenWindow,
        titleScreenWindowRenderer);

    mainMenuLogoTexture = mainMenuLogoTextureWithRect.texture;
    mainMenuLogoRect = mainMenuLogoTextureWithRect.rectangle;

    //set no interpolation scaling mode
    SDL_SetTextureScaleMode(mainMenuLogoTexture, SDL_ScaleModeNearest);

    mainMenuLogoRect.w *= FOUR_TIMES_SCALAR;
    mainMenuLogoRect.h *= FOUR_TIMES_SCALAR;

    //render menu option selection sprite
    int menuSelectionIconVerticalPosition;
    switch(currentlyDisplayedMenu)
    {
        case MAIN_MENU_INDEX:
        {
            menuSelectionIconVerticalPosition = (menuOptionsPositionMap[currentlySelectedMainMenuOption] - MENU_SELECTION_ICON_VERTICAL_OFFSET);
            break;
        }
        case SETTINGS_MENU_INDEX:
        {
            menuSelectionIconVerticalPosition = (menuOptionsPositionMap[currentlySelectedSettingsMenuOption] - MENU_SELECTION_ICON_VERTICAL_OFFSET);
            break;
        }
    }

    menuSelectionIconTextureWithRect = textureRenderer.createAndVerifyTexture(
        0, //place on far left side of screen
        menuSelectionIconVerticalPosition,
        MENU_SELECTION_ICON_IMAGE_PATH, 
        titleScreenWindow, 
        titleScreenWindowRenderer);

    menuSelectionIconTexture = menuSelectionIconTextureWithRect.texture;
    mainMenuSelectionRect = menuSelectionIconTextureWithRect.rectangle;

    //render menu option selection rectangle first so text appears on top of it
    SDL_RenderCopy(titleScreenWindowRenderer, menuSelectionIconTexture, NULL, &mainMenuSelectionRect);

    //render menu logo
    SDL_RenderCopy(titleScreenWindowRenderer, mainMenuLogoTexture, NULL, &mainMenuLogoRect);
}

void MenuRenderer::destroyTextures()
{
    // Destroy old textures to prevent memory leaks
    if(mainMenuLogoTexture != nullptr) 
    {
        SDL_DestroyTexture(mainMenuLogoTexture);
        mainMenuLogoTexture = nullptr;  // Prevent dangling pointer
    }
    if(menuSelectionIconTexture != nullptr) 
    {
        SDL_DestroyTexture(menuSelectionIconTexture);
        menuSelectionIconTexture = nullptr;  // Prevent dangling pointer
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
                //TODO: ADD MOUSE CONTROLS FOR RESOLUTION AND VOLUME
                switch(currentlySelectedSettingsMenuOption)
                {
                    case RESOLUTION_INDEX:
                    {
                        int currentWindowedResolutionSetting = settingsManager.getCurrentWindowedResolutionSetting();
                        
                        settingsManager.setCurrentWindowedResolutionSetting(currentWindowedResolutionSetting - 1);
                        
                        if(settingsManager.getCurrentWindowedResolutionSetting() < 0)
                        {
                            settingsManager.setCurrentWindowedResolutionSetting(2);
                        }
                        //TODO: MAKE CHANGES APPLY ON "APPLY" RATHER THAN INSTANTLY
                        updateResolution();
                        break;
                    }
                    case MUSIC_VOLUME_INDEX:
                    {
                        int currentMusicVolumeSetting = settingsManager.getCurrentMusicVolumeSetting();
                        
                        if(settingsManager.getCurrentMusicVolumeSetting() > 0)
                        {
                            settingsManager.setCurrentMusicVolumeSetting(currentMusicVolumeSetting - 1);
                        }
                        break;
                    }
                    case SOUND_EFFECTS_VOLUME_INDEX:
                    {
                        int currentSoundEffectVolumeSetting = settingsManager.getCurrentSoundEffectVolumeSetting();
                        
                        if(settingsManager.getCurrentSoundEffectVolumeSetting() > 0)
                        {
                            settingsManager.setCurrentSoundEffectVolumeSetting(currentSoundEffectVolumeSetting - 1);
                        }                        
                        break;
                    }
                }
            }
            else if(event.key.keysym.sym == SDLK_RIGHT)
            {
                //TODO: ADD MOUSE CONTROLS FOR RESOLUTION AND VOLUME
                switch(currentlySelectedSettingsMenuOption)
                {
                    case RESOLUTION_INDEX:
                    {
                        int currentWindowedResolutionSetting = settingsManager.getCurrentWindowedResolutionSetting();
                        
                        settingsManager.setCurrentWindowedResolutionSetting(currentWindowedResolutionSetting + 1);
                        
                        if(settingsManager.getCurrentWindowedResolutionSetting() > 2)
                        {
                            settingsManager.setCurrentWindowedResolutionSetting(0);
                        }
                        //TODO: MAKE CHANGES APPLY ON "APPLY" RATHER THAN INSTANTLY
                        updateResolution();
                        break;
                    }
                    case MUSIC_VOLUME_INDEX:
                    {
                        int currentMusicVolumeSetting = settingsManager.getCurrentMusicVolumeSetting();
                        
                        if(settingsManager.getCurrentMusicVolumeSetting() < 10)
                        {
                            settingsManager.setCurrentMusicVolumeSetting(currentMusicVolumeSetting + 1);
                        }
                        break;
                    }
                    case SOUND_EFFECTS_VOLUME_INDEX:
                    {
                        int currentSoundEffectVolumeSetting = settingsManager.getCurrentSoundEffectVolumeSetting();
                        
                        if(settingsManager.getCurrentSoundEffectVolumeSetting() < 10)
                        {
                            settingsManager.setCurrentSoundEffectVolumeSetting(currentSoundEffectVolumeSetting + 1);
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
                        setFullscreen(!settingsManager.getFullscreen());
                        break;
                    }
                    case RETURN_TO_MAIN_MENU_INDEX:
                    {
                        settingsManager.saveSettings();
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
    int menuTextFifthVerticalUIUpperEdgePosition = menuTextFifthVerticalPosition - UISelectionMargin;

    int menuTextFirtVerticalUILowerEdgePosition = menuTextFirstVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    int menuTextSecondVerticalUILowerEdgePosition = menuTextSecondVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    int menuTextThirdVerticalUILowerEdgePosition = menuTextThirdVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    int menuTextFourthVerticalUILowerEdgePosition = menuTextFourthVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    int menuTextFifthVerticalUILowerEdgePosition = menuTextFifthVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;

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
            currentlySelectedSettingsMenuOption = RESOLUTION_INDEX;
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
            currentlySelectedSettingsMenuOption = MUSIC_VOLUME_INDEX;
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
            currentlySelectedSettingsMenuOption = SOUND_EFFECTS_VOLUME_INDEX;
        }    
    }
        else if((menuTextFifthVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFifthVerticalUILowerEdgePosition))
    {
        if(currentlyDisplayedMenu == MAIN_MENU_INDEX)
        {
            //no fifth option on main menu
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
                    setFullscreen(!settingsManager.getFullscreen());
                    break;
                }
                case RESOLUTION_INDEX:
                {
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
                    settingsManager.saveSettings(); 
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

bool MenuRenderer::getFullscreen()
{
    return settingsManager.getFullscreen();
}

void MenuRenderer::setFullscreen(const bool newFullscreen)
{
    //grab current resolution so mouse position can be kept proportionally the same
    int previousHorizontalResolution = currentHorizontalResolution;
    int previousVerticalResolution = currentVerticalResolution;

    settingsManager.setFullscreen(newFullscreen);
    SDL_SetWindowFullscreen(titleScreenWindow, (settingsManager.getFullscreen() ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
    
    SDL_GetWindowSize(titleScreenWindow, &currentHorizontalResolution, &currentVerticalResolution);

    //determine where to place the mouse cursor within the new window so it's in the same spot as it was before proportionally
    int newMouseHorziontalPositionProportionalToPreviousResolution = (currentHorizontalMousePosition * currentHorizontalResolution) / previousHorizontalResolution;
    int newMouseVerticalPositionProportionalToPreviousResolution = (currentVerticalMousePosition * currentVerticalResolution) / previousVerticalResolution;

    SDL_WarpMouseInWindow(titleScreenWindow, newMouseHorziontalPositionProportionalToPreviousResolution, newMouseVerticalPositionProportionalToPreviousResolution);

    if(settingsManager.getFullscreen())
    {
        SDL_DisplayMode displayMode;
        int displayIndex = 0; //TODO: Multi-Monitor support

        SDL_GetDesktopDisplayMode(displayIndex, &displayMode);

        usersMonitorResolution = std::to_string(displayMode.w) + " x " + std::to_string(displayMode.h);
    }

    //update UI vertical position for new resolution
    updateUIPositions();
}

void MenuRenderer::updateUIPositions()
{
    menuTitleLogoVerticalPosition = currentVerticalResolution / 3.0;

    menuTextFirstVerticalPosition = menuTitleLogoVerticalPosition + (150);
    menuTextSecondVerticalPosition = menuTextFirstVerticalPosition + (50);
    menuTextThirdVerticalPosition = menuTextSecondVerticalPosition + (50);
    menuTextFourthVerticalPosition = menuTextThirdVerticalPosition + (50);
    menuTextFifthVerticalPosition = menuTextFourthVerticalPosition + (50);

    menuOptionsPositionMap = 
    {
        {0, menuTextFirstVerticalPosition},
        {1, menuTextSecondVerticalPosition},
        {2, menuTextThirdVerticalPosition},
        {3, menuTextFourthVerticalPosition},
        {4, menuTextFifthVerticalPosition}
    };
}

void MenuRenderer::updateResolution()
{
    switch(settingsManager.getCurrentWindowedResolutionSetting())
    {
        case(0):
        {
            currentHorizontalResolution = 1280;
            currentVerticalResolution = 720;
            break;
        }
        case(1):
        {
            currentHorizontalResolution = 1600;
            currentVerticalResolution = 900;
            break;
        }
        case(2):
        {
            currentHorizontalResolution = 1920;
            currentVerticalResolution = 1080;
            break;
        }
    }

    SDL_SetWindowSize(titleScreenWindow, currentHorizontalResolution, currentVerticalResolution);
    SDL_SetWindowPosition(titleScreenWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    updateUIPositions();
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

SDL_Window* MenuRenderer::getTitleScreenWindow()
{
    return WindowRenderer::getWindow();
}

void MenuRenderer::setTitleScreenWindow(SDL_Window* window)
{
    WindowRenderer::setWindow(window);
}

SDL_Renderer* MenuRenderer::getTitleScreenRenderer()
{
    return WindowRenderer::getRenderer();
}

void MenuRenderer::setTitleScreenRenderer(SDL_Renderer* renderer)
{
    WindowRenderer::setRenderer(renderer);
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

//TODO: FILE IS GETTING LONG, LOOK FOR WAYS TO SPLIT UP
//CANDIDATES: 
//            SPLIT MAIN MENU AND SETTINGS MENU TO SEPARATE FILES
//            LOOK FOR REPEATED LOGIC AND REDUCE
//            MOVE COMMON FUNCTIONALITY TO WINDOW RENDERER
//            MOVE MOUSE/KEYBOARD LISTENERS TO SEPARATE FILE