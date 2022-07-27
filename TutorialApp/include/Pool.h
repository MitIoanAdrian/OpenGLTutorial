#pragma once

#include <TextureList.h>
#include <UniformList.h>
#include <iostream>
#include <vector>

template <typename T> class Pool {
private:
  std::vector<T> m_Buffer;
  std::size_t m_Index = 0;

public:
  Pool(std::size_t initial_size = 10000) { m_Buffer.resize(initial_size); }

  void clear() { m_Index = 0; }

  T *alloc() {
    if (m_Index == m_Buffer.size())
      return nullptr;

    return &(m_Buffer[m_Index++]);
  }
};