#include "textureRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureRenderer::TextureRenderer()
    : textureID(0), rectangle{0, 0, 0, 0}  // Initialize OpenGL texture ID and rectangle
{
}

TextureRenderer::TextureWithRect TextureRenderer::createAndVerifyOpenGLTexture(int horizontalPosition, int verticalPosition, const char* imagePath)
{
    TextureRenderer::TextureWithRect textureWithRect = {0, { 0, 0, 0, 0 }};

    // Load the image using stb_image
    int width, height, channels;
    unsigned char* imageData = stbi_load(imagePath, &width, &height, &channels, STBI_rgb_alpha); // Ensure RGBA format

    if (!imageData)
    {
        std::cerr << "Failed to load texture: " << imagePath << std::endl;
        return textureWithRect;  // Return an empty structure if texture creation fails
    }

    // Generate an OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // Linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Clamp to edge (no wrapping)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Clamp to edge

    // Load the texture data into OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    // Free the image data as it's now loaded into OpenGL
    stbi_image_free(imageData);

    // Optionally, generate mipmaps for texture scaling
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set up the rectangle for positioning and sizing
    textureWithRect.texture = textureID;

    // Query the OpenGL texture dimensions
    int textureWidth, textureHeight;
    glBindTexture(GL_TEXTURE_2D, textureID);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

    SDL_Rect textureRect = {
        horizontalPosition,
        verticalPosition,
        textureWidth,
        textureHeight
    };

    textureWithRect.rectangle = textureRect;

    return textureWithRect;
}

void TextureRenderer::renderTexture(const TextureWithRect& textureWithRect)
{
    glBindTexture(GL_TEXTURE_2D, textureWithRect.texture);

    // Enable texture and set up vertex data for rendering a quad
    GLfloat vertices[] = 
    {
        static_cast<GLfloat>(textureWithRect.rectangle.x), 
        static_cast<GLfloat>(textureWithRect.rectangle.y), 
        0.0f, 0.0f, 0.0f, // Bottom-left corner
        
        static_cast<GLfloat>(textureWithRect.rectangle.x + textureWithRect.rectangle.w), 
        static_cast<GLfloat>(textureWithRect.rectangle.y), 
        1.0f, 0.0f, 0.0f, // Bottom-right corner
        
        static_cast<GLfloat>(textureWithRect.rectangle.x + textureWithRect.rectangle.w), 
        static_cast<GLfloat>(textureWithRect.rectangle.y + textureWithRect.rectangle.h), 
        1.0f, 1.0f, 0.0f, // Top-right corner
        
        static_cast<GLfloat>(textureWithRect.rectangle.x), 
        static_cast<GLfloat>(textureWithRect.rectangle.y + textureWithRect.rectangle.h), 
        0.0f, 1.0f, 0.0f // Top-left corner
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

    // Draw the texture (quad)
    glDrawArrays(GL_QUADS, 0, 4);

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
