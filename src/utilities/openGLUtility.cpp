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
    glUseProgram(shaderProgram);

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
