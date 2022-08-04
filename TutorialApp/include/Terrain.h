#pragma once

#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <IndexBuffer.h>
#include <HeightMap.h>
#include <memory>
#include <iostream>
#include <ogldev_math_3d.h>
#include <RenderingQueue.h>
#include <UniformList.h>
#include <ResourceManager.h>
#include <ShadersProgram.h>
#include <Texture.h>

class Terrain{
private:
	std::shared_ptr<VertexLayout> m_vLay;
    std::shared_ptr<VertexBuffer> m_vBuff;
	std::shared_ptr<IndexBuffer> m_iBuff;
	std::shared_ptr<HeightMap> m_hMap;

	std::shared_ptr<Texture> m_Texture;
    std::shared_ptr<ShadersProgram> m_TerrainShader;

	std::size_t m_Width;
	std::size_t m_Height;
	float m_Step = 10.0f;

	void generateTerrain();

	RenderPacket createTerrainPacket(RenderingQueue* render_queue, IUniformNode* uniforms);

	Vector3f getNormal(std::size_t x, std::size_t z);


public:
	Terrain();

	void loadHeightMap(std::shared_ptr<HeightMap> height_map);
	void generate();
	void initResources(ResourceManager* resource_manager);

	float getWidth();
	float getHeight();

	std::vector<RenderPacket> getPackets(RenderingQueue* render_queue, IUniformNode* uniforms);

};
