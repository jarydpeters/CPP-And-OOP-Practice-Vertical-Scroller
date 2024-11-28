#include "settingsMenuRenderer.h"

SettingsMenuRenderer::SettingsMenuRenderer(SdlUtility sdlUtility,
            SDL_Window* win, 
            SDL_Renderer* ren,
            std::string titleFontPath,
            std::string subtitleFontPath,
            int titleTextPointSize,
            int subtitleTextPointSize)
    : MenuRenderer(win, ren)
{
    //set member variables to inherited values from windowRenderer
    menuScreenWindow = getWindow();
    menuScreenWindowRenderer = getRenderer();
    
    SDL_SetWindowResizable(menuScreenWindow, SDL_bool::SDL_FALSE);

    TTF_Font* titleFont = sdlUtility.createAndVerifyTTFFont(FONT_PATH, 
        TITLE_TEXT_POINT_SIZE, 
        getWindow(), 
        getRenderer());

    TTF_Font* subtitleFont = sdlUtility.createAndVerifyTTFFont(FONT_PATH, 
        SUBTITLE_TEXT_POINT_SIZE, 
        getWindow(), 
        getRenderer());

    setMenuTitleTextFont(titleFont);
    setMenuSubtitleTextFont(subtitleFont);

    settingsManager.loadSavedSettings();
    setFullscreen(getFullscreen());
    std::cout << "SETTINGS MENU" << std::endl;
    updateResolution();
}

void SettingsMenuRenderer::renderCurrentScreen(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) 
{
    RenderMainMenuLogo();
    RenderMenuOptionSelectionSprite();

    menuSubtextRenderer.renderHorizontallyCenteredText(menuScreenWindowRenderer, 
        SETTINGS_MENU_FULLSCREEN_TEXT, 
        menuTextFirstVerticalPosition, 
        ((currentlySelectedSettingsMenuOption == FULLSCREEN_INDEX) ? black : white), 
        menuScreenWindow);
    menuSubtextRenderer.renderHorizontallyCenteredText(menuScreenWindowRenderer, 
        SETTINGS_MENU_RESOLUTION_TEXT, 
        menuTextSecondVerticalPosition, 
        ((currentlySelectedSettingsMenuOption == RESOLUTION_INDEX) ? black : white), 
        menuScreenWindow);
    menuSubtextRenderer.renderHorizontallyCenteredText(menuScreenWindowRenderer, 
        SETTINGS_MENU_MUSIC_VOLUME_TEXT, 
        menuTextThirdVerticalPosition, 
        ((currentlySelectedSettingsMenuOption == MUSIC_VOLUME_INDEX) ? black : white), 
        menuScreenWindow);
    menuSubtextRenderer.renderHorizontallyCenteredText(menuScreenWindowRenderer, 
        SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT, 
        menuTextFourthVerticalPosition, 
        ((currentlySelectedSettingsMenuOption == SOUND_EFFECTS_VOLUME_INDEX) ? black : white), 
        menuScreenWindow);
    menuSubtextRenderer.renderHorizontallyCenteredText(menuScreenWindowRenderer, 
        SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT, 
        menuTextFifthVerticalPosition, 
        ((currentlySelectedSettingsMenuOption == RETURN_TO_MAIN_MENU_INDEX) ? black : white), 
        menuScreenWindow);

    //render fullscreen toggle icon
    menuSubtextRenderer.renderText(menuScreenWindowRenderer, 
        (settingsManager.getFullscreen() ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), 
        ((currentHorizontalResolution / 2) + 200), 
        menuTextFirstVerticalPosition, 
        ((currentlySelectedSettingsMenuOption == FULLSCREEN_INDEX) ? black : white), 
        menuScreenWindow);

    //render resolution selection icon
    menuSubtextRenderer.renderText(menuScreenWindowRenderer, 
        (settingsManager.getFullscreen() ? usersMonitorResolution : windowedResolutionSelectionMap[settingsManager.getCurrentWindowedResolutionSetting()]), //TODO: RESOLUTION CHANGE IN FULLSCREEN SUPPORT
        ((currentHorizontalResolution / 2) + 200), 
        menuTextSecondVerticalPosition, 
        ((currentlySelectedSettingsMenuOption == RESOLUTION_INDEX) ? black : white), 
        menuScreenWindow);

    //render music and sound effects volume selection icons
    menuSubtextRenderer.renderText(menuScreenWindowRenderer, 
        variableSettingSelectionMap[settingsManager.getCurrentMusicVolumeSetting()], 
        ((currentHorizontalResolution / 2) + 200), 
        menuTextThirdVerticalPosition, 
        ((currentlySelectedSettingsMenuOption == MUSIC_VOLUME_INDEX) ? black : white), 
        menuScreenWindow);

    menuSubtextRenderer.renderText(menuScreenWindowRenderer, 
        variableSettingSelectionMap[settingsManager.getCurrentSoundEffectVolumeSetting()], 
        ((currentHorizontalResolution / 2) + 200), 
        menuTextFourthVerticalPosition, 
        ((currentlySelectedSettingsMenuOption == SOUND_EFFECTS_VOLUME_INDEX) ? black : white), 
        menuScreenWindow);

    SDL_RenderPresent(menuScreenWindowRenderer);
}

