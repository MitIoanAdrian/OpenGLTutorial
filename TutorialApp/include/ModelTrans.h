#pragma once

#include <ogldev_math_3d.h>

class ModelTrans {
public:
  ModelTrans() {}

  void setScale(float scale);
  void setRotation(float x, float y, float z);
  void setPosition(float x, float y, float z);

  void Rotate(float x, float y, float z);

  Matrix4f GetMatrix() const;

private:
  float m_scale = 1.0f;
  Vector3f m_rotation = Vector3f(0.0f, 0.0f, 0.0f);
  Vector3f m_pos = Vector3f(0.0f, 0.0f, 0.0f);
};
