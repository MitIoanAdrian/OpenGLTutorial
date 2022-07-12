#include <AttributeHelper.h>
#include <OGL.h>
#include <VertexLayout.h>
#include <iostream>

void VertexLayout::AddVertexAttribute(const AttributeHelper::AttributeType t,
                                      const std::size_t number_of_floats) {

  VertexAttribute vAttr;

  vAttr.type = AttributeHelper::getAttributeName(t);
  vAttr.number_of_floats = number_of_floats;

  m_Size += number_of_floats * sizeof(float);

  m_VertexAttrib.push_back(vAttr);
}

std::size_t VertexLayout::getSize() const { return m_Size; }

const std::vector<VertexAttribute> &VertexLayout::getAll() const {
  return m_VertexAttrib;
}
