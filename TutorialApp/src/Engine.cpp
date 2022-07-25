#include <Application.hpp>
#include <AttributeHelper.h>
#include <Engine.h>
#include <OGL.h>
#include <ShadersProgram.h>
#include <Texture.h>
#include <VertexLayout.h>
#include <iostream>
#include <memory>
#include <vector>

void Engine::initBuffer() {

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
  m_Texture = getResourceManager().getTexture("bricks.jpeg", GL_TEXTURE_2D);
  m_Texture->load();
  m_Texture->bind(0);
}

void Engine::initCamera() { m_Camera.setProjection(getHeight(), getWidth()); }

void Engine::initModel() { m_Model.setPosition(0.0f, 0.0f, 0.0f); }

bool Engine::initialize(const char *window_name, std::size_t width,
                        std::size_t height) {
  if (!init_window(window_name, width, height))
    return false;

  initBuffer();
  initShader();
  initCamera();
  initModel();
  initTexture();

  return true;
}

void Engine::window_callback(Application *App, int Width, int Height) {
  Engine *handler = reinterpret_cast<Engine *>(App);
  handler->m_Camera.setProjection((float)Height, (float)Width);
}

void Engine::key_callback(Application *App, int key) {
  Engine *handler = reinterpret_cast<Engine *>(App);
  handler->m_Camera.Move(
      m_Control.moveCamera(key, m_Camera.getPosition(), m_Camera.getTarget()));
}

void Engine::update(const float delta_seconds) {}

void Engine::render() {

  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, getWidth() * 2, getHeight() * 2);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_Model.Rotate(0.0f, 1.0f, 0.0f);

  m_Shaders->bind();

  m_Camera.updateCamera();
  auto mvp = m_Camera.getProjectionMatrix() * m_Camera.getViewMatrix() *
             m_Model.GetMatrix();

  m_Shaders->setUniformMat4(UniformHelper::UniformType::kMVP, mvp);
  m_Shaders->setUniform1i(UniformHelper::UniformType::kTexture, 0);

  m_Texture->bind(0);
  m_VertexBuffer->bind();
  m_IndexBuffer->bind();

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