void SettingsMenuRenderer::evaluateKeystrokeEvent(const SDL_Event event)
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
        //TODO: MOVE MOUSE TO NEW SPOT AFTER RESOLUTION CHANGE (MAKE INTO MENURENDER/WINDOWRENDERER FEATURE?)
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
        //TODO: MOVE MOUSE TO NEW SPOT AFTER RESOLUTION CHANGE (MAKE INTO MENURENDER/WINDOWRENDERER FEATURE?)
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
                updateResolution();
                break;
            }
            case RETURN_TO_MAIN_MENU_INDEX:
            {
                currentScreen = MAIN_MENU_SCREEN;
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
}

void SettingsMenuRenderer::evaluateMouseMotionEvent()
{
    //TODO: CHANGE MOUSE CLICK HITBOX FOR BETTER UX
    SDL_GetMouseState(&currentHorizontalMousePosition, &currentVerticalMousePosition);

    if((menuTextFirstVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFirstVerticalUILowerEdgePosition))
    {
        currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;
    }
    else if((menuTextSecondVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextSecondVerticalUILowerEdgePosition))
    {
        currentlySelectedSettingsMenuOption = RESOLUTION_INDEX;  
    }
    else if((menuTextThirdVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextThirdVerticalUILowerEdgePosition))
    {
        currentlySelectedSettingsMenuOption = MUSIC_VOLUME_INDEX;  
    }
    else if((menuTextFourthVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFourthVerticalUILowerEdgePosition))
    {
        currentlySelectedSettingsMenuOption = SOUND_EFFECTS_VOLUME_INDEX; 
    }
    else if((menuTextFifthVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFifthVerticalUILowerEdgePosition))
    {
        currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;  
    }
}

void SettingsMenuRenderer::evaluateMouseWheelEvent(const SDL_Event event)
{
    //scroll up
    if(event.wheel.y < 0)
    {
        currentlySelectedSettingsMenuOption++;
        if(currentlySelectedSettingsMenuOption > RETURN_TO_MAIN_MENU_INDEX)
        {
            currentlySelectedSettingsMenuOption = FULLSCREEN_INDEX;
        }
    }
    //scroll down
    else if(event.wheel.y > 0)
    {
        currentlySelectedSettingsMenuOption--;
        if(currentlySelectedSettingsMenuOption < FULLSCREEN_INDEX)
        {
            currentlySelectedSettingsMenuOption = RETURN_TO_MAIN_MENU_INDEX;
        }
    }
}

void SettingsMenuRenderer::evaluateMouseButtonEvent(const SDL_Event event)
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
            currentScreen = MAIN_MENU_SCREEN;
            settingsManager.saveSettings(); 
            //select exit game as highlighted option as that is where user's mouse will be upon exiting settings menu
            setCurrentMenu(MAIN_MENU_INDEX, EXIT_GAME_INDEX);
            break;
        }
    }
}