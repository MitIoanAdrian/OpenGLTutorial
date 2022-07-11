//
//  Application.cpp
//  TutorialApp
//
//  Created by Adrian Mit - (p) on 05.07.2022.
//

#include "Application.hpp"
#include <OGL.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <iostream>
#include <memory>
#include <shader.h>

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

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  v_Lay = std::make_shared<VertexLayout>();
  v_Buff = std::make_shared<VertexBuffer>();

  v_Lay->AddVertexAttribute("Position", 2);
  v_Lay->AddVertexAttribute("Colour", 3);

  float data[] = {-1.0f, -1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
                  0.0f,  0.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f};

  v_Buff->create(data, *v_Lay, sizeof(data) / v_Lay->getSize());
  v_Buff->bind();
  CompileShaders();

  return true;
}

void Application::run() {
  float delta_time = glfwGetTime();

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

  glClear(GL_COLOR_BUFFER_BIT);

  v_Buff->bind();

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);
}
