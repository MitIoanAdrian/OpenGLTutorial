#include <Texture.h>
#include <iostream>
#include <StbHelper.h>

std::hash<std::string> Texture::m_HashObj;

Texture::Texture(const std::string &FileName) { m_fileName = FileName; }

void Texture::load() {
  //stbi_set_flip_vertically_on_load(1);
  int width = 0, height = 0, bpp = 0;
  unsigned char *image_data =
  StbHelper::stbi_helper_load(m_fileName.c_str(), &width, &height, &bpp, 0);

  glGenTextures(1, &m_textureObj);
  glBindTexture(m_textureTarget, m_textureObj);
  if (m_textureTarget == GL_TEXTURE_2D) {
    glTexImage2D(m_textureTarget, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image_data);
  } else {
    printf("Support for texture target %x is not implemented\n",
           m_textureTarget);
  }

  glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);

  glBindTexture(m_textureTarget, 0);

  m_Hash = m_HashObj(m_fileName);

  StbHelper::stbi_helper_free(image_data);

}

const uint64_t &Texture::get_hash() const { return m_Hash; }

void Texture::bind(int tslot) {
  glActiveTexture(GL_TEXTURE0 + tslot);
  glBindTexture(m_textureTarget, m_textureObj);
}
