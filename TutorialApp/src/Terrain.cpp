#include <Terrain.h>

#include <iostream>
#include <memory>
#include <vector>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <IndexBuffer.h>
#include <AttributeHelper.h>
#include <RenderingQueue.h>
#include <UniformList.h>
#include <ResourceManager.h>

Terrain::Terrain(){
	m_vBuff = std::make_shared<VertexBuffer>();
	m_iBuff = std::make_shared<IndexBuffer>();
	m_vLay = std::make_shared<VertexLayout>();

	m_vLay->AddVertexAttribute(AttributeHelper::AttributeType::kPosition, 3);
	m_vLay->AddVertexAttribute(AttributeHelper::AttributeType::kUV, 2);
	m_vLay->AddVertexAttribute(AttributeHelper::AttributeType::kNormal, 3);
}

void Terrain::initResources(ResourceManager* resource_manager){
	m_Texture = resource_manager->getTexture("soil.jpeg");
	m_TerrainShader = resource_manager->createShader("terrain_shader");
}


void Terrain::generate(){
	generateTerrain();
}

void Terrain::loadHeightMap(std::shared_ptr<HeightMap> height_map){
	m_hMap = height_map;
	m_Width = m_hMap->getWidth();
	m_Height = m_hMap->getHeight();

}

Vector3f Terrain::getNormal(std::size_t x, std::size_t y){
	float hL = m_hMap->getHeight(x - 1, y);
	float hR = m_hMap->getHeight(x + 1, y);
	float hD = m_hMap->getHeight(x, y - 1);
	float hU = m_hMap->getHeight(x, y + 1);

	Vector3f normal;
	normal.x = hL - hR;
	normal.y = hD - hU;
	normal.z = 0.01f;
	normal = normal.Normalize();

	return normal;
}

float Terrain::getWidth(){
	return m_Width * m_Step;
}

float Terrain::getHeight(){
	return m_Height * m_Step;
}

void Terrain::generateTerrain(){
	struct Vertex{
		Vector3f position;
		Vector2f UV;
		Vector3f normal;
	};

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	for(std::size_t y = 0; y < m_Height; y++)
		for(std::size_t x = 0; x < m_Width; x++){
			
			float map_height = m_hMap->getHeight(x, y);

			Vertex v;
			v.position = Vector3f{(float)x, (float)y,  map_height};
			v.UV = Vector2f{ float(x)/m_Width, float(y)/m_Height};
			v.normal = getNormal(x, y);
			vertices.push_back(v);
			
		}

	for(std::size_t y = 0; y < m_Height - 1; y++)
		for(std::size_t x = 0; x < m_Width - 1; x++){

			indices.push_back(y * m_Width + x);
        	indices.push_back(y * m_Width + x + 1);
        	indices.push_back((y + 1) * m_Width + x);
        	indices.push_back(y * m_Width + x + 1);
        	indices.push_back((y + 1) * m_Width + x + 1);
        	indices.push_back((y + 1) * m_Width + x);
		}

	m_vBuff->create(vertices.data(), *m_vLay, vertices.size());
	m_iBuff->create(*m_vBuff, indices.data(), indices.size());
}

RenderPacket Terrain::createTerrainPacket(RenderingQueue* render_queue, IUniformNode* uniforms){
	std::size_t topology_size = 3;

    auto* tex = render_queue->create_texture(nullptr, m_Texture.get(),
                        UniformHelper::UniformType::kTexture);

	RenderPacket packet;
	packet.vbuff = m_vBuff.get();
	packet.ibuff = m_iBuff.get();
	packet.shader = m_TerrainShader.get();
	packet.topology = GL_TRIANGLES;
    packet.primitive_start = 0;
    packet.primitive_end = m_iBuff->getSize()/topology_size;
	packet.first_texture = tex;
	packet.first_uniform = uniforms;

	return packet;
}


std::vector<RenderPacket> Terrain::getPackets(RenderingQueue* render_queue, IUniformNode* uniforms){
	std::vector<RenderPacket> packets;

	auto terrain_packet = createTerrainPacket(render_queue, uniforms);

	packets.push_back(terrain_packet);

	return packets;
}
