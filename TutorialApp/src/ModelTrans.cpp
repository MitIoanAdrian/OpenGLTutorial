#include <ModelTrans.h>
#include <ogldev_math_3d.h>

void ModelTrans::setScale(float scale) { m_scale = scale; }

void ModelTrans::setRotation(float x, float y, float z) {

  m_rotation.x = x;
  m_rotation.y = y;
  m_rotation.z = z;
}

void ModelTrans::setPosition(float x, float y, float z) {

  m_pos.x = x;
  m_pos.y = y;
  m_pos.z = z;
}

void ModelTrans::Rotate(float x, float y, float z) {

  m_rotation.x += x;
  m_rotation.y += y;
  m_rotation.z += z;
}

Matrix4f ModelTrans::GetMatrix() const {

  Matrix4f Scale;
  Scale.InitScaleTransform(m_scale, m_scale, m_scale);

  Matrix4f Rotation;
  Rotation.InitRotateTransform(m_rotation.x, m_rotation.y, m_rotation.z);

  Matrix4f Translation;
  Translation.InitTranslationTransform(m_pos.x, m_pos.y, m_pos.z);

  Matrix4f ModelTransformation = Translation * Rotation * Scale;

  return ModelTransformation;
}
