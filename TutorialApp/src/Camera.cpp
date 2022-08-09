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

void Camera::onPitch(float rad) { m_pitch += rad; }

void Camera::moveUp(const double speed) { m_LookAt.z += 100.0f * speed; }

void Camera::moveSide(const double speed) {
  Vector3f dir{0.0f, 1.0f, 0.0f};

  dir.Rotate(m_yaw, {0.0f, 0.0f, 1.0f});

  m_LookAt += (dir * speed) * 1000.0f;
}

void Camera::moveForward(const double speed) {
  Vector3f dir{1.0f, 0.0f, 0.0f};

  dir.Rotate(m_pitch, {0.0f, 1.0f, 0.0f});
  dir.Rotate(m_yaw, {0.0f, 0.0f, 1.0f});

  dir.z = 0;
  dir.Normalize();
  m_LookAt += dir * speed * 1000.0f;
}
void Camera::updateCamera() {
  Vector3f dir{1.0f, 0.0f, 0.0f};

  dir.Rotate(m_pitch, {0.0f, 1.0f, 0.0f});
  dir.Rotate(m_yaw, {0.0f, 0.0f, 1.0f});
  m_View.InitCameraTransform(m_LookAt + dir * m_Distance, m_LookAt, m_up);
}

const Matrix4f &Camera::getViewMatrix() const { return m_View; }

const Vector3f &Camera::getLookAt() const { return m_LookAt; }

const float &Camera::getYaw() const { return m_yaw; }

void Camera::setProjection(float height, float width) {

  PersProjInfo PersProjInfo = {m_fov, width, height, m_near, m_far};

  m_Projection.InitPersProjTransform(PersProjInfo);
}

const Matrix4f &Camera::getProjectionMatrix() const { return m_Projection; }
