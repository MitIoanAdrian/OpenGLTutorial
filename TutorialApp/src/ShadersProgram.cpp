#include <OGL.h>
#include <ShadersProgram.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <ogldev_math_3d.h>
#include <stdio.h>
#include <string.h>

ShadersProgram::ShadersProgram(){};

ShadersProgram::~ShadersProgram(){};

std::string ShadersProgram::readFile(const char *file) {
  std::string toread;
  std::ifstream in;

  in.open(file);

  if (!in.is_open()) {
    std::cout << "Couldn't open: " << file << std::endl;
    exit(1);
  }

  std::string temp;

  while (in) {
    getline(in, temp);
    toread = toread + temp;
    toread.push_back('\n');
  }

  in.close();
  return toread;
}

void ShadersProgram::addShader(const char *pShaderText, GLenum ShaderType) {
  GLuint ShaderObj = glCreateShader(ShaderType);

  if (ShaderObj == 0) {
    fprintf(stderr, "Error creating shader type %d\n", ShaderType);
    exit(0);
  }

  const GLchar *p[1];
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
    fprintf(stderr, "Error compiling shader type %d: '%s\n", ShaderType,
            InfoLog);
    exit(1);
  }

  glAttachShader(m_Shader_Program, ShaderObj);
}

void ShadersProgram::link() {
  GLint Success = 0;
  GLchar ErrorLog[1024] = {0};

  glLinkProgram(m_Shader_Program);

  glGetProgramiv(m_Shader_Program, GL_LINK_STATUS, &Success);
  if (Success == 0) {
    glGetProgramInfoLog(m_Shader_Program, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
    exit(1);
  }

  m_uOffsetLocation = glGetUniformLocation(m_Shader_Program, "gWorld");
  if (m_uOffsetLocation == -1) {
    printf("Error getting uniform location of 'uOffset'\n");
  }
}

void ShadersProgram::setUniform(Matrix4f FinalMatrix) {
  glUniformMatrix4fv(m_uOffsetLocation, 1, GL_TRUE, &FinalMatrix.m[0][0]);
}

void ShadersProgram::create() {
  m_Shader_Program = glCreateProgram();

  if (m_Shader_Program == 0) {
    fprintf(stderr, "Error creating shader program\n");
    exit(1);
  }

  addShader(readFile(m_Vertex_Shader).c_str(), GL_VERTEX_SHADER);

  addShader(readFile(m_Fragment_Shader).c_str(), GL_FRAGMENT_SHADER);

  link();

  bind();
}

void ShadersProgram::bind() { glUseProgram(m_Shader_Program); }
