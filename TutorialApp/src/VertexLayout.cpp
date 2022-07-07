#include <OGL.h>
#include <VertexLayout.h>

#include <iostream>

void VertexLayout::AddVertexAttribute(const char *name,
                                      const std::size_t number_of_floats) {

  VertexAttribute vAttr;

  vAttr.name = name;
  vAttr.number_of_floats = number_of_floats;

  m_Size += sizeof(number_of_floats);

  m_VertexAttrib.push_back(vAttr);
}

std::size_t VertexLayout::getSize() const { return m_Size; }

const std::vector<VertexAttribute> &VertexLayout::getAll() const {
  return m_VertexAttrib;
}
