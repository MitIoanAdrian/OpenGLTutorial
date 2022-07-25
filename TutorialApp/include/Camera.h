#pragma once

#include <ogldev_math_3d.h>

class Camera {
public:
  Camera();

  void LookAt(float x, float y, float z);

  void Move(Vector3f distance);

public:
  void setProjection(float height, float width);
  const void setViewMatrix();

  const Vector3f &getPosition() const;
  const Vector3f &getTarget() const;

  const Matrix4f &getProjectionMatrix() const;
  const Matrix4f &getViewMatrix();

private:
  Vector3f m_pos;
  Vector3f m_target;
  Vector3f m_up;
  float m_near = 1.0f;
  float m_far = 1000.0f;
  float m_fov = 90.0f;

protected:
  Matrix4f m_Projection;
  Matrix4f m_View;
};
