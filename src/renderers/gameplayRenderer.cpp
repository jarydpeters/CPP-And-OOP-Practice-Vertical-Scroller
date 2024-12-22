#include "gameplayRenderer.h"

GameplayRenderer::GameplayRenderer(SdlUtility sdlUtility,
            SDL_Window* win, 
            SDL_Renderer* ren,
            std::string titleFontPath,
            std::string subtitleFontPath,
            int titleTextPointSize,
            int subtitleTextPointSize)
    : WindowRenderer(win, ren)
{
    SDL_SetWindowResizable(getWindow(), SDL_bool::SDL_FALSE);

    //TODO: Initialize font rendering using OpenGL (need to implement or use FreeType for this)
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

    setRedballHorizontalPosition(getCurrentHorizontalResolution() / 2.0);
    setRedballVerticalPosition((getCurrentVerticalResolution() * 9.0) / 10.0);
}

void GameplayRenderer::renderMainGame()
{
    SDL_GetWindowSize(getWindow(), &currentHorizontalResolution, &currentVerticalResolution);

    WindowRenderer::renderFPS(getRenderer(), getMenuSubtitleTextFont());

    renderRedball();

    SDL_GL_SwapWindow(getWindow());
}

void GameplayRenderer::renderRedball()
{
    // Create the OpenGL texture for the redball
    TextureRenderer::TextureWithRect textureWithRect = textureRenderer.createAndVerifyOpenGLTexture(
        100, //redballCurrentHorizontalPosition,
        100, //redballCurrentVerticalPosition,
        REDBALL_GAMEPLAY_SPRITE_PATH);

    redballTexture = textureWithRect.texture;
    redballRect = textureWithRect.rectangle;

    if (redballTexture == 0) 
    {
        std::cout << "Failed to load redball texture" << std::endl;
        return;
    }

    // Set up OpenGL texture parameters and drawing
    glBindTexture(GL_TEXTURE_2D, redballTexture);

    // Optionally set up texture filtering and wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Render the redball as a textured quad
    GLfloat vertices[] = {
        static_cast<GLfloat>(redballRect.x), static_cast<GLfloat>(redballRect.y), 0.0f, 0.0f, 0.0f, // Bottom-left corner
        static_cast<GLfloat>(redballRect.x + redballRect.w), static_cast<GLfloat>(redballRect.y), 1.0f, 0.0f, 0.0f, // Bottom-right corner
        static_cast<GLfloat>(redballRect.x + redballRect.w), static_cast<GLfloat>(redballRect.y + redballRect.h), 1.0f, 1.0f, 0.0f, // Top-right corner
        static_cast<GLfloat>(redballRect.x), static_cast<GLfloat>(redballRect.y + redballRect.h), 0.0f, 1.0f, 0.0f  // Top-left corner
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Define the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Draw the textured quad
    glDrawArrays(GL_QUADS, 0, 4);

    // Clean up
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GameplayRenderer::executeGameplayActionBasedOnEvent(const SDL_Event event)
{

}

void GameplayRenderer::destroyTextures()
{
    // Clean up textures (OpenGL)
    if (redballTexture != 0) 
    {
        glDeleteTextures(1, &redballTexture);
        redballTexture = 0;
    }
}

SDL_Window* GameplayRenderer::getMainGameWindow()
{
    return mainGameWindow;
}

void GameplayRenderer::setMainGameWindow(SDL_Window* window)
{
    mainGameWindow = window;
}

SDL_Renderer* GameplayRenderer::getMainGameWindowRenderer()
{
    return mainGameRenderer;
}

void GameplayRenderer::setMainGameRenderer(SDL_Renderer* renderer)
{
    mainGameRenderer = renderer;
}

int GameplayRenderer::getRedballHorizontalPosition()
{
    return redballCurrentHorizontalPosition;
}

void GameplayRenderer::setRedballHorizontalPosition(const int horizontalPosition)
{
    redballCurrentHorizontalPosition = horizontalPosition;
}

int GameplayRenderer::getRedballVerticalPosition()
{
    return redballCurrentVerticalPosition;
}

void GameplayRenderer::setRedballVerticalPosition(const int verticalPosition)
{
    redballCurrentVerticalPosition = verticalPosition;
}