#pragma once

struct UniformHelper {
  enum UniformType {
    kOffset = 0,
    kMVP,
    kTexture,
    kUniformCount

  };

  static const char *getUniformName(const UniformType t);
  static UniformType getUniformType(const char *uniform_name);
};
