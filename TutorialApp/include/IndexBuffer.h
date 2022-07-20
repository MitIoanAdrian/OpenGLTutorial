#pragma once

#include <OGL.h>
#include <VertexBuffer.h>

class IndexBuffer {
public:
  IndexBuffer();
  ~IndexBuffer();

  std::size_t getSize();
  void bind();
  void create(const VertexBuffer &vertex_buffer, const uint32_t *data,
              const std::size_t size);

private:
  GLuint m_IBO;
  std::size_t m_Size = 0;
};
