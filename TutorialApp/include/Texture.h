#pragma once

#include <OGL.h>
#include <string>

class Texture {
public:
  Texture(GLenum TextureTarget, const std::string &FileName);

  void load();

  void bind(int tslot);

  void GetImageSize(int &ImageWidth, int &ImageHeight) {
    ImageWidth = m_imageWidth;
    ImageHeight = m_imageHeight;
  }

private:
  std::string m_fileName;
  GLenum m_textureTarget;
  GLuint m_textureObj;
  int m_imageWidth = 0;
  int m_imageHeight = 0;
  int m_imageBPP = 0;
};
