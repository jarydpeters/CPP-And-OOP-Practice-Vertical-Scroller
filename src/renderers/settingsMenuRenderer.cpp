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
    SDL_SetWindowResizable(getWindow(), SDL_bool::SDL_FALSE);

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
    updateResolution();
    updateUIPositions();
}

void SettingsMenuRenderer::renderCurrentScreen(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) 
{
    renderMenuOptionSelectionSprite();

    for(int menuOption = 0; menuOption < NUMBER_OF_SETTINGS_OPTIONS; menuOption++)
    {
        menuSubtextRenderer.renderHorizontallyCenteredText(getRenderer(), 
            settingsMenuOptionsText[menuOption], 
            menuOptionsVerticalPositions[menuOption], 
            ((getCurrentMenuOption() == menuOption) ? black : white), 
            getWindow());
    }

    //render fullscreen toggle icon
    menuSubtextRenderer.renderText(getRenderer(), 
        (settingsManager.getFullscreen() ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), 
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuOptionsVerticalPositions[FULLSCREEN_INDEX], 
        ((getCurrentMenuOption() == FULLSCREEN_INDEX) ? black : white), 
        getWindow());

    //render FPS display toggle icon
    menuSubtextRenderer.renderText(getRenderer(), 
        (settingsManager.getDisplayFPS() ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), 
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuOptionsVerticalPositions[DISPLAY_FPS_INDEX], 
        ((getCurrentMenuOption() == DISPLAY_FPS_INDEX) ? black : white), 
        getWindow());

    //render CRT scanlines toggle icon
    menuSubtextRenderer.renderText(getRenderer(), 
        (settingsManager.getDisplayCRTScanlines() ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), 
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuOptionsVerticalPositions[DISPLAY_CRT_SCANLINES_INDEX], 
        ((getCurrentMenuOption() == DISPLAY_CRT_SCANLINES_INDEX) ? black : white), 
        getWindow());

    //render resolution selection icon
    menuSubtextRenderer.renderText(getRenderer(), 
        (settingsManager.getFullscreen() ? usersMonitorResolution : windowedResolutionSelectionMap[settingsManager.getCurrentWindowedResolutionSetting()]), //TODO: RESOLUTION CHANGE IN FULLSCREEN SUPPORT
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuOptionsVerticalPositions[RESOLUTION_INDEX], 
        ((getCurrentMenuOption() == RESOLUTION_INDEX) ? black : white), 
        getWindow());

    //render music and sound effects volume selection icons
    menuSubtextRenderer.renderText(getRenderer(), 
        variableSettingSelectionMap[settingsManager.getCurrentMusicVolumeSetting()], 
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuOptionsVerticalPositions[MUSIC_VOLUME_INDEX], 
        ((getCurrentMenuOption() == MUSIC_VOLUME_INDEX) ? black : white), 
        getWindow());

    menuSubtextRenderer.renderText(getRenderer(), 
        variableSettingSelectionMap[settingsManager.getCurrentSoundEffectVolumeSetting()], 
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuOptionsVerticalPositions[SOUND_EFFECTS_VOLUME_INDEX], 
        ((getCurrentMenuOption() == SOUND_EFFECTS_VOLUME_INDEX) ? black : white), 
        getWindow());

    if(settingsManager.getDisplayFPS())
    {
        WindowRenderer::renderFPS(getRenderer(), getMenuSubtitleTextFont());
    }
    if(settingsManager.getDisplayCRTScanlines())
    {
        WindowRenderer::renderScanLines(getRenderer());
    }

    SDL_RenderPresent(getRenderer());
}

