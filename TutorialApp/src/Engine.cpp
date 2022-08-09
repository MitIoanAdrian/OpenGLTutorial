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

void Engine::window_callback(int Width, int Height) {
  Application::window_callback(Width, Height); //, <#Height#>)
  this->m_Camera.setProjection((float)Height, (float)Width);
}

void Engine::update(const InputState &input_state, const float delta_seconds) {

  if (input_state.mouse_moved) {
    const float yaw_diff = input_state.mouse_delta.x;
    const float pitch_diff = input_state.mouse_delta.y;

    m_Camera.onYaw(yaw_diff * delta_seconds);

    m_Camera.onPitch(pitch_diff * delta_seconds);
  }

  if (m_InputState.keys_pressed[GLFW_KEY_W]) {
    m_Camera.moveForward(-delta_seconds);
  }
  if (m_InputState.keys_pressed[GLFW_KEY_S]) {
    m_Camera.moveForward(delta_seconds);
  }
  if (m_InputState.keys_pressed[GLFW_KEY_A]) {
    m_Camera.moveSide(delta_seconds);
  }
  if (m_InputState.keys_pressed[GLFW_KEY_D]) {
    m_Camera.moveSide(-delta_seconds);
  }
  if (m_InputState.keys_pressed[GLFW_KEY_Q]) {
    m_Camera.moveUp(delta_seconds);
  }
  if (m_InputState.keys_pressed[GLFW_KEY_E]) {
    m_Camera.moveUp(-delta_seconds);
  }
}

void Engine::render() {

  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, getWidth() * 2, getHeight() * 2);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_Camera.updateCamera();

  m_Terrain->createRenderPackets(m_RenderQueue, m_Camera);

  m_RenderQueue.draw_all();
  m_RenderQueue.clear();
}

void Engine::before_run(InputState &input_state) { capture_mouse(); }
