#include <iostream>
#include <SDL_ttf.h>

#include "windowRenderer.h"

bool WindowRenderer::quitGame = false;
int WindowRenderer::currentScreen = MAIN_MENU_SCREEN;

bool WindowRenderer::displayFPS = true;
int WindowRenderer::currentFPS = 0;
WindowRenderer::Resolution WindowRenderer::resolution = WindowRenderer::Resolution(DEFAULT_HORIZONTAL_RESOLUTION, DEFAULT_VERTICAL_RESOLUTION);

int WindowRenderer::menuTitleLogoVerticalPosition = (DEFAULT_VERTICAL_RESOLUTION / 3.0);

int WindowRenderer::menuTextFirstVerticalPosition = menuTitleLogoVerticalPosition + (150);
int WindowRenderer::menuTextSecondVerticalPosition = menuTextFirstVerticalPosition + (50);
int WindowRenderer::menuTextThirdVerticalPosition = menuTextSecondVerticalPosition + (50);
int WindowRenderer::menuTextFourthVerticalPosition = menuTextThirdVerticalPosition + (50);
int WindowRenderer::menuTextFifthVerticalPosition = menuTextFourthVerticalPosition + (50);

//TODO: REMOVE ALL SDL RENDERERS
WindowRenderer::WindowRenderer(SDL_Window* win, SDL_Renderer* ren)
{
    window = win;
    renderer = ren;
}

SDL_Window* WindowRenderer::getWindow()
{
    return window;
}

void WindowRenderer::setWindow(SDL_Window* win)
{
    window = win;
}

SDL_Renderer* WindowRenderer::getRenderer()
{
    return renderer;
}

void WindowRenderer::setRenderer(SDL_Renderer* ren)
{
    renderer = ren;
}

bool WindowRenderer::getDisplayFPS()
{
    return displayFPS;
}

void WindowRenderer::setDisplayFPS(const bool newDisplayFPS)
{
    displayFPS = newDisplayFPS;
}

int WindowRenderer::getCurrentFPS()
{
    return currentFPS;
}

void WindowRenderer::setCurrentFPS(const int newCurrentFPS)
{
    currentFPS = newCurrentFPS;
}

int WindowRenderer::getCurrentHorizontalResolution()
{
    return resolution.currentHorizontalResolution;
}

void WindowRenderer::setCurrentHorizontalResolution(const int horizontalResolution)
{
    resolution.currentHorizontalResolution = horizontalResolution;
}

int WindowRenderer::getCurrentVerticalResolution()
{
    return resolution.currentVerticalResolution;
}

void WindowRenderer::setCurrentVerticalResolution(const int verticalResolution)
{
    resolution.currentVerticalResolution = verticalResolution;
}

void WindowRenderer::renderFPS(TTF_Font* menuSubtitleFont)
{
    if (displayFPS)
    {
        // Create a string with the current FPS value
        std::string fpsText = std::to_string(getCurrentFPS());

        // Create a surface from the FPS text using SDL_ttf
        SDL_Surface* textSurface = TTF_RenderText_Solid(menuSubtitleFont, fpsText.c_str(), white);

        if(textSurface == nullptr)
        {
            std::cout << "Error creating text surface: " << TTF_GetError() << std::endl;
            return;
        }

        // Generate an OpenGL texture from the SDL surface
        GLuint textTexture;
        glGenTextures(1, &textTexture);
        glBindTexture(GL_TEXTURE_2D, textTexture);

        // Upload the surface data to the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textSurface->w, textSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textSurface->pixels);

        // Set texture filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Set up the destination rectangle for rendering (top-left corner)
        GLfloat x = 10.0f;
        GLfloat y = 10.0f;
        GLfloat width = static_cast<GLfloat>(textSurface->w);
        GLfloat height = static_cast<GLfloat>(textSurface->h);

        GLfloat vertices[] = 
        {
            static_cast<GLfloat>(x),               static_cast<GLfloat>(y),                0.0f, 0.0f, // Bottom-left corner
            static_cast<GLfloat>(x + width),       static_cast<GLfloat>(y),                1.0f, 0.0f, // Bottom-right corner
            static_cast<GLfloat>(x + width),       static_cast<GLfloat>(y + height),       1.0f, 1.0f, // Top-right corner
            static_cast<GLfloat>(x),               static_cast<GLfloat>(y + height),       0.0f, 1.0f  // Top-left corner
        };

         // Clean up the SDL surface now that we've uploaded it to an OpenGL texture
        SDL_FreeSurface(textSurface);

        // Use the shader program
        //glUseProgram(shaderProgram);

        // Set up the vertex buffer and attributes (assuming you have VBO/VAO set up)
        GLuint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Enable the position and texture coordinates attributes (adjust the attribute pointers as necessary)
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0); // Vertex position
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat))); // Texture coordinates
        glEnableVertexAttribArray(1);

        // Bind the texture and draw the quad
        glBindTexture(GL_TEXTURE_2D, textTexture);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // Clean up
        glDeleteTextures(1, &textTexture);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
}

TTF_Font* WindowRenderer::getMenuTitleTextFont()
{
    return menuTitleFont;
}

void WindowRenderer::setMenuTitleTextFont(TTF_Font* font)
{
    menuTitleFont = font;
}

TTF_Font* WindowRenderer::getMenuSubtitleTextFont()
{
    return menuSubtitleFont;
}

void WindowRenderer::setMenuSubtitleTextFont(TTF_Font* font)
{
    menuSubtitleFont = font;
}
