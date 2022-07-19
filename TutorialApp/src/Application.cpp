//  Application.cpp
//  TutorialApp
//
//  Created by Adrian Mit - (p) on 05.07.2022.
//

#include "Application.hpp"
#include <ShadersProgram.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <ogldev_math_3d.h>

void Application::first_innit() {

  m_model_transform.setPosition(0.0f, 0.0f, 0.0f);
  v_Lay = std::make_shared<VertexLayout>();
  v_Buff = std::make_shared<VertexBuffer>();
  s_Prog = std::make_shared<ShadersProgram>();

  v_Lay->AddVertexAttribute(AttributeHelper::kPosition, 3);
  v_Lay->AddVertexAttribute(AttributeHelper::kColor, 3);

  float data[] = {
      -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,
      1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
      -0.5f, 1.0f,  0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,
      0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,
      0.5f,  -0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,
      0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  -0.5f, 0.5f,
      0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,
      1.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,
      0.5f,  1.0f,  0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,
      0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
      0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,
      1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
      0.5f,  1.0f,  0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f};

  v_Buff->create(data, *v_Lay, sizeof(data) / v_Lay->getSize());
  v_Buff->bind();
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

// void Application::on_key(int key){
//   m_control.moveCamera(key, m_camera);
//}

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

  v_Buff->bind();

  glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Application::key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));

  //   handler->on_key(key);

  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);
}
