#pragma once

#include <ogldev_math_3d.h>

class Camera {
public:
    Camera();
    
    void LookAt(float x, float y, float z);

  void Move(unsigned char Key);

  Matrix4f getViewMatrix();

public:
  void setProjection(float near, float far, float fov, float view_size);

  Matrix4f getProjectionMatrix();

private:
    Matrix4f m_Projection;
    
    Vector3f m_pos;
	Vector3f m_target;
	Vector3f m_up;
	float m_speed = 1;
};

