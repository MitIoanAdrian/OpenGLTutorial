#include <Camera.h>
#include <OGL.h>
#include <ogldev_math_3d.h>

Camera::Camera() {
  m_pos = Vector3f(3.0f, 3.0f, 2.0f);
  m_target = Vector3f(0.0f, 0.0f, 0.0f);
  m_up = Vector3f(0.0f, 1.0f, 0.0f);
}

void Camera::LookAt(float x, float y, float z) {
  m_pos.x = x;
  m_pos.y = y;
  m_pos.z = z;
}

void Camera::Move(int Key) {
  /*  switch (Key) {

    case GLFW_KEY_UP:
      m_pos += (m_target * m_speed);
      break;

    case GLFW_KEY_DOWN:
      m_pos -= (m_target * m_speed);
      break;

    case GLFW_KEY_LEFT: {
      Vector3f Left = m_target.Cross(m_up);
      Left.Normalize();
      Left *= m_speed;
      m_pos += Left;
    }

    break;

    case GLFW_KEY_RIGHT: {
      Vector3f Right = m_up.Cross(m_target);
      Right.Normalize();
      Right *= m_speed;
      m_pos += Right;
    } break;

    case GLFW_KEY_W:
      m_pos.y += m_speed;
      break;

    case GLFW_KEY_S:
      m_pos -= m_speed;
      break;

    case '+': {
      m_speed -= 0.1f;
      printf("Speed changed to %f\n", m_speed);
    } break;

    case '-': {
      m_speed -= 0.1f;
      if (m_speed < 0.1f)
        m_speed = 0.1f;
      printf("Speed changed to %f\n", m_speed);
    }

    break;
    }*/
}

Matrix4f Camera::getViewMatrix() {

  m_View.InitCameraTransform(m_pos, m_target, m_up);

  return m_View;
}

void Camera::setProjection(float height, float width) {

  PersProjInfo PersProjInfo = {m_fov, width, height, m_near, m_far};

  m_Projection.InitPersProjTransform(PersProjInfo);
}

Matrix4f Camera::getProjectionMatrix() { return m_Projection; }
