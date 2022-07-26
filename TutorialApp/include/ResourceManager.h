#pragma once

#include <OGL.h>
#include <ShadersProgram.h>
#include <Texture.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class ResourceManager {
public:
  ResourceManager();

  std::shared_ptr<ShadersProgram> createShader(const std::string shaderName);

  std::shared_ptr<Texture> getTexture(const std::string textureName);

private:
  static inline std::string m_Shaders =
      "/Users/adrianm2/Desktop/OpenGLWindow/OpenGLWindow/"
      "TutorialApp/shaders/";

  static inline std::string m_Textures =
      "/Users/adrianm2/Desktop/OpenGLWindow/OpenGLWindow/"
      "TutorialApp/textures/";

  void load_shaders(const std::string shader_file,
                    std::shared_ptr<ShadersProgram> &);

  void load_textures(const std::string texture_file,
                     std::shared_ptr<Texture> &);

  std::unordered_map<std::string, std::shared_ptr<Texture>> m_TexMap;
  std::unordered_map<std::string, std::shared_ptr<ShadersProgram>> m_ShaderMap;
};
