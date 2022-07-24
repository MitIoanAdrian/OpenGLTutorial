#pragma once

#include <OGL.h>
#include <ShadersProgram.h>
#include <Texture.h>
#include <memory>
#include <string>

class ResourceManager {
public:
  ResourceManager();

  std::shared_ptr<ShadersProgram> createShader(const std::string shaderName);

  std::shared_ptr<Texture> getTexture(const std::string textureName,
                                      GLenum type);

private:
  static inline std::string m_Shaders =
      "/Users/adrianm2/Desktop/OpenGLWindow/OpenGLWindow/"
      "TutorialApp/shaders/";

  static inline std::string m_Textures =
      "/Users/adrianm2/Desktop/OpenGLWindow/OpenGLWindow/"
      "TutorialApp/textures/";

  void load_shaders(const std::string shader_file,
                    std::shared_ptr<ShadersProgram> &);

  void load_textures(const std::string texture_file, GLenum target,
                     std::shared_ptr<Texture> &);
};
