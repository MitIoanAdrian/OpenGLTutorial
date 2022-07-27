#include <AttributeHelper.h>
#include <OGL.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>

VertexBuffer::VertexBuffer() {

  glGenVertexArrays(1, &m_VAO);

  glGenBuffers(1, &m_Buff);
}

void VertexBuffer::bind() const {

  glBindVertexArray(m_VAO);

  // glBindBuffer(GL_ARRAY_BUFFER, m_Buff);
}

void VertexBuffer::create(const void *data, const VertexLayout &vertex_layout,
                          const std::size_t vertex_count) {

  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_Buff);

  glBufferData(GL_ARRAY_BUFFER, vertex_layout.getSize() * vertex_count,
               (void *)data, GL_STATIC_DRAW);

  std::size_t offset = 0;

  for (VertexAttribute v : vertex_layout.getAll()) {

    glEnableVertexAttribArray(AttributeHelper::getAttributeType(v.type));

    glVertexAttribPointer(AttributeHelper::getAttributeType(v.type),
                          v.number_of_floats, GL_FLOAT, GL_FALSE,
                          vertex_layout.getSize(), (void *)offset);

    offset += v.number_of_floats * sizeof(float);
  }

  glBindVertexArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  for (VertexAttribute v : vertex_layout.getAll())
    glDisableVertexAttribArray(AttributeHelper::getAttributeType(v.type));
}

void VertexBuffer::unbind() const { glBindVertexArray(0); }

VertexBuffer::~VertexBuffer() {

  glDeleteVertexArrays(1, &m_VAO);

  glDeleteBuffers(1, &m_Buff);
}
