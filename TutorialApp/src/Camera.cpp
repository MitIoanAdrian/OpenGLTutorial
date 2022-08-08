#include <Camera.h>
#include <OGL.h>
#include <ogldev_math_3d.h>

Camera::Camera() {
  m_up = Vector3f(0.0f, 0.0f, 1.0f);
  m_pitch = 0.0f;
  m_yaw = 0.0f;
}

void Camera::LookAt(float x, float y, float z) {
  m_LookAt.x = x;
  m_LookAt.y = y;
  m_LookAt.z = z;
}

void Camera::onYaw(float rad) { m_yaw += rad; }

void Camera::onPitch(float rad) {
  const float half_pi = 89.0f;
  m_pitch = rad;

  if (m_pitch > half_pi)
    m_pitch = half_pi;

  if (m_pitch < -half_pi)
    m_pitch = -half_pi;
}

void Camera::updateCamera() {
  Vector3f dir{1.0f, 0.0f, 0.0f};

  dir.Rotate(m_pitch, (0.0f, 1.0f, 0.0f));
  dir.Rotate(m_yaw, (0.0f, 0.0f, 1.0f));
  m_View.InitCameraTransform(m_LookAt + dir * m_Distance, m_LookAt, m_up);
  // m_View.InitCameraTransform(Vector3f{ 0.0f, 0.0f, 10.0f }, m_LookAt, m_up);
}

const Matrix4f &Camera::getViewMatrix() const { return m_View; }

const Vector3f &Camera::getLookAt() const { return m_LookAt; }

const float &Camera::getYaw() const { return m_yaw; }

void Camera::setProjection(float height, float width) {

  PersProjInfo PersProjInfo = {m_fov, width, height, m_near, m_far};

  m_Projection.InitPersProjTransform(PersProjInfo);
}

const Matrix4f &Camera::getProjectionMatrix() const { return m_Projection; }
