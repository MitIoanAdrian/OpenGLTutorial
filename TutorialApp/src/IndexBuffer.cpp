#include <IndexBuffer.h>
#include <OGL.h>
#include <VertexBuffer.h>
#include <iostream>

IndexBuffer::IndexBuffer() { glGenBuffers(1, &m_IBO); }

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_IBO); }

std::size_t IndexBuffer::getSize() { return m_Size; }

void IndexBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO); }

void IndexBuffer::create(const VertexBuffer &vertex_buffer,
                         const uint32_t *data, const std::size_t size) {
  vertex_buffer.bind();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), data,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  m_Size = size;
}
