#include "menuRenderer.h"

MenuRenderer::MenuRenderer(SDL_Window* win, SDL_Renderer* ren)
    : WindowRenderer(win, ren)
{

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
            evaluateMouseMotionEvent();
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            evaluateMouseButtonEvent(event);
            break;
        }
        case SDL_MOUSEWHEEL:
        {
            evaluateMouseWheelEvent(event);
        }
    }
}

bool MenuRenderer::getFullscreen()
{
    return settingsManager.getFullscreen();
}

//overloads setFullscreen from settingsManager.cpp
void MenuRenderer::setFullscreen(const bool newFullscreen)
{
    //grab current resolution so mouse position can be kept proportionally the same
    int previousHorizontalResolution = currentHorizontalResolution;
    int previousVerticalResolution = currentVerticalResolution;

    settingsManager.setFullscreen(newFullscreen);
    SDL_SetWindowFullscreen(menuScreenWindow, (settingsManager.getFullscreen() ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
    
    SDL_GetWindowSize(menuScreenWindow, &currentHorizontalResolution, &currentVerticalResolution);

    //determine where to place the mouse cursor within the new window so it's in the same spot as it was before proportionally
    int newMouseHorziontalPositionProportionalToPreviousResolution = (currentHorizontalMousePosition * currentHorizontalResolution) / previousHorizontalResolution;
    int newMouseVerticalPositionProportionalToPreviousResolution = (currentVerticalMousePosition * currentVerticalResolution) / previousVerticalResolution;

    SDL_WarpMouseInWindow(menuScreenWindow, newMouseHorziontalPositionProportionalToPreviousResolution, newMouseVerticalPositionProportionalToPreviousResolution);

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

void MenuRenderer::renderLogoAndMenuOptionSelectionSprites()
{
    //render main logo
    mainMenuLogoTextureWithRect = textureRenderer.createAndVerifyTexture(
        ((currentHorizontalResolution / 2) - MAIN_MENU_LOGO_HORIZONTAL_OFFSET), //place in horizontal center of screen
        (menuTitleLogoVerticalPosition - MAIN_MENU_LOGO_VERTICAL_OFFSET),
        MENU_LOGO_IMAGE_PATH,
        menuScreenWindow,
        menuScreenWindowRenderer);

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
        menuScreenWindow, 
        menuScreenWindowRenderer);

    menuSelectionIconTexture = menuSelectionIconTextureWithRect.texture;
    mainMenuSelectionRect = menuSelectionIconTextureWithRect.rectangle;

    //render menu option selection rectangle first so text appears on top of it
    SDL_RenderCopy(menuScreenWindowRenderer, menuSelectionIconTexture, NULL, &mainMenuSelectionRect);

    //render menu logo
    SDL_RenderCopy(menuScreenWindowRenderer, mainMenuLogoTexture, NULL, &mainMenuLogoRect);
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

SDL_Texture* MenuRenderer::getMenuSelectionIconTexture()
{
    return menuSelectionIconTexture;
}

int MenuRenderer::getCurrentlyDisplayedMenu()
{
    return currentlyDisplayedMenu;
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

    SDL_SetWindowSize(menuScreenWindow, currentHorizontalResolution, currentVerticalResolution);
    SDL_SetWindowPosition(menuScreenWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    updateUIPositions();
}