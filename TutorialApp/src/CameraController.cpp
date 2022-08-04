#include <CameraController.h>
#include <OGL.h>
#include <ogldev_math_3d.h>


Vector3f CameraController::moveCamera(int key, Vector3f LookAt, float yaw) {
  Vector3f distance = Vector3f(0.0f, 0.0f, 0.0f);


  switch (key) {
  case GLFW_KEY_UP: // move towards target
      {
          Vector3f dir {1.0f, 0.0f, 0.0f};
          dir.Rotate(yaw,(0.0f,0.0f,1.0f));
          LookAt = LookAt - dir;
      }
    break;

  case GLFW_KEY_DOWN: // move away from target
      {
          Vector3f dir {1.0f, 0.0f, 0.0f};
          dir.Rotate(yaw,(0.0f,0.0f,1.0f));
          LookAt = LookAt + dir;
      }
    break;

  case GLFW_KEY_W: // raise camera while looking at target
          LookAt.z += 1;
    break;

  case GLFW_KEY_S: // lower camera while looking at target
          LookAt.z -= 1;
    break;

  case GLFW_KEY_LEFT: {
      Vector3f dir{ 0.0f, 1.0f, 0.0f };

         dir.Rotate(yaw,(0.0f, 0.0f, 1.0f));

         LookAt = LookAt + dir;
  } break;

  case GLFW_KEY_RIGHT:
  {
      Vector3f dir{ 0.0f, 1.0f, 0.0f };

         dir.Rotate(yaw, (0.0f,0.0f,1.0f));

         LookAt = LookAt - dir;
  } break;
  }

  return LookAt;
}


