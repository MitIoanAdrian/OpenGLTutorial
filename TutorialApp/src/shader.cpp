
#include <shader.h>
#include <iostream>
#include <OGL.h>
#include <fstream>
#include <istream>

const char* pVSFileName = "/Users/adrianm2/Desktop/OpenGLWindow/OpenGLWindow/TutorialApp/shaders/shader.vs";

const char* pFSFileName = "/Users/adrianm2/Desktop/OpenGLWindow/OpenGLWindow/TutorialApp/shaders/shader.fs";

std::string ReadFile(const char* fileName){
    
    std::string file;
    std::ifstream in;
    
    in.open(fileName);
    
    if(!in.is_open()){
        std::cout<<"Couldn't open: "<<fileName<<std::endl;
        exit(1);
    }
    
    std::string temp;
    
    while(in){
        getline(in, temp);
        file = file + temp;
        file.push_back('\n');
    }
    
    in.close();
    
    return file;
}
    

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;

    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

static void Link(GLuint ShaderProgram){
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }
}



void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    
    AddShader(ShaderProgram, ReadFile(pVSFileName).c_str(), GL_VERTEX_SHADER);

    AddShader(ShaderProgram, ReadFile(pFSFileName).c_str(), GL_FRAGMENT_SHADER);
    

    Link(ShaderProgram);
   

    glUseProgram(ShaderProgram);
}

