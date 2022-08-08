#pragma once

#include <HeightMap.h>
#include <IndexBuffer.h>
#include <RenderingQueue.h>
#include <ResourceManager.h>
#include <ShadersProgram.h>
#include <Texture.h>
#include <UniformList.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <iostream>
#include <memory>
#include <ogldev_math_3d.h>

class Terrain {
private:
  std::shared_ptr<VertexLayout> m_vLay;
  std::shared_ptr<VertexBuffer> m_vBuff;
  std::shared_ptr<IndexBuffer> m_iBuff;
  std::shared_ptr<HeightMap> m_hMap;

  std::shared_ptr<VertexLayout> m_WaterLayout;
  std::shared_ptr<VertexBuffer> m_WaterVerBuff;
  std::shared_ptr<IndexBuffer> m_WaterIndBuff;

  std::shared_ptr<Texture> m_GrassTex;
  std::shared_ptr<Texture> m_Rock1Tex;
  std::shared_ptr<Texture> m_Rock2Tex;
  std::shared_ptr<Texture> m_SnowTex;

  std::shared_ptr<ShadersProgram> m_TerrainShader;
  std::shared_ptr<ShadersProgram> m_WaterShader;

  std::shared_ptr<Texture> m_SplatMap;

  std::size_t m_Width;
  std::size_t m_Height;
  float m_Step = 10.0f;

  void generateTerrain();
  void generateWater();

  RenderPacket createTerrainPacket(RenderingQueue *render_queue,
                                   IUniformNode *uniforms);
  RenderPacket createWaterPacket(RenderingQueue *render_queue,
                                 IUniformNode *uniforms);

  Vector3f getNormal(std::size_t x, std::size_t z);

public:
  Terrain();

  void loadHeightMap(std::shared_ptr<HeightMap> height_map);
  void generate();
  void initResources(ResourceManager *resource_manager);

  float getWidth();
  float getHeight();

  std::vector<RenderPacket> getPackets(RenderingQueue *render_queue,
                                       IUniformNode *uniforms);
};
