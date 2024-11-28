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
    updateResolution();
}

void MainMenuRenderer::renderCurrentScreen(TextRenderer& menuTitleTextRenderer, TextRenderer& menuSubtextRenderer) 
{
    RenderMainMenuLogo();
    RenderMenuOptionSelectionSprite();

    menuSubtextRenderer.renderHorizontallyCenteredText(menuScreenWindowRenderer, 
        MAIN_MENU_CONTINUE_TEXT, 
        menuTextFirstVerticalPosition, 
        ((currentlySelectedMainMenuOption == CONTINUE_INDEX) ? black : white), 
        menuScreenWindow);
    menuSubtextRenderer.renderHorizontallyCenteredText(menuScreenWindowRenderer, 
        MAIN_MENU_NEW_GAME_TEXT, 
        menuTextSecondVerticalPosition, 
        ((currentlySelectedMainMenuOption == NEW_GAME_INDEX) ? black : white), 
        menuScreenWindow);
    menuSubtextRenderer.renderHorizontallyCenteredText(menuScreenWindowRenderer, 
        MAIN_MENU_SETTINGS_TEXT, 
        menuTextThirdVerticalPosition, 
        ((currentlySelectedMainMenuOption == SETTINGS_INDEX) ? black : white), 
        menuScreenWindow);
    menuSubtextRenderer.renderHorizontallyCenteredText(menuScreenWindowRenderer, 
        MAIN_MENU_EXIT_TEXT, 
        menuTextFourthVerticalPosition, 
        ((currentlySelectedMainMenuOption == EXIT_GAME_INDEX) ? black : white), 
        menuScreenWindow);

    SDL_RenderPresent(menuScreenWindowRenderer);
}

void MainMenuRenderer::evaluateKeystrokeEvent(const SDL_Event event)
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
                currentScreen = SETTINGS_MENU_SCREEN;
                setCurrentMenu(SETTINGS_MENU_INDEX, RETURN_TO_MAIN_MENU_INDEX);
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
        currentlySelectedMainMenuOption = CONTINUE_INDEX;
    }
    else if((menuTextSecondVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextSecondVerticalUILowerEdgePosition))
    {
        currentlySelectedMainMenuOption = NEW_GAME_INDEX;
    }
    else if((menuTextThirdVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextThirdVerticalUILowerEdgePosition))
    {
        currentlySelectedMainMenuOption = SETTINGS_INDEX;
    }
    else if((menuTextFourthVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFourthVerticalUILowerEdgePosition))
    {
        currentlySelectedMainMenuOption = EXIT_GAME_INDEX;
    }
    else if((menuTextFifthVerticalUIUpperEdgePosition < currentVerticalMousePosition) && (currentVerticalMousePosition < menuTextFifthVerticalUILowerEdgePosition))
    {
        //no fifth option on main menu
    }
}


void MainMenuRenderer::evaluateMouseWheelEvent(const SDL_Event event)
{
    //scroll up
    if(event.wheel.y < 0)
    {
        currentlySelectedMainMenuOption++;
        if(currentlySelectedMainMenuOption > RETURN_TO_MAIN_MENU_INDEX)
        {
            currentlySelectedMainMenuOption = FULLSCREEN_INDEX;
        }
    }
    //scroll down
    else if(event.wheel.y > 0)
    {
        currentlySelectedMainMenuOption--;
        if(currentlySelectedMainMenuOption < FULLSCREEN_INDEX)
        {
            currentlySelectedMainMenuOption = RETURN_TO_MAIN_MENU_INDEX;
        }
    }
}

void MainMenuRenderer::evaluateMouseButtonEvent(const SDL_Event event)
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
            currentScreen = SETTINGS_MENU_SCREEN;
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
}