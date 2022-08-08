#include <UniformHelper.h>
#include <iostream>

const char *UniformHelper::getUniformName(const UniformType t) {
  switch (t) {
  case UniformHelper::UniformType::kOffset:
    return "Offset";
    break;
  case UniformHelper::UniformType::kMVP:
    return "MVP";
    break;
  case UniformHelper::UniformType::kTexture0:
    return "Texture0";
    break;
  case UniformHelper::UniformType::kTexture1:
    return "Texture1";
    break;
  case UniformHelper::UniformType::kTexture2:
    return "Texture2";
    break;
  case UniformHelper::UniformType::kTexture3:
    return "Texture3";
    break;
  case UniformHelper::UniformType::kTexture4:
    return "Texture4";
    break;
  case UniformHelper::UniformType::kSplatMapTexture:
    return "SplatMapTexture";
    break;
  case UniformHelper::UniformType::kUniformCount:
    return "UniformCount";
    break;
  default:
    break;
    return nullptr;
  }
}

UniformHelper::UniformType
UniformHelper::getUniformType(const char *uniform_name) {
  if (strcmp(uniform_name, "Offset") == 0)
    return UniformHelper::UniformType::kOffset;
  if (strcmp(uniform_name, "MVP") == 0)
    return UniformHelper::UniformType::kMVP;
  if (strcmp(uniform_name, "Texture0") == 0)
    return UniformHelper::UniformType::kTexture0;
  if (strcmp(uniform_name, "Texture1") == 0)
    return UniformHelper::UniformType::kTexture1;
  if (strcmp(uniform_name, "Texture2") == 0)
    return UniformHelper::UniformType::kTexture2;
  if (strcmp(uniform_name, "Texture3") == 0)
    return UniformHelper::UniformType::kTexture3;
  if (strcmp(uniform_name, "Texture4") == 0)
    return UniformHelper::UniformType::kTexture4;
  if (strcmp(uniform_name, "SplatMapTexture") == 0)
    return UniformHelper::UniformType::kSplatMapTexture;
  return UniformHelper::UniformType::kUniformCount;
}
