#pragma once

class Camera
{
	public:
		void LookAt(target, from_position);

		void Move(vec3 distance);

		mat4 getViewMatrix();
	public:
		void setProjection(near, far, fov, view_size);

		mat4 getProjectionMatrix();
}