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
}

void MainMenuRenderer::renderCurrentScreen(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) 
{
    WindowRenderer::renderFPS(getRenderer(), getMenuSubtitleTextFont());
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

    //TODO: make setting
    WindowRenderer::renderScanLines(getRenderer());

    SDL_RenderPresent(getRenderer());
}

void MainMenuRenderer::evaluateKeystrokeEvent(const SDL_Event event)
{
    if(event.key.keysym.sym == SDLK_UP)
    {
        advanceToNextMenuOption();
    }   
    else if(event.key.keysym.sym == SDLK_DOWN)
    {
        returnToPreviousMenuOption();
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
    
    if((menuTextFirstVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFirstVerticalUILowerEdgePosition))
    {
        setCurrentMenuOption(CONTINUE_INDEX);
    }
    else if((menuTextSecondVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextSecondVerticalUILowerEdgePosition))
    {
        setCurrentMenuOption(NEW_GAME_INDEX);
    }
    else if((menuTextThirdVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextThirdVerticalUILowerEdgePosition))
    {
        setCurrentMenuOption(SETTINGS_INDEX);
    }
    else if((menuTextFourthVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFourthVerticalUILowerEdgePosition))
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