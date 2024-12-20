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
}

void SettingsMenuRenderer::renderCurrentScreen(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) 
{
    WindowRenderer::renderFPS(getMenuSubtitleTextFont());
    renderMainMenuLogo();
    renderMenuOptionSelectionSprite();

    menuSubtextRenderer.renderHorizontallyCenteredText(
        SETTINGS_MENU_FULLSCREEN_TEXT, 
        menuTextFirstVerticalPosition, 
        ((getCurrentMenuOption() == FULLSCREEN_INDEX) ? backlitBlack : white), 
        getWindow());

    menuSubtextRenderer.renderHorizontallyCenteredText(
        SETTINGS_MENU_RESOLUTION_TEXT, 
        menuTextSecondVerticalPosition, 
        ((getCurrentMenuOption() == RESOLUTION_INDEX) ? backlitBlack : white), 
        getWindow());

    menuSubtextRenderer.renderHorizontallyCenteredText(
        SETTINGS_MENU_MUSIC_VOLUME_TEXT, 
        menuTextThirdVerticalPosition, 
        ((getCurrentMenuOption() == MUSIC_VOLUME_INDEX) ? backlitBlack : white), 
        getWindow());

    menuSubtextRenderer.renderHorizontallyCenteredText(
        SETTINGS_MENU_SOUND_EFFECTS_VOLUME_TEXT, 
        menuTextFourthVerticalPosition, 
        ((getCurrentMenuOption() == SOUND_EFFECTS_VOLUME_INDEX) ? backlitBlack : white), 
        getWindow());

    menuSubtextRenderer.renderHorizontallyCenteredText(
        SETTINGS_MENU_RETURN_TO_MAIN_MENU_TEXT, 
        menuTextFifthVerticalPosition, 
        ((getCurrentMenuOption() == RETURN_TO_MAIN_MENU_INDEX) ? backlitBlack : white), 
        getWindow());

    // Render fullscreen toggle icon
    menuSubtextRenderer.renderText(
        (settingsManager.getFullscreen() ? SETTING_SELECTED_TEXT : SETTING_NOT_SELECTED_TEXT), 
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuTextFirstVerticalPosition, 
        ((getCurrentMenuOption() == FULLSCREEN_INDEX) ? backlitBlack : white), 
        getWindow());

    // Render resolution selection icon
    menuSubtextRenderer.renderText(
        (settingsManager.getFullscreen() ? usersMonitorResolution : windowedResolutionSelectionMap[settingsManager.getCurrentWindowedResolutionSetting()]), 
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuTextSecondVerticalPosition, 
        ((getCurrentMenuOption() == RESOLUTION_INDEX) ? backlitBlack : white), 
        getWindow());

    // Render music volume selection icon
    menuSubtextRenderer.renderText(
        variableSettingSelectionMap[settingsManager.getCurrentMusicVolumeSetting()], 
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuTextThirdVerticalPosition, 
        ((getCurrentMenuOption() == MUSIC_VOLUME_INDEX) ? backlitBlack : white), 
        getWindow());

    // Render sound effects volume selection icon
    menuSubtextRenderer.renderText(
        variableSettingSelectionMap[settingsManager.getCurrentSoundEffectVolumeSetting()], 
        (getResolutionSettingLeftSideHorizontalPlacement()), 
        menuTextFourthVerticalPosition, 
        ((getCurrentMenuOption() == SOUND_EFFECTS_VOLUME_INDEX) ? backlitBlack : white), 
        getWindow());

    SDL_GL_SwapWindow(getWindow()); // Swap the OpenGL buffers
}


void SettingsMenuRenderer::evaluateKeystrokeEvent(const SDL_Event event)
{
    if(event.key.keysym.sym == SDLK_UP)
    {
        setCurrentMenuOption(getCurrentMenuOption() - 1);
        if(getCurrentMenuOption() < FULLSCREEN_INDEX)
        {
            setCurrentMenuOption(RETURN_TO_MAIN_MENU_INDEX);
        }
    }   
    else if(event.key.keysym.sym == SDLK_DOWN)
    {
        setCurrentMenuOption(getCurrentMenuOption() + 1);
        if(getCurrentMenuOption() > RETURN_TO_MAIN_MENU_INDEX)
        {
            setCurrentMenuOption(FULLSCREEN_INDEX);
        }
    } 
    else if(event.key.keysym.sym == SDLK_LEFT)
    {
        //TODO: ADD MOUSE CONTROLS FOR RESOLUTION AND VOLUME
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
        //TODO: ADD MOUSE CONTROLS FOR RESOLUTION AND VOLUME
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
                setFullscreen(!settingsManager.getFullscreen());
                updateResolution();
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
    else if(event.key.keysym.sym == SDLK_ESCAPE)
    {
        setCurrentMenu(MAIN_MENU_INDEX);
        setCurrentMenuOption(CONTINUE_INDEX);
    }   
}

void SettingsMenuRenderer::evaluateMouseMotionEvent()
{
    SDL_GetMouseState(&currentHorizontalMousePosition, &currentVerticalMousePosition);

    if((menuTextFirstVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFirstVerticalUILowerEdgePosition))
    {
        setCurrentMenuOption(FULLSCREEN_INDEX);
    }
    else if((menuTextSecondVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextSecondVerticalUILowerEdgePosition))
    {
        setCurrentMenuOption(RESOLUTION_INDEX);  
    }
    else if((menuTextThirdVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextThirdVerticalUILowerEdgePosition))
    {
        setCurrentMenuOption(MUSIC_VOLUME_INDEX);  
    }
    else if((menuTextFourthVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFourthVerticalUILowerEdgePosition))
    {
        setCurrentMenuOption(SOUND_EFFECTS_VOLUME_INDEX); 
    }
    else if((menuTextFifthVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFifthVerticalUILowerEdgePosition))
    {
        setCurrentMenuOption(RETURN_TO_MAIN_MENU_INDEX);  
    }
}

void SettingsMenuRenderer::evaluateMouseWheelEvent(const SDL_Event event)
{
    //scroll up
    if(event.wheel.y < 0)
    {
        setCurrentMenuOption(getCurrentMenuOption() + 1);
        if(getCurrentMenuOption() > RETURN_TO_MAIN_MENU_INDEX)
        {
            setCurrentMenuOption(FULLSCREEN_INDEX);
        }
    }
    //scroll down
    else if(event.wheel.y > 0)
    {
        setCurrentMenuOption(getCurrentMenuOption() - 1);
        if(getCurrentMenuOption() < FULLSCREEN_INDEX)
        {
            setCurrentMenuOption(RETURN_TO_MAIN_MENU_INDEX);
        }
    }
}

void SettingsMenuRenderer::evaluateMouseButtonEvent(const SDL_Event event)
{
    SDL_GetMouseState(&currentHorizontalMousePosition, &currentVerticalMousePosition);

    switch(getCurrentMenuOption())
    {
        case FULLSCREEN_INDEX:
        {
            setFullscreen(!settingsManager.getFullscreen());
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