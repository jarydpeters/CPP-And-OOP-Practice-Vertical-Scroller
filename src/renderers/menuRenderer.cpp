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

    menuTextFirstVerticalPosition = menuTitleLogoVerticalPosition + (150);
    menuTextSecondVerticalPosition = menuTextFirstVerticalPosition + (50);
    menuTextThirdVerticalPosition = menuTextSecondVerticalPosition + (50);
    menuTextFourthVerticalPosition = menuTextThirdVerticalPosition + (50);
    menuTextFifthVerticalPosition = menuTextFourthVerticalPosition + (50);

    menuTextFirstVerticalUIUpperEdgePosition = menuTextFirstVerticalPosition - UISelectionMargin;
    menuTextSecondVerticalUIUpperEdgePosition = menuTextSecondVerticalPosition - UISelectionMargin;
    menuTextThirdVerticalUIUpperEdgePosition = menuTextThirdVerticalPosition - UISelectionMargin;
    menuTextFourthVerticalUIUpperEdgePosition = menuTextFourthVerticalPosition - UISelectionMargin;
    menuTextFifthVerticalUIUpperEdgePosition = menuTextFifthVerticalPosition - UISelectionMargin;

    menuTextFirstVerticalUILowerEdgePosition = menuTextFirstVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    menuTextSecondVerticalUILowerEdgePosition = menuTextSecondVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    menuTextThirdVerticalUILowerEdgePosition = menuTextThirdVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    menuTextFourthVerticalUILowerEdgePosition = menuTextFourthVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
    menuTextFifthVerticalUILowerEdgePosition = menuTextFifthVerticalPosition + SUBTITLE_TEXT_POINT_SIZE + UISelectionMargin;
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
    // Create the texture and retrieve the textureID and SDL_Rect
    TextureRenderer::TextureWithRect textureWithRect = textureRenderer.createAndVerifyOpenGLTexture(
        ((getCurrentHorizontalResolution() / 2) - MAIN_MENU_LOGO_HORIZONTAL_OFFSET), 
        (menuTitleLogoVerticalPosition - MAIN_MENU_LOGO_VERTICAL_OFFSET),
        MENU_LOGO_IMAGE_PATH);

    GLuint textureID = textureWithRect.texture;  // Extract the texture ID
    SDL_Rect textureRect = textureWithRect.rectangle;  // Extract the rectangle data

    // Scale the texture with OpenGL (no SDL scaling)
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Render the logo (you need to draw this texture in a quad)
    renderQuadWithTexture(textureID, textureRect);  // Use the texture rectangle
}


void MenuRenderer::renderQuadWithTexture(GLuint textureID, const SDL_Rect& rect)
{
    // Set up OpenGL to render the texture on a quad
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set up the vertices for the quad
    GLfloat vertices[] = 
    {
        (GLfloat)rect.x, (GLfloat)rect.y, 0.0f, 0.0f,  // Bottom-left corner (x, y) and texture coordinates (u, v)
        (GLfloat)(rect.x + rect.w), (GLfloat)rect.y, 1.0f, 0.0f, // Bottom-right corner
        (GLfloat)rect.x, (GLfloat)(rect.y + rect.h), 0.0f, 1.0f, // Top-left corner
        (GLfloat)(rect.x + rect.w), (GLfloat)(rect.y + rect.h), 1.0f, 1.0f // Top-right corner
    };

    // Set up the indices (two triangles for the quad)
    GLuint indices[] = { 0, 1, 2, 1, 2, 3 };

    // Create VBOs (Vertex Buffer Objects) and VAOs (Vertex Array Objects)
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Draw the quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Clean up
    glBindVertexArray(0);
}

void MenuRenderer::renderMenuOptionSelectionSprite()
{
    int menuSelectionIconVerticalPosition;

    // Determine the vertical position based on the selected menu option
    switch(currentlySelectedMenuOption)
    {
        case(0):
            menuSelectionIconVerticalPosition = (menuTextFirstVerticalPosition - MENU_SELECTION_ICON_VERTICAL_OFFSET);
            break;
        case(1):
            menuSelectionIconVerticalPosition = (menuTextSecondVerticalPosition - MENU_SELECTION_ICON_VERTICAL_OFFSET);
            break;
        case(2):
            menuSelectionIconVerticalPosition = (menuTextThirdVerticalPosition - MENU_SELECTION_ICON_VERTICAL_OFFSET);
            break;
        case(3):
            menuSelectionIconVerticalPosition = (menuTextFourthVerticalPosition - MENU_SELECTION_ICON_VERTICAL_OFFSET);
            break;
        case(4):
            menuSelectionIconVerticalPosition = (menuTextFifthVerticalPosition - MENU_SELECTION_ICON_VERTICAL_OFFSET);
            break;
    }

    // Create the texture and get both textureID and the rectangle data
    TextureRenderer::TextureWithRect textureWithRect = textureRenderer.createAndVerifyOpenGLTexture(
        0, // place on far left side of screen
        menuSelectionIconVerticalPosition,
        MENU_SELECTION_ICON_IMAGE_PATH);

    GLuint textureID = textureWithRect.texture;  // Extract the texture ID
    SDL_Rect textureRect = textureWithRect.rectangle;  // Extract the rectangle data

    // Scale the texture with OpenGL (no SDL scaling)
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Render the menu option selection sprite (you need to draw this texture in a quad)
    renderQuadWithTexture(textureID, textureRect);  // Use the extracted rectangle
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