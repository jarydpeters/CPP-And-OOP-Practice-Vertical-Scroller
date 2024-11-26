#include "settingsMenuRenderer.h"

SettingsMenuRenderer::SettingsMenuRenderer(SDL_Window* win, SDL_Renderer* ren)
    : MenuRenderer(win, ren)
{
    //set member variables to inherited values from windowRenderer
    titleScreenWindow = getWindow();
    titleScreenWindowRenderer = getRenderer();

    settingsManager.loadSavedSettings();
    //updateResolution();
}

void SettingsMenuRenderer::renderCurrentlyDisplayedMenu(const int currentlyDisplayedMenu, TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) 
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
}