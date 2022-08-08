#include <HeightMap.h>

#include <StbHelper.h>
#include <iostream>

HeightMap::HeightMap() {}

bool HeightMap::load(const char *file) {
  int width, height, channels;
  unsigned char *data =
      StbHelper::stbi_helper_load(file, &width, &height, &channels, 3);

  if (!data)
    return false;

  readHeights(data, channels);

  StbHelper::stbi_helper_free(data);

  return true;
}

void HeightMap::readHeights(unsigned char *data, const short bytes_per_pixel) {
  for (std::size_t i = 0; i < m_TxtWidth; i++)
    for (std::size_t j = 0; j < m_TxtHeight; j++) {
      const unsigned char *offset =
          data + (i + m_TxtWidth * j) * bytes_per_pixel;
      unsigned char red = offset[0];

      m_Height[i + m_TxtWidth * j] = red / 255.0f;
    }
}

float HeightMap::getHeight(std::size_t x, std::size_t z) {
  if (x >= m_TxtWidth || z >= m_TxtHeight)
    return 0.0f;

  return m_Height[x + m_TxtWidth * z];
}

const std::size_t HeightMap::getWidth() { return m_TxtWidth; }

const std::size_t HeightMap::getHeight() { return m_TxtHeight; }
