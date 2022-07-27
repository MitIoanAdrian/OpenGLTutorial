#pragma once

#include <IndexBuffer.h>
#include <OGL.h>
#include <ShadersProgram.h>
#include <TextureList.h>
#include <UniformList.h>
#include <VertexBuffer.h>
#include <iostream>

struct RenderPacket {
  int priority = 0;

  ShadersProgram *shader;
  VertexBuffer *vbuff;
  IndexBuffer *ibuff;
  GLenum topology;
  std::size_t primitive_start;
  std::size_t primitive_end;
  IUniformNode *first_uniform = nullptr;
  TextureNode *first_texture = nullptr;

  static bool compare(RenderPacket const &, RenderPacket const &);
};
