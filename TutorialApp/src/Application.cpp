//  Application.cpp
//  TutorialApp
//
//  Created by Adrian Mit - (p) on 05.07.2022.
//

#include "Application.hpp"
#include <ShadersProgram.h>
#include <Texture.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <ogldev_math_3d.h>

void Application::first_innit() {

  const char *txtr = "/Users/adrianm2/Desktop/OpenGLWindow/OpenGLWindow/"
                     "TutorialApp/textures/bricks.jpeg";

  m_model_transform.setPosition(0.0f, 0.0f, 0.0f);
  v_Lay = std::make_shared<VertexLayout>();
  v_Buff = std::make_shared<VertexBuffer>();
  s_Prog = std::make_shared<ShadersProgram>();
  i_Buff = std::make_shared<IndexBuffer>();
  m_Texture = std::make_shared<Texture>(GL_TEXTURE_2D, txtr);

  v_Lay->AddVertexAttribute(AttributeHelper::kPosition, 3);
  v_Lay->AddVertexAttribute(AttributeHelper::kUV, 2);

  float vertex_data[] = {0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
                         0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,  0.5f,
                         -0.5f, -0.5f, 1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0.0f,
                         0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.5f,  -0.5f,
                         0.5f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  1.0f,  1.0f};

  v_Buff->create(vertex_data, *v_Lay, sizeof(vertex_data) / v_Lay->getSize());
  v_Buff->bind();

  unsigned int index_data[] = {0, 1, 2, 1, 3, 4, 5, 6, 3, 7, 3, 6,
                               2, 4, 7, 0, 7, 6, 0, 5, 1, 1, 5, 3,
                               5, 0, 6, 7, 4, 3, 2, 1, 4, 0, 2, 7};

  i_Buff->create(*v_Buff, index_data, sizeof(index_data));
  i_Buff->bind();

  m_Texture->load();
  m_Texture->bind(0);

  const char *vs = "/Users/adrianm2/Desktop/OpenGLWindow/OpenGLWindow/"
                   "TutorialApp/shaders/shader.vs";
  const char *fs = "/Users/adrianm2/Desktop/OpenGLWindow/OpenGLWindow/"
                   "TutorialApp/shaders/shader.fs";
  s_Prog->create(vs, fs);
}

void Application::on_resize(int width, int height) {
  float fwidth = (float)width;
  float fheight = (float)height;
  m_camera.setProjection(fwidth, fheight);
}

void Application::window_size_callback(GLFWwindow *window, int width,
                                       int height) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));

  handler->on_resize(width, height);
}

void Application::on_key(int key) {
  m_camera.Move(
      m_control.moveCamera(key, m_camera.getPosition(), m_camera.getTarget()));
}

bool Application::initialize(const char *window_name, std::size_t width,
                             std::size_t height) {

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  m_Window = glfwCreateWindow(width, height, window_name, NULL, NULL);

  if (!m_Window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(m_Window);
  glfwSetKeyCallback(m_Window, Application::key_callback);
  glfwSetWindowUserPointer(m_Window, this);

  glfwSetWindowSizeCallback(m_Window, window_size_callback);

  on_resize(width, height);

  return true;
}

void Application::run() {
  float delta_time = glfwGetTime();
  int key;
  while (!glfwWindowShouldClose(m_Window)) {
    float current_time = glfwGetTime();
    this->update(current_time - delta_time);
    this->render();
    delta_time = current_time;
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
  }
}

void Application::update(const float delta_seconds) {}

void Application::render() {

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  if (!innit) {
    first_innit();
    innit = 1;
  }
  glClear(GL_COLOR_BUFFER_BIT);
  m_model_transform.Rotate(0.0f, 1.0f, 0.0f);
  s_Prog->bind();
  auto mvp = m_camera.getProjectionMatrix() * m_camera.getViewMatrix() *
             m_model_transform.GetMatrix();

  s_Prog->setUniformMat4(UniformHelper::UniformType::kMVP, mvp);
  s_Prog->setUniform1i(UniformHelper::UniformType::kTexture, 0);

  m_Texture->bind(0);
  v_Buff->bind();
  i_Buff->bind();

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Application::key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));

  handler->on_key(key);

  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);
}
