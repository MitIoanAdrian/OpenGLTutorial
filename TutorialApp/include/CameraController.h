#pragma once

#include <Camera.h>

class CameraController {
public:
  Vector3f moveCamera(int key, Vector3f camera_pos, Vector3f camera_target);
};
