#include "mainMenuRenderer.h"

MainMenuRenderer::MainMenuRenderer(SdlUtility sdlUtility,
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

void MainMenuRenderer::renderCurrentScreen(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) 
{
    renderMainMenuLogo();
    renderMenuOptionSelectionSprite();

    for(int menuOption = 0; menuOption < NUMBER_OF_MAIN_MENU_OPTIONS; menuOption++)
    {
        menuSubtextRenderer.renderHorizontallyCenteredText(getRenderer(), 
            mainMenuOptionsText[menuOption], 
            menuOptionsVerticalPositions[menuOption], 
            ((getCurrentMenuOption() == menuOption) ? black : white), 
            getWindow());
    }

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

void MainMenuRenderer::evaluateKeystrokeEvent(const SDL_Event event)
{
    if(event.key.keysym.sym == SDLK_UP)
    {
        returnToPreviousMenuOption();
    }   
    else if(event.key.keysym.sym == SDLK_DOWN)
    {
        advanceToNextMenuOption();
    } 
    else if(event.key.keysym.sym == SDLK_RETURN)
    {
        switch(getCurrentMenuOption())
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
                currentScreen = SETTINGS_MENU_SCREEN;
                setCurrentMenu(SETTINGS_MENU_INDEX);
                setCurrentMenuOption(RETURN_TO_MAIN_MENU_INDEX);
                break;
            }
        }
    } 
}

void MainMenuRenderer::evaluateMouseMotionEvent()
{
    //TODO: CHANGE MOUSE CLICK HITBOX FOR BETTER UX
    SDL_GetMouseState(&currentHorizontalMousePosition, &currentVerticalMousePosition);
    
    if((menuTextVerticalUIUpperEdgePositions[CONTINUE_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUIULowerEdgePositions[CONTINUE_INDEX]))
    {
        setCurrentMenuOption(CONTINUE_INDEX);
    }
    else if((menuTextVerticalUIUpperEdgePositions[NEW_GAME_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUIULowerEdgePositions[NEW_GAME_INDEX]))
    {
        setCurrentMenuOption(NEW_GAME_INDEX);
    }
    else if((menuTextVerticalUIUpperEdgePositions[SETTINGS_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUIULowerEdgePositions[SETTINGS_INDEX]))
    {
        setCurrentMenuOption(SETTINGS_INDEX);
    }
    else if((menuTextVerticalUIUpperEdgePositions[EXIT_GAME_INDEX] < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextVerticalUIULowerEdgePositions[EXIT_GAME_INDEX]))
    {
        setCurrentMenuOption(EXIT_GAME_INDEX);
    }
}


void MainMenuRenderer::evaluateMouseWheelEvent(const SDL_Event event)
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

void MainMenuRenderer::evaluateMouseButtonEvent(const SDL_Event event)
{
    switch(getCurrentMenuOption())
    {
        case CONTINUE_INDEX:
        {
            currentScreen = MAIN_GAME_SCREEN;
            break;
        }
        case NEW_GAME_INDEX:
        {
            break;
        }
        case SETTINGS_INDEX:
        {
            currentScreen = SETTINGS_MENU_SCREEN;
            setCurrentMenu(SETTINGS_MENU_INDEX);
            //select sound effects volume as highlighted option as that is where user's mouse will be upon entering settings menu
            setCurrentMenuOption(MUSIC_VOLUME_INDEX);
            break;
        }
        case EXIT_GAME_INDEX:
        {
            quitGame = true;
            break;
        }
    }
}

void MainMenuRenderer::advanceToNextMenuOption()
{
    setCurrentMenuOption(getCurrentMenuOption() + 1);
    if(getCurrentMenuOption() > EXIT_GAME_INDEX)
    {
        setCurrentMenuOption(CONTINUE_INDEX);
    }
}

void MainMenuRenderer::returnToPreviousMenuOption()
{
    setCurrentMenuOption(getCurrentMenuOption() - 1);
    if(getCurrentMenuOption() < CONTINUE_INDEX)
    {
        setCurrentMenuOption(EXIT_GAME_INDEX);
    }
}

void MainMenuRenderer::updateUIPositions()
{
    menuTitleLogoVerticalPosition = getCurrentVerticalResolution() / 3.0;

    menuOptionsVerticalPositions[0] = menuTitleLogoVerticalPosition + (MENU_OPTION_INITIAL_OFFSET);

    for(int menuOption = 1; menuOption < NUMBER_OF_SETTINGS_OPTIONS; menuOption++)
    {
        menuOptionsVerticalPositions[menuOption] = (menuOptionsVerticalPositions[menuOption - 1] + MENU_OPTION_SUBSEQUENT_OFFSET);
        menuTextVerticalUIUpperEdgePositions[menuOption] = menuOptionsVerticalPositions[menuOption];
        menuTextVerticalUIULowerEdgePositions[menuOption] = menuOptionsVerticalPositions[menuOption] + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    }
}