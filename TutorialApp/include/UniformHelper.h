#pragma once

struct UniformHelper {
  enum UniformType {
    kOffset = 0,
    kMVP,
    kTexture0,
    kTexture1,
    kTexture2,
    kTexture3,
    kTexture4,
    kSplatMapTexture,
    kUniformCount

  };

  static const char *getUniformName(const UniformType t);
  static UniformType getUniformType(const char *uniform_name);
};
