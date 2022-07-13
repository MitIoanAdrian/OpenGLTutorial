// vertex layout.

#pragma once

#include <AttributeHelper.h>
#include <iostream>
#include <vector>

struct VertexAttribute {

  const char *type;

  std::size_t number_of_floats;

  // std::size_t offset;
};

class VertexLayout {
  // this class describes the attributes you have in the data:
public:
  std::size_t getSize() const;
  //^ returns the size in bytes of a single vertex

  void AddVertexAttribute(const AttributeHelper::AttributeType t,
                          const std::size_t number_of_floats);

  const std::vector<VertexAttribute> &getAll() const;

private:
  std::vector<VertexAttribute> m_VertexAttrib;
  std::size_t m_Size = 0;
};
