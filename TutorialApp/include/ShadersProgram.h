#pragma once

#include <OGL.h>
#include <UniformHelper.h>
#include <array>
#include <iostream>
#include <ogldev_math_3d.h>

class ShadersProgram {
public:
  ShadersProgram();
  ~ShadersProgram();

public:
  void create(const char *vs, const char *fs);

  std::size_t getAttributeCount() const;

  const char *getAttributeName(const std::size_t attribute_index) const;

  void setUniformMat4(UniformHelper::UniformType u, const Matrix4f &);
  void setUniformVec2(UniformHelper::UniformType u, const Vector2f &);

  std::size_t getUniformCount() const;

  const char *getUniformName(const std::size_t uniform_index) const;

  void bind(); // or glUseProgram

private:
  void addShader(const char *pShaderText, GLenum ShaderType);
  void link();

  GLuint m_Shader_Program;
  // GLint m_uOffsetLocation;
  std::array<GLuint, UniformHelper::UniformType::kUniformCount>
      m_uniformLocations;

  const char *m_Vertex_Shader = nullptr;
  const char *m_Fragment_Shader = nullptr;
};
