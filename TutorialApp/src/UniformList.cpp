#include <ShadersProgram.h>
#include <UniformList.h>

void UniformIntegerNode::set_uniform(ShadersProgram *shader) {
  shader->set_uniform(uniform, value);
}

void UniformFloatNode::set_uniform(ShadersProgram *shader) {
  shader->set_uniform(uniform, value);
}

void UniformVector2fNode::set_uniform(ShadersProgram *shader) {
  shader->set_uniform(uniform, value);
}

void UniformVector3fNode::set_uniform(ShadersProgram *shader) {
  shader->set_uniform(uniform, value);
}

void UniformMatrix3fNode::set_uniform(ShadersProgram *shader) {
  shader->set_uniform(uniform, value);
}

void UniformMatrix4fNode::set_uniform(ShadersProgram *shader) {
  shader->set_uniform(uniform, value);
}
