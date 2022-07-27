#pragma once

#include <Pool.h>
#include <RenderPacket.h>
#include <UniformHelper.h>
#include <UniformList.h>
#include <memory>
#include <vector>

class RenderingQueue {
private:
  std::vector<RenderPacket> m_Packets;

  Pool<UniformMatrix4fNode> m_Mat4UniformPool;
  Pool<UniformIntegerNode> m_IntUniformPool;

  Pool<TextureNode> m_TexturePool;

  static void set_uniforms(ShadersProgram *shader, IUniformNode *first_uniform,
                           TextureNode *first_texture);
  static void set_textures(TextureNode *texture);

  static void draw_vbo(GLenum topology, std::size_t primitive_start,
                       std::size_t primitive_end);
  static void draw_ibo(GLenum topology, std::size_t primitive_start,
                       std::size_t primitive_end);

public:
  RenderingQueue() = default;

  IUniformNode *create_uniform(IUniformNode *prev,
                               UniformHelper::UniformType type, int value);
  IUniformNode *create_uniform(IUniformNode *prev,
                               UniformHelper::UniformType type,
                               const Matrix4f &value);

  TextureNode *create_texture(TextureNode *prv, Texture *value,
                              UniformHelper::UniformType type);

  void push_rendering_packet(const RenderPacket &p);

  void draw_all();
  void clear();
};
