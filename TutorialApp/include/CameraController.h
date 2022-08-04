#pragma once

#include <Camera.h>
#include <ogldev_math_3d.h>

class CameraController {
public:
  Vector3f moveCamera(int key, Vector3f LookAt, float yaw);
};
