#include <HeightMap.h>
#include <OGL.h>
#include <ResourceManager.h>
#include <ShadersProgram.h>
#include <Texture.h>
#include <memory>
#include <unordered_map>
#include <vector>

// make strings references

ResourceManager::ResourceManager() {}

void ResourceManager::load_shaders(const std::string name,
                                   std::shared_ptr<ShadersProgram> &s) {
  auto path = m_Shaders + name;
  auto v_path = path + ".vs";
  auto f_path = path + ".fs";

  auto shader = std::make_shared<ShadersProgram>();

  shader->create(v_path.c_str(), f_path.c_str());

  s = shader;
}

void ResourceManager::load_textures(const std::string name,
                                    std::shared_ptr<Texture> &t) {
  auto path = m_Textures + name;

  auto texture = std::make_shared<Texture>(path.c_str());

  texture->load();

  t = texture;
}

void ResourceManager::load_heightmap(const std::string name,
                                     std::shared_ptr<HeightMap> &h) {
  auto path = m_HeightMapPath + name;

  auto hmap = std::make_shared<HeightMap>();

  hmap->load(path.c_str());

  h = hmap;
}

std::shared_ptr<ShadersProgram>
ResourceManager::createShader(const std::string shader_name) {

  if (m_ShaderMap.count(shader_name))
    return m_ShaderMap[shader_name];

  std::shared_ptr<ShadersProgram> s;

  load_shaders(shader_name, s);

  m_ShaderMap.insert(std::make_pair(shader_name, s));
  return s;
}

std::shared_ptr<Texture>
ResourceManager::getTexture(const std::string texture_name) {

  if (m_TexMap.count(texture_name))
    return m_TexMap[texture_name];

  std::shared_ptr<Texture> t;

  load_textures(texture_name, t);

  m_TexMap.insert(std::make_pair(texture_name, t));
  return t;
}

std::shared_ptr<HeightMap>
ResourceManager::getHeightMap(const std::string heightmap_file) {
  if (m_HeightMap.count(heightmap_file))
    return m_HeightMap[heightmap_file];

  std::shared_ptr<HeightMap> h;
  load_heightmap(heightmap_file, h);

  m_HeightMap.insert(std::make_pair(heightmap_file, h));

  return h;
}
