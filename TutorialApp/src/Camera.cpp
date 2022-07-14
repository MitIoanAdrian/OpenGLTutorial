#include <Camera.h>
#include <OGL.h>
#include <ogldev_math_3d.h>


Camera::Camera(){
	m_pos = Vector3f(0.0f, 0.0f, 0.0f);
	m_target = Vector3f(0.0f, 0.0f, 1.0f);
	m_up = Vector3f(0.0f, 1.0f, 0.0f);
}

void Camera::LookAt(float x, float y, float z){
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Camera::Move(unsigned char Key){
	switch(Key){

		case GLFW_KEY_UP:
			m_pos += (m_target * m_speed);
			break;

		case GLFW_KEY_DOWN:
			m_pos -= (m_target * m_speed);
			break;

		case GLFW_KEY_LEFT:{
			Vector3f Left = m_target.Cross(m_up);
			Left.Normalize();
			Left *= m_speed;
			m_pos += Left;
		}

			break;

		case GLFW_KEY_RIGHT:{
			Vector3f Right = m_up.Cross(m_target);
			Right.Normalize();
			Right *= m_speed;
			m_pos += Right;
		}
			break;

		case GLFW_KEY_PAGE_UP:
			m_pos.y += m_speed;
			break;

		case GLFW_KEY_PAGE_DOWN:
			m_pos -= m_speed;
			break;

		case '+':{
			m_speed -= 0.1f;
			printf("Speed changed to %f\n", m_speed);
		}
			break;

		case '-':{
			m_speed -= 0.1f;
			if(m_speed < 0.1f)
				m_speed = 0.1f;
			printf("Speed changed to %f\n", m_speed);
		}

		break;
	}
}


Matrix4f Camera::getViewMatrix(){
    
    Matrix4f CameraTransformation;
    CameraTransformation.InitCameraTransform(m_pos, m_target, m_up);
    
    return CameraTransformation;
}

void Camera::setProjection(float near, float far, float fov, float view_size){

	float tanHalfFov = tanf(ToRadian(fov/2.0f));
	float d = 1/ tanHalfFov;
	float range = near - far;
	float A = (-far - near)/range;
	float B = 2.0f * far * near / range;
    
    m_Projection.m[0][0] = d/view_size;
    m_Projection.m[0][1] = 0.0f;
    m_Projection.m[0][2] = 0.0f;
    m_Projection.m[0][3] = 0.0f;
    m_Projection.m[1][0] = 0.0f;
    m_Projection.m[1][1] = d;
    m_Projection.m[1][2] = 0.0f;
    m_Projection.m[1][3] = 0.0f;
    m_Projection.m[2][0] = 0.0f;
    m_Projection.m[2][1] = 0.0f;
    m_Projection.m[2][2] = A;
    m_Projection.m[2][3] = B;
    m_Projection.m[3][0] = 0.0f;
    m_Projection.m[3][1] = 0.0f;
    m_Projection.m[3][2] = 1.0f;
    m_Projection.m[3][3] = 0.0f;

}

Matrix4f Camera::getProjectionMatrix(){ return m_Projection; }

