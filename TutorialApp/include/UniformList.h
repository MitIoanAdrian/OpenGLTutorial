#pragma once

#include <ShadersProgram.h>
#include <UniformHelper.h>
#include <ogldev_math_3d.h>

struct IUniformNode {
  IUniformNode *next = nullptr;

  UniformHelper::UniformType uniform;
  virtual void set_uniform(ShadersProgram *sp) = 0;
};

struct UniformIntegerNode : public IUniformNode {
  int value;
  void set_uniform(ShadersProgram *sp) override;
};

struct UniformFloatNode : public IUniformNode {
  float value;
  void set_uniform(ShadersProgram *sp) override;
};

struct UniformVector2fNode : public IUniformNode {
  Vector2f value;
  void set_uniform(ShadersProgram *sp) override;
};

struct UniformVector3fNode : public IUniformNode {
  Vector3f value;
  void set_uniform(ShadersProgram *sp) override;
};

struct UniformMatrix3fNode : public IUniformNode {
  Matrix3f value;
  void set_uniform(ShadersProgram *sp) override;
};

struct UniformMatrix4fNode : public IUniformNode {
  Matrix4f value;
  void set_uniform(ShadersProgram *sp) override;
};
