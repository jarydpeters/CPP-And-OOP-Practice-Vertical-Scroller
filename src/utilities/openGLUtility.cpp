#include "openGLUtility.h"

SDL_GLContext glContext;
GLuint shaderProgram;
GLuint VAO;
GLuint VBO;

void initOpenGL(SDL_Window* window) 
{
    glewInit();  // Initialize GLEW

    glMatrixMode(GL_PROJECTION);  // Switch to projection matrix
    glLoadIdentity();             // Reset the projection matrix
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);  // Create an orthographic projection
    glMatrixMode(GL_MODELVIEW);   // Switch back to modelview matrix

    //TODO: UPDATE RENDERING FOR 3.3
    // Set SDL attributes for OpenGL version and profile
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

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

    // Set uniform values
    glUseProgram(shaderProgram);

    // Set the distortion amount (adjust this value as necessary)
    glUniform1f(glGetUniformLocation(shaderProgram, "distortionAmount"), 0.1f);

    // Set the screen size (replace with your actual screen size)
    glUniform2f(glGetUniformLocation(shaderProgram, "screenSize"), 800.0f, 600.0f);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set the texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(MENU_LOGO_IMAGE_PATH, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

    // Set the OpenGL viewport (typically after the context and shaders are set up)
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);  // Get window size
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

    // Create Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object
    glBindVertexArray(VAO);

    // Bind the VBO and upload the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    // Position attribute (layout location = 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute (layout location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}