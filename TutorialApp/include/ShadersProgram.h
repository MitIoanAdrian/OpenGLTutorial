#pragma once

#include <OGL.h>
#include <iostream>
#include <ogldev_math_3d.h>

class ShadersProgram {
public:
  ShadersProgram();
  ~ShadersProgram();

public:
  std::string readFile(const char *file);

  void create(const char *vs, const char *fs);

  std::size_t getAttributeCount() const;

  const char *getAttributeName(const std::size_t attribute_index) const;

  void setUniform(Matrix4f);

  std::size_t getUniformCount() const;

  const char *getUniformName(const std::size_t uniform_index) const;

  void bind(); // or glUseProgram

private:
  void addShader(const char *pShaderText, GLenum ShaderType);
  void link();

  const char *m_Vertex_Shader = nullptr;
  const char *m_Fragment_Shader = nullptr;
  GLuint m_Shader_Program;
  GLint m_uOffsetLocation;
};
