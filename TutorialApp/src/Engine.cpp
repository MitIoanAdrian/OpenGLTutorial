#include <Application.hpp>
#include <AttributeHelper.h>
#include <Engine.h>
#include <HeightMap.h>
#include <IndexBuffer.h>
#include <OGL.h>
#include <RenderPacket.h>
#include <ResourceManager.h>
#include <ShadersProgram.h>
#include <Terrain.h>
#include <Texture.h>
#include <VertexLayout.h>
#include <iostream>
#include <memory>
#include <vector>

/*void Engine::initBuffer() {

  m_VertexBuffer = std::make_shared<VertexBuffer>();
  m_VertexLayout = std::make_shared<VertexLayout>();
  m_IndexBuffer = std::make_shared<IndexBuffer>();

  m_VertexLayout->AddVertexAttribute(AttributeHelper::AttributeType::kPosition,
                                     3);
  m_VertexLayout->AddVertexAttribute(AttributeHelper::AttributeType::kUV, 2);

  float vertex_data[] = {0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
                         0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,  0.5f,
                         -0.5f, -0.5f, 1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0.0f,
                         0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.5f,  -0.5f,
                         0.5f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  1.0f,  1.0f};

  m_VertexBuffer->create(vertex_data, *m_VertexLayout,
                         sizeof(vertex_data) / m_VertexLayout->getSize());
  m_VertexBuffer->bind();

  unsigned int index_data[] = {0, 1, 2, 1, 3, 4, 5, 6, 3, 7, 3, 6,
                               2, 4, 7, 0, 7, 6, 0, 5, 1, 1, 5, 3,
                               5, 0, 6, 7, 4, 3, 2, 1, 4, 0, 2, 7};

  m_IndexBuffer->create(*m_VertexBuffer, index_data, sizeof(index_data));
  m_IndexBuffer->bind();
}

void Engine::initShader() {
  m_Shaders = getResourceManager().createShader("shader");
}

void Engine::initTexture() {
  m_Texture = getResourceManager().getTexture("soil.jpeg");
  m_Texture->load();
  m_Texture->bind(0);
}
 */

void Engine::initTerrain() {
  m_HeightMap = getResourceManager().getHeightMap("heightmap.tga");

  m_Terrain = std::make_shared<Terrain>();
  m_Terrain->initResources(&getResourceManager());
  m_Terrain->loadHeightMap(m_HeightMap);
  m_Terrain->generate();
}

void Engine::initCamera() {
  m_Camera.setProjection(getHeight(), getWidth());
  m_Camera.LookAt(0.0f, 0.0f, 10.0f);
}

void Engine::initModel() { m_Model.setPosition(0.0f, 0.0f, 0.0f); }

bool Engine::initialize(const char *window_name, std::size_t width,
                        std::size_t height) {
  if (!init_window(window_name, width, height))
    return false;

  // initBuffer();
  // initShader();
  initCamera();
  initModel();
  initTerrain();
  // initTexture();

  m_Mouse.x = 0.0f;
  m_Mouse.y = 0.0f;

  return true;
}

void Engine::window_callback(Application *App, int Width, int Height) {
  Engine *handler = reinterpret_cast<Engine *>(App);
  handler->m_Camera.setProjection((float)Height, (float)Width);
}

void Engine::key_callback(Application *App, int key) {
  Engine *handler = reinterpret_cast<Engine *>(App);
  Vector3f new_look_at;
  new_look_at = handler->m_Control.moveCamera(key, m_Camera.getLookAt(),
                                              m_Camera.getYaw());
  m_Camera.LookAt(new_look_at.x, new_look_at.y, new_look_at.z);
}

void Engine::cursor_callback(Application *App, double xpos, double ypos) {
  Engine *handler = reinterpret_cast<Engine *>(App);
  float x = (float)xpos;
  float y = (float)ypos;

  float mouse_deltax = x - m_Mouse.x;
  float mouse_deltay = y - m_Mouse.y;

  const float yaw_diff = mouse_deltax;
  const float pitch_diff = mouse_deltay;

  m_Mouse.x = x;
  m_Mouse.y = y;

  if (yaw_diff != 0)
    m_Camera.onYaw(yaw_diff);

  if (pitch_diff != 0)
    m_Camera.onPitch(pitch_diff);
}

void Engine::update(const float delta_seconds) {}

void Engine::render() {

  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, getWidth() * 2, getHeight() * 2);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // m_Model.Rotate(0.0f, 1.0f, 0.0f);

  // m_Shaders->bind();

  m_Camera.updateCamera();
  auto mvp = m_Camera.getProjectionMatrix() * m_Camera.getViewMatrix() *
             m_Model.GetMatrix();
  auto *wvp = m_RenderQueue.create_uniform(
      nullptr, UniformHelper::UniformType::kMVP, mvp);

  auto packets = m_Terrain->getPackets(&m_RenderQueue, wvp);

  for (auto &packet : packets) {
    m_RenderQueue.push_rendering_packet(packet);
  }

  m_RenderQueue.draw_all();
  m_RenderQueue.clear();
}
