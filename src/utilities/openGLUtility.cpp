#include "openGLUtility.h"

SDL_GLContext glContext;
GLuint shaderProgram;

void initOpenGL(SDL_Window* window) 
{
    // Set SDL attributes for OpenGL version and profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create OpenGL context
    glContext = SDL_GL_CreateContext(window);

    // Check if the context was created successfully
    if (!glContext) 
    {
        std::cout << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Initialize GLEW
    GLenum glewError = glewInit();
    if (GLEW_OK != glewError) 
    {
        std::cout << "GLEW Error: " << glewGetErrorString(glewError) << std::endl;
        SDL_GL_DeleteContext(glContext);
        exit(1);
    }

    // Load and compile shaders
    shaderProgram = loadShaderProgram(VERTEX_SHADER_PATH, BARREL_DISTORTION_SHADER_PATH);

    // Check if the shader program was loaded correctly
    if (shaderProgram == 0)
    {
        std::cout << "Failed to load shader program!" << std::endl;
        SDL_GL_DeleteContext(glContext);
        exit(1);
    }

    // Use the shader program
    //glUseProgram(shaderProgram);

    // Set the OpenGL viewport (typically after the context and shaders are set up)
    int width, height;
    SDL_GetWindowSize(window, &width, &height);  // Get window size
    glViewport(0, 0, width, height);  // Set the OpenGL viewport to match the window size
}

void cleanupOpenGL() 
{
    glDeleteProgram(shaderProgram);
    SDL_GL_DeleteContext(glContext);
}

void renderQuadWithTexture(GLuint textureID, const SDL_Rect& rect)
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