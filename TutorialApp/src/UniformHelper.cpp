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
  return UniformHelper::UniformType::kUniformCount;
}
