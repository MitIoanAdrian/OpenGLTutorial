#pragma once

#include <ogldev_math_3d.h>

class Camera {
public:
  Camera();

  void LookAt(float x, float y, float z);

  void Move(Vector3f distance);

public:
  void setProjection(float height, float width);
    void onYaw(float rad);
    void onPitch(float rad);
  void updateCamera();
  const void setViewMatrix();
    
    
  const Vector3f &getLookAt() const;
    const float &getYaw() const;
  const Matrix4f &getProjectionMatrix() const;
  const Matrix4f &getViewMatrix() const;

private:
    Vector3f m_LookAt;
  Vector3f m_up;
    float m_yaw;
    float m_pitch;
    float m_Distance = 1.0f;
  float m_near = 1.0f;
  float m_far = 10000.0f;
  float m_fov = 90.0f;

protected:
  Matrix4f m_Projection;
  Matrix4f m_View;
};
