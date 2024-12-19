#include <fstream>
#include <iostream>
#include <sstream>

#include "shaderUtility.h"

// Utility function to load a shader from a file
std::string readShaderFile(const std::string& filePath) 
{
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

// Function to compile a shader (vertex or fragment)
GLuint compileShader(const std::string& source, GLenum shaderType) 
{
    GLuint shader = glCreateShader(shaderType);
    const char* shaderCode = source.c_str();
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) 
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR: Shader compilation failed\n" << infoLog << std::endl;
    }
    return shader;
}

// Function to load, compile, and link vertex and fragment shaders into a program
GLuint loadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) 
{
    // Load shader source code
    std::string vertexCode = readShaderFile(vertexPath);
    std::string fragmentCode = readShaderFile(fragmentPath);

    // Compile shaders
    GLuint vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

    // Link shaders into a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) 
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR: Shader linking failed\n" << infoLog << std::endl;
    }

    // Clean up shaders (they're linked into the program now)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
