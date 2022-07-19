#include <Camera.h>
#include <OGL.h>
#include <ogldev_math_3d.h>

Camera::Camera() {
  m_pos = Vector3f(3.0f, 3.0f, 2.0f);
  m_target = Vector3f(0.0f, 0.0f, 0.0f);
  m_up = Vector3f(0.0f, 1.0f, 0.0f);
}

void Camera::LookAt(float x, float y, float z) {
  m_target.x = x;
  m_target.y = y;
  m_target.z = z;
}

void Camera::Move(Vector3f distance) { m_pos += distance; }

Matrix4f Camera::getViewMatrix() {

  m_View.InitCameraTransform(m_pos, m_target, m_up);

  return m_View;
}

Vector3f Camera::getTarget() { return m_target; }

Vector3f Camera::getPosition() { return m_pos; }

void Camera::setProjection(float height, float width) {

  PersProjInfo PersProjInfo = {m_fov, width, height, m_near, m_far};

  m_Projection.InitPersProjTransform(PersProjInfo);
}

Matrix4f Camera::getProjectionMatrix() { return m_Projection; }
