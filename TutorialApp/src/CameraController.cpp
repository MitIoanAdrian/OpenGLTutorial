#include <CameraController.h>
#include <OGL.h>
#include <ogldev_math_3d.h>

Vector3f CameraController::moveCamera(int key, Vector3f camera_pos,
                                      Vector3f camera_target) {
  Vector3f distance = Vector3f(0.0f, 0.0f, 0.0f);
  Vector3f totarget = camera_target - camera_pos;

  switch (key) {
  case GLFW_KEY_UP: // move towards target
    distance += totarget.Normalize();
    break;

  case GLFW_KEY_DOWN: // move away from target
    distance -= totarget.Normalize();
    break;

  case GLFW_KEY_W: // raise camera while looking at target
    distance = Vector3f(0.0f, 1.0f, 0.0f);
    break;

  case GLFW_KEY_S: // lower camera while looking at target
    distance = Vector3f(0.0f, -1.0f, 0.0f);
    break;

  case GLFW_KEY_LEFT: {
    Vector3f Left = totarget.Cross(Vector3f(0.0f, 1.0f, 0.0f));
    Left.Normalize();
    distance += Left;
  } break;

  case GLFW_KEY_RIGHT: // left and right are easier to observe if model rotate
                       // is disabled in //   application
  {
    Vector3f Right = Vector3f(0.0f, 1.0f, 0.0f).Cross(totarget);
    Right.Normalize();
    distance += Right;
  } break;
  }

  return distance;
}
