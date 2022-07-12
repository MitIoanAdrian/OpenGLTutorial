//
//  Application.cpp
//  TutorialApp
//
//  Created by Adrian Mit - (p) on 05.07.2022.
//

#include "Application.hpp"
#include <OGL.h>
#include <ShadersProgram.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <iostream>
#include <memory>
#include <ogldev_math_3d.h>

Vector2f uOffset(0.0f, 0.0f);

void Application::first_innit() {
  v_Lay = std::make_shared<VertexLayout>();
  v_Buff = std::make_shared<VertexBuffer>();
  s_Prog = std::make_shared<ShadersProgram>();

  v_Lay->AddVertexAttribute(AttributeHelper::kPosition, 2);
  v_Lay->AddVertexAttribute(AttributeHelper::kColor, 3);

  float data[] = {-1.0f, -1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
                  1.0f,  0.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f};

  v_Buff->create(data, *v_Lay, sizeof(data) / v_Lay->getSize());
  v_Buff->bind();
  s_Prog->create();
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
  if (!innit)
    first_innit();
  glClear(GL_COLOR_BUFFER_BIT);
  s_Prog->bind();
  s_Prog->setUniform(uOffset);

  v_Buff->bind();

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_UP) {
    uOffset.y += 0.05f;
  }
  if (key == GLFW_KEY_DOWN) {
    uOffset.y -= 0.05f;
  }
  if (key == GLFW_KEY_LEFT) {
    uOffset.x -= 0.05f;
  }
  if (key == GLFW_KEY_RIGHT) {
    uOffset.x += 0.05f;
  }
  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);
}
