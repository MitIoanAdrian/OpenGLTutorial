#include <ModelTrans.h>
#include <ogldev_math_3d.h>

void ModelTrans::SetScale(float scale){

	m_scale = scale;
}

void ModelTrans::SetRotation(float x, float y, float z){

	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void ModelTrans::SetPosition(float x, float y, float z){

	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void ModelTrans::Rotate(float x, float y, float z){

	m_rotation.x += x;
	m_rotation.y += y;
	m_rotation.z += z;
}

Matrix4f WorldTrans::GetMatrix(){

	Matrix4f Scale;
	Scale.InitScaleTransform(m_scale, m_scale, m_scale);

	Matrix4f Rotation;
	Scale.InitRotateTransform(m_rotation.x, m_rotation.y, m_rotation,z);

	Matrix4f Translation;
	Translation.InitTranslationTransform(m_pos.x, m_pos.y, m_pos.z);

	Matrix4f WorldTransformation = Translation * Rotation * Scale;

	return WorldTransforamtion;


}