#pragma once

#include <OGL.h>
#include <UniformHelper.h>
#include <array>
#include <functional>
#include <iostream>
#include <ogldev_math_3d.h>
#include <set>
#include <string>
#include <vector>

enum class BlendingFunc {
  NONE = 0,

  src_COLOR,
  ONE_MINUS_SRC_COLOR,
  DST_COLOR,
  ONE_MINUS_DST_COLOR,
  SRC_ALPHA,
  ONE_MINUS_SRC_ALPHA,
  DST_ALPHA,
  ONE_MINUS_DST_ALPHA,
  CONSTANT_COLOR,
  ONE_MINUS_CONSTANT_COLOR,
  CONSTANT_ALPHA,
  ONE_MINUS_CONSTANT_ALPHA,

  Count
};

struct BlendingState {
  bool enabled = false;

  BlendingFunc source_func = BlendingFunc::NONE;
  BlendingFunc dest_func = BlendingFunc::NONE;

  bool equals(const BlendingState &cmp) const;

  bool operator==(const BlendingState &other) const;
  bool operator!=(const BlendingState &other) const;
  bool operator<(const BlendingState &other) const;
};

class ShadersProgram {
public:
  ShadersProgram();
  ~ShadersProgram();

public:
  void create(const char *vs, const char *fs);

  std::size_t getAttributeCount() const;

  const char *getAttributeName(const std::size_t attribute_index) const;

  void set_uniform(UniformHelper::UniformType u, int value);
  void set_uniform(UniformHelper::UniformType u, float value);
  void set_uniform(UniformHelper::UniformType u, const Matrix3f &Matrix);
  void set_uniform(UniformHelper::UniformType u, const Matrix4f &Matrix);
  void set_uniform(UniformHelper::UniformType u, const Vector2f &Vector);
  void set_uniform(UniformHelper::UniformType u, const Vector3f &Vector);

  std::size_t getUniformCount() const;

  const char *getUniformName(const std::size_t uniform_index) const;

  void bind(); // or glUseProgram
  inline void setBlendingState(BlendingState &blend) {
    m_BlendingState = blend;
  }
  inline const BlendingState &getBlendingState() const {
    return m_BlendingState;
  }

  bool operator<(const ShadersProgram &other);

  bool operator!=(const ShadersProgram &other);

private:
  void addShader(const char *pShaderText, GLenum ShaderType);
  void link();

  BlendingState m_BlendingState;

  GLuint m_Shader_Program;
  // GLint m_uOffsetLocation;
  std::array<GLuint, UniformHelper::UniformType::kUniformCount>
      m_uniformLocations;

  const char *m_Vertex_Shader = nullptr;
  const char *m_Fragment_Shader = nullptr;
};

/*struct ShaderPreprocessing
{
private:
    struct BlendingFuncMap
    {
        BlendingFuncMap();
        std::array<std::pair<std::string, BlendingFunc>,
(std::size_t)BlendingFunc::Count> blending_funcs;
    };

public:
    static BlendingFunc get_blending_func(const char* );
//    static bool process_text(ShadersProgram&, std::stringstream&,
ResourceManager&, std::set<std::string>&, std::string& out);
 //   static bool process_line(ShadersProgram&, const std::string& line,
ResourceManager&, std::set<std::string>&, std::string& out);
};
*/
