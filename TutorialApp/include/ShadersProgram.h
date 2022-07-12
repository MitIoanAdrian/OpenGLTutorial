#pragma once

#include <OGL.h>
#include <iostream>
#include <ogldev_math_3d.h>
#include <stdio.h>
#include <string.h>

class ShadersProgram {
public:
  ShadersProgram();
  ~ShadersProgram();

public:
  std::string readFile(const char *file);

  void addShader(const char *pShaderText, GLenum ShaderType);

  void link();

  void create();

  std::size_t getAttributeCount() const;

  const char *getAttributeName(const std::size_t attribute_index) const;

  void setUniform(Vector2f);

  std::size_t getUniformCount() const;

  const char *getUniformName(const std::size_t uniform_index) const;

  void bind(); // or glUseProgram

private:
  const char *m_Vertex_Shader = "/Users/adrianm2/Desktop/OpenGLWindow/"
                                "OpenGLWindow/TutorialApp/shaders/shader.vs";
  const char *m_Fragment_Shader = "/Users/adrianm2/Desktop/OpenGLWindow/"
                                  "OpenGLWindow/TutorialApp/shaders/shader.fs";
  GLuint m_Shader_Program;
  GLint m_uOffsetLocation;
};
