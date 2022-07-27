#include <RenderingQueue.h>

#include <IndexBuffer.h>
#include <RenderPacket.h>
#include <UniformList.h>
#include <VertexBuffer.h>
#include <algorithm>
#include <vector>

IUniformNode *RenderingQueue::create_uniform(IUniformNode *prev,
                                             UniformHelper::UniformType type,
                                             int value) {

  auto *n = m_IntUniformPool.alloc();
  n->uniform = type;
  n->value = value;
  n->next = prev;

  return n;
}

IUniformNode *RenderingQueue::create_uniform(IUniformNode *prev,
                                             UniformHelper::UniformType type,
                                             const Matrix4f &value) {

  auto *n = m_Mat4UniformPool.alloc();
  n->uniform = type;
  n->value = value;
  n->next = prev;

  return n;
}

TextureNode *RenderingQueue::create_texture(TextureNode *prev, Texture *value,
                                            UniformHelper::UniformType type) {

  auto *n = m_TexturePool.alloc();
  n->value = value;
  n->target = type;

  if (prev == nullptr)
    n->hash = value->get_hash();
  else
    n->hash = value->get_hash();

  n->next = prev;
  return n;
}

void RenderingQueue::push_rendering_packet(const RenderPacket &packet) {

  m_Packets.push_back(packet);
}

void RenderingQueue::clear() {

  m_Packets.clear();
  m_Mat4UniformPool.clear();
  m_IntUniformPool.clear();
  m_TexturePool.clear();
}

void RenderingQueue::draw_all() {
  std::sort(m_Packets.begin(), m_Packets.end(), RenderPacket::compare);

  VertexBuffer *current_vbo = nullptr;
  IndexBuffer *current_ibo = nullptr;
  ShadersProgram *active_shader = nullptr;
  uint64_t bound_textures_hash = 0;

  for (const auto &packet : m_Packets) {

    if (current_vbo != packet.vbuff) {
      current_vbo = packet.vbuff;
      current_vbo->bind();
    }

    if (packet.first_texture != nullptr &&
        bound_textures_hash != packet.first_texture->hash) {
      bound_textures_hash = packet.first_texture->hash;
      set_textures(packet.first_texture);
    }

    if (active_shader != packet.shader) {
      active_shader = packet.shader;
      active_shader->bind();
    }

    if (packet.first_uniform != nullptr)
      set_uniforms(active_shader, packet.first_uniform, packet.first_texture);

    if (packet.ibuff != nullptr) {
      if (current_ibo != packet.ibuff) {
        current_ibo = packet.ibuff;
        current_ibo->bind();
      }

      draw_ibo(packet.topology, packet.primitive_start, packet.primitive_end);
    }

    else {
      draw_vbo(packet.topology, packet.primitive_start, packet.primitive_end);
    }
  }

  current_vbo->unbind();
}

void RenderingQueue::draw_vbo(GLenum topology, std::size_t primitive_start,
                              std::size_t primitive_end) {
  std::size_t primitive_size = 0;
  switch (topology) {
  case GL_LINES:
    primitive_size = 2;
    break;
  case GL_TRIANGLES:
    primitive_size = 3;
  }
  std::size_t primitive_count = primitive_end - primitive_start;
  std::size_t start = primitive_size * primitive_start;
  std::size_t count = primitive_size * primitive_count;

  glDrawArrays(topology, start, count);
}

void RenderingQueue::draw_ibo(GLenum topology, std::size_t primitive_start,
                              std::size_t primitive_end) {
  std::size_t primitive_size = 0;
  switch (topology) {
  case GL_LINES:
    primitive_size = 2;
    break;
  case GL_TRIANGLES:
    primitive_size = 3;

    std::size_t primitive_count = primitive_end - primitive_start;
    std::size_t start = primitive_size * primitive_start;
    std::size_t count = primitive_size * primitive_count;

    glDrawElements(topology, count, GL_UNSIGNED_INT, (void *)start);
  }
}

void RenderingQueue::set_uniforms(ShadersProgram *active_shader,
                                  IUniformNode *first_uniform,
                                  TextureNode *first_texture) {
  {
    auto node = first_uniform;
    while (node != nullptr) {
      node->set_uniform(active_shader);

      node = node->next;
    }
  }

  {
    auto node = first_texture;
    std::size_t slot = 0;
    while (node != nullptr && slot <= 8) {
      active_shader->set_uniform(node->target, int(node->slot));
      node = node->next;
    }
  }
}

void RenderingQueue::set_textures(TextureNode *texture) {
  auto node = texture;

  uint32_t slot = 0;
  while (node != nullptr && slot <= 8) {
    node->value->bind(slot);
    node->slot = slot;
    slot++;
    node = node->next;
  }
}