void SettingsMenuRenderer::evaluateKeystrokeEvent(const SDL_Event event)
{
    if(event.key.keysym.sym == SDLK_UP)
    {
        returnToPreviousMenuOption();
    }   
    else if(event.key.keysym.sym == SDLK_DOWN)
    {
        advanceToNextMenuOption();
    } 
    else if(event.key.keysym.sym == SDLK_LEFT)
    {
        //TODO: ADD MOUSE CONTROLS FOR VOLUME
        //TODO: MOVE MOUSE TO NEW SPOT AFTER RESOLUTION CHANGE (MAKE INTO MENURENDER/WINDOWRENDERER FEATURE?)
        switch(getCurrentMenuOption())
        {
            case RESOLUTION_INDEX:
            {
                int currentWindowedResolutionSetting = settingsManager.getCurrentWindowedResolutionSetting();
                
                settingsManager.setCurrentWindowedResolutionSetting(currentWindowedResolutionSetting - 1);

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
        //TODO: ADD MOUSE CONTROLS FOR FPS, CRT AND VOLUME
        //TODO: MOVE MOUSE TO NEW SPOT AFTER RESOLUTION CHANGE (MAKE INTO MENURENDER/WINDOWRENDERER FEATURE?)
        switch(getCurrentMenuOption())
        {
            case RESOLUTION_INDEX:
            {
                int currentWindowedResolutionSetting = settingsManager.getCurrentWindowedResolutionSetting();
                
                settingsManager.setCurrentWindowedResolutionSetting(currentWindowedResolutionSetting + 1);
                
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
        switch(getCurrentMenuOption())
        {
            case FULLSCREEN_INDEX:
            {
                //TODO: MOVE FUNCTION TO SETTINGS MANAGER AKIN TO FPS AND SCANLINES
                setFullscreen(!settingsManager.getFullscreen());
                updateResolution();
                break;
            }
            case DISPLAY_FPS_INDEX:
            {
                settingsManager.setDisplayFPS(!settingsManager.getDisplayFPS());
                break;
            }
            case DISPLAY_CRT_SCANLINES_INDEX:
            {
                settingsManager.setDisplayCRTScanlines(!settingsManager.getDisplayCRTScanlines());
                break;
            }
            case RETURN_TO_MAIN_MENU_INDEX:
            {
                currentScreen = MAIN_MENU_SCREEN;
                settingsManager.saveSettings();
                setCurrentMenu(MAIN_MENU_INDEX);
                //TODO: FIX BUG WHERE MENU SELECTION OPTION IS CHANGED BEFORE NEW MENU IS RENDERED
                setCurrentMenuOption(CONTINUE_INDEX);
                break;
            }
        }
    } 
    else if(event.key.keysym.sym == SDLK_ESCAPE)
    {
        setCurrentMenu(MAIN_MENU_INDEX);
        setCurrentMenuOption(CONTINUE_INDEX);
    }   
}

void SettingsMenuRenderer::advanceToNextMenuOption()
{
    setCurrentMenuOption(getCurrentMenuOption() + 1);
    if(getCurrentMenuOption() > RETURN_TO_MAIN_MENU_INDEX)
    {
        setCurrentMenuOption(FULLSCREEN_INDEX);
    }
}

void SettingsMenuRenderer::returnToPreviousMenuOption()
{
    setCurrentMenuOption(getCurrentMenuOption() - 1);
    if(getCurrentMenuOption() < FULLSCREEN_INDEX)
    {
        setCurrentMenuOption(RETURN_TO_MAIN_MENU_INDEX);
    }
}

void SettingsMenuRenderer::evaluateMouseMotionEvent()
{
    SDL_GetMouseState(&currentHorizontalMousePosition, &currentVerticalMousePosition);

    if(DEBUG)
    {
        if(false)
        {
            for(int settingsMenuIndex = 0; settingsMenuIndex < NUMBER_OF_SETTINGS_OPTIONS; settingsMenuIndex++)
            {
                std::cout << "Upper " << settingsMenuIndex << ": " << menuTextVerticalUIUpperEdgePositions[settingsMenuIndex] << std::endl;
                std::cout << "Lower " << settingsMenuIndex << ": " << menuTextVerticalUILowerEdgePositions[settingsMenuIndex] << std::endl;
                
                std::cout << "\n" << std::endl;

                std::cout << "Horizontal: " << currentHorizontalMousePosition << std::endl;
                std::cout << "Vertical:   " << currentVerticalMousePosition << std::endl;
            }
        }
    }

    if((menuTextVerticalUIUpperEdgePositions[FULLSCREEN_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUILowerEdgePositions[FULLSCREEN_INDEX]))
    {
        setCurrentMenuOption(FULLSCREEN_INDEX);
    }
    else if((menuTextVerticalUIUpperEdgePositions[DISPLAY_FPS_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUILowerEdgePositions[DISPLAY_FPS_INDEX]))
    {
        setCurrentMenuOption(DISPLAY_FPS_INDEX);  
    }
    else if((menuTextVerticalUIUpperEdgePositions[DISPLAY_CRT_SCANLINES_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUILowerEdgePositions[DISPLAY_CRT_SCANLINES_INDEX]))
    {
        setCurrentMenuOption(DISPLAY_CRT_SCANLINES_INDEX);  
    }
    else if((menuTextVerticalUIUpperEdgePositions[RESOLUTION_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUILowerEdgePositions[RESOLUTION_INDEX]))
    {
        setCurrentMenuOption(RESOLUTION_INDEX);  
    }
    else if((menuTextVerticalUIUpperEdgePositions[MUSIC_VOLUME_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUILowerEdgePositions[MUSIC_VOLUME_INDEX]))
    {
        setCurrentMenuOption(MUSIC_VOLUME_INDEX);  
    }
    else if((menuTextVerticalUIUpperEdgePositions[SOUND_EFFECTS_VOLUME_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUILowerEdgePositions[SOUND_EFFECTS_VOLUME_INDEX]))
    {
        setCurrentMenuOption(SOUND_EFFECTS_VOLUME_INDEX); 
    }
    else if((menuTextVerticalUIUpperEdgePositions[RETURN_TO_MAIN_MENU_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUILowerEdgePositions[RETURN_TO_MAIN_MENU_INDEX]))
    {
        setCurrentMenuOption(RETURN_TO_MAIN_MENU_INDEX);  
    }
}

void SettingsMenuRenderer::evaluateMouseWheelEvent(const SDL_Event event)
{
    //scroll up
    if(event.wheel.y < 0)
    {
        advanceToNextMenuOption();
    }
    //scroll down
    else if(event.wheel.y > 0)
    {
        returnToPreviousMenuOption();
    }
}

void SettingsMenuRenderer::evaluateMouseButtonEvent(const SDL_Event event)
{
    if(DEBUG)
    {
        std::cout << getCurrentMenuOption() << std::endl;
    }

    SDL_GetMouseState(&currentHorizontalMousePosition, &currentVerticalMousePosition);

    switch(getCurrentMenuOption())
    {
        case FULLSCREEN_INDEX:
        {
            setFullscreen(!settingsManager.getFullscreen());
            break;
        }
        case DISPLAY_FPS_INDEX:
        {
            settingsManager.setDisplayFPS(!settingsManager.getDisplayFPS());
            break;
        }
        case DISPLAY_CRT_SCANLINES_INDEX:
        {
            settingsManager.setDisplayCRTScanlines(!settingsManager.getDisplayCRTScanlines());
            break;
        }
        case RESOLUTION_INDEX:
        {
            if(currentHorizontalMousePosition < (getResolutionSettingLeftSideHorizontalPlacement() + (WIDTH_OF_RESOLUTION_OPTION_TEXT / 2)))
            {
                settingsManager.setCurrentWindowedResolutionSetting(settingsManager.getCurrentWindowedResolutionSetting() - 1);
            }
            else if(currentHorizontalMousePosition > (getResolutionSettingLeftSideHorizontalPlacement() + (WIDTH_OF_RESOLUTION_OPTION_TEXT / 2)))
            {
                settingsManager.setCurrentWindowedResolutionSetting(settingsManager.getCurrentWindowedResolutionSetting() + 1);
            }
            updateResolution();
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
            setCurrentMenu(MAIN_MENU_INDEX);
            setCurrentMenuOption(CONTINUE_INDEX);
            break;
        }
    }
}

int SettingsMenuRenderer::getResolutionSettingLeftSideHorizontalPlacement()
{
    return((getCurrentHorizontalResolution() / 2) + 200);
}

void SettingsMenuRenderer::updateUIPositions()
{
    menuOptionsVerticalPositions[0] = (MENU_OPTION_INITIAL_OFFSET);

    for(int menuOption = FULLSCREEN_INDEX; menuOption < NUMBER_OF_SETTINGS_OPTIONS; menuOption++)
    {
        if(menuOption == FULLSCREEN_INDEX)
        {
            menuOptionsVerticalPositions[menuOption] = 100;
        }
        else
        {
            menuOptionsVerticalPositions[menuOption] = (menuOptionsVerticalPositions[menuOption - 1] + MENU_OPTION_SUBSEQUENT_OFFSET);
        }
        menuTextVerticalUIUpperEdgePositions[menuOption] = menuOptionsVerticalPositions[menuOption];
        menuTextVerticalUILowerEdgePositions[menuOption] = menuOptionsVerticalPositions[menuOption] + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    }
}