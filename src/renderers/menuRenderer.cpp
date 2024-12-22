#include "menuRenderer.h"

int MenuRenderer::currentlySelectedMenuOption = 0;

int MenuRenderer::menuTextFirstVerticalUIUpperEdgePosition = 0;
int MenuRenderer::menuTextSecondVerticalUIUpperEdgePosition = 0;
int MenuRenderer::menuTextThirdVerticalUIUpperEdgePosition = 0;
int MenuRenderer::menuTextFourthVerticalUIUpperEdgePosition = 0;
int MenuRenderer::menuTextFifthVerticalUIUpperEdgePosition = 0;

int MenuRenderer::menuTextFirstVerticalUILowerEdgePosition = 0;
int MenuRenderer::menuTextSecondVerticalUILowerEdgePosition = 0;
int MenuRenderer::menuTextThirdVerticalUILowerEdgePosition = 0;
int MenuRenderer::menuTextFourthVerticalUILowerEdgePosition = 0;
int MenuRenderer::menuTextFifthVerticalUILowerEdgePosition = 0;

std::array<int, NUMBER_OF_ALLOCATED_MENU_OPTIONS> MenuRenderer::menuOptionsVerticalPositions;

MenuRenderer::MenuRenderer(SDL_Window* win, SDL_Renderer* ren)
    : WindowRenderer(win, ren)
{
    updateUIPositions();
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
    //TODO: MAKE THIS HAPPEN ON RESOLUTION RESIZE AS WELL.
    //grab current resolution so mouse position can be kept proportionally the same
    int previousHorizontalResolution;
    int previousVerticalResolution;

    SDL_GetWindowSize(getWindow(), &previousHorizontalResolution, &previousVerticalResolution);

    settingsManager.setFullscreen(newFullscreen);
    SDL_SetWindowFullscreen(getWindow(), (settingsManager.getFullscreen() ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));  

    int currentHorizontalResolution;
    int currentVerticalResolution;

    SDL_GetWindowSize(getWindow(), &currentHorizontalResolution, &currentVerticalResolution);

    setCurrentHorizontalResolution(currentHorizontalResolution);
    setCurrentVerticalResolution(currentVerticalResolution);

    //determine where to place the mouse cursor within the new window so it's in the same spot as it was before proportionally
    int newMouseHorizontalPositionProportionalToPreviousResolution = (currentHorizontalMousePosition * getCurrentHorizontalResolution()) / previousHorizontalResolution;
    int newMouseVerticalPositionProportionalToPreviousResolution = (currentVerticalMousePosition * getCurrentVerticalResolution()) / previousVerticalResolution;

    SDL_WarpMouseInWindow(getWindow(), newMouseHorizontalPositionProportionalToPreviousResolution, newMouseVerticalPositionProportionalToPreviousResolution);

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

void MenuRenderer::setCurrentMenu(const int newMenu)
{
    currentScreen = newMenu;
}

void MenuRenderer::setCurrentMenuOption(const int selectedMenuOption)
{
    currentlySelectedMenuOption = selectedMenuOption;
}

int MenuRenderer::getCurrentMenuOption()
{
    return currentlySelectedMenuOption;
}

void MenuRenderer::updateUIPositions()
{
    menuTitleLogoVerticalPosition = getCurrentVerticalResolution() / 3.0;

    menuOptionsVerticalPositions[0] = menuTitleLogoVerticalPosition + (MENU_OPTION_INITIAL_OFFSET);

    for(int menuOption = 1; menuOption < NUMBER_OF_SETTINGS_OPTIONS; menuOption++)
    {
        menuOptionsVerticalPositions[menuOption] = (menuOptionsVerticalPositions[menuOption - 1] + MENU_OPTION_SUBSEQUENT_OFFSET);
    }

    // menuTextFirstVerticalUILowerEdgePosition = menuTextFirstVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    // menuTextSecondVerticalUILowerEdgePosition = menuTextSecondVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    // menuTextThirdVerticalUILowerEdgePosition = menuTextThirdVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    // menuTextFourthVerticalUILowerEdgePosition = menuTextFourthVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    // menuTextFifthVerticalUILowerEdgePosition = menuTextFifthVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
}


SDL_Texture* MenuRenderer::getMenuSelectionIconTexture()
{
    return menuSelectionIconTexture;
}

int MenuRenderer::getcurrentScreen()
{
    return currentScreen;
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
    if(!getFullscreen())
    {
        switch(settingsManager.getCurrentWindowedResolutionSetting())
        {
            case(0):
            {
                setCurrentHorizontalResolution(1280);
                setCurrentVerticalResolution(720);
                break;
            }
            case(1):
            {
                setCurrentHorizontalResolution(1600);
                setCurrentVerticalResolution(900);
                break;
            }
            case(2):
            {
                setCurrentHorizontalResolution(1920);
                setCurrentVerticalResolution(1080);
                break;
            }
        }
        SDL_SetWindowSize(getWindow(), getCurrentHorizontalResolution(), getCurrentVerticalResolution());
        SDL_SetWindowPosition(getWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

        updateUIPositions();
    }
}

void MenuRenderer::renderMainMenuLogo()
{
    menuLogoTextureWithRect = textureRenderer.createAndVerifyTexture(
        ((getCurrentHorizontalResolution() / 2) - MAIN_MENU_LOGO_HORIZONTAL_OFFSET), //place in horizontal center of screen
        (menuTitleLogoVerticalPosition - MAIN_MENU_LOGO_VERTICAL_OFFSET),
        MENU_LOGO_IMAGE_PATH,
        getWindow(),
        getRenderer());

    mainMenuLogoTexture = menuLogoTextureWithRect.texture;
    mainMenuLogoRect = menuLogoTextureWithRect.rectangle;

    //set no interpolation scaling mode
    SDL_SetTextureScaleMode(mainMenuLogoTexture, SDL_ScaleModeNearest);

    mainMenuLogoRect.w *= FOUR_TIMES_SCALAR;
    mainMenuLogoRect.h *= FOUR_TIMES_SCALAR;

    SDL_RenderCopy(getRenderer(), mainMenuLogoTexture, NULL, &mainMenuLogoRect);
}

void MenuRenderer::renderMenuOptionSelectionSprite()
{
    int menuSelectionIconVerticalPosition;

    menuSelectionIconVerticalPosition = (menuOptionsVerticalPositions[currentlySelectedMenuOption] - MENU_SELECTION_ICON_VERTICAL_OFFSET);

    menuSelectionIconTextureWithRect = textureRenderer.createAndVerifyTexture(
        0, //place on far left side of screen
        menuSelectionIconVerticalPosition,
        MENU_SELECTION_ICON_IMAGE_PATH, 
        getWindow(), 
        getRenderer());

    menuSelectionIconTexture = menuSelectionIconTextureWithRect.texture;
    menuSelectionIconRect = menuSelectionIconTextureWithRect.rectangle;

    SDL_RenderCopy(getRenderer(), menuSelectionIconTexture, NULL, &menuSelectionIconRect);
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