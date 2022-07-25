//  Application.cpp
//  TutorialApp
//
//  Created by Adrian Mit - (p) on 05.07.2022.
//

#include <Application.hpp>
#include <ShadersProgram.h>
#include <Texture.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <ogldev_math_3d.h>

void Application::window_size_callback(GLFWwindow *window, int width,
                                       int height) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
  handler->m_Width = width;
  handler->m_Height = height;
  handler->window_callback(handler, width, height);
}

bool Application::init_window(const char *window_name, std::size_t width,
                              std::size_t height) {

  if (!glfwInit())
    return -1;

  m_Width = width;
  m_Height = height;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  m_Window = glfwCreateWindow(width, height, window_name, NULL, NULL);

  if (!m_Window) {
    glfwTerminate();
    return -1;
  }

  int vp_width, vp_height;
  glfwGetWindowSize(m_Window, &vp_width, &vp_height);
  glfwMakeContextCurrent(m_Window);
  glfwSetKeyCallback(m_Window, Application::key_callback);
  glfwSetWindowUserPointer(m_Window, this);
  glfwSetWindowSizeCallback(m_Window, window_size_callback);

  return true;
}

ResourceManager &Application::getResourceManager() { return m_ResourceManager; }

int Application::getWidth() const { return m_Width; }

int Application::getHeight() const { return m_Height; }

int Application::on_key(int key) { return key; }

void Application::run() {
  float delta_time = glfwGetTime();
  int key;
  while (!glfwWindowShouldClose(m_Window)) {
    float current_time = glfwGetTime();
    // this->update(current_time - delta_time);
    this->render();
    //  delta_time = current_time;
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
  }
}

void Application::key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(handler->m_Window, GLFW_TRUE);

  handler->key_callback(handler, key);
}
