#include <Application.hpp>
#include <ogldev_math_3d.h>

inline Application *glfw_get_base(GLFWwindow *window) {
  return reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
}

void Application::window_size_callback(GLFWwindow *window, int width,
                                       int height) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));

  handler->window_callback(width, height);
}
void Application::window_callback(int w, int h) {
  m_Width = w;
  m_Height = h;
}
void Application::cursor_pos_callback(double x, double y) {
  m_InputState.mouse_moved = true;

  float yratio = (float)getWidth() / getHeight();

  m_InputState.mouse_delta.x = -1.0f * m_InputState.mouse_pos.x + x;
  m_InputState.mouse_delta.y = m_InputState.mouse_pos.y - y;
  m_InputState.mouse_delta.y *= yratio;

  m_InputState.mouse_pos.x = x;
  m_InputState.mouse_pos.y = y;
}
void glfw_cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
  handler->cursor_pos_callback(xpos, ypos);
}
void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action,
                       int mods) {
  Application *handler =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));

  handler->key_callback(key, action);
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
  for (auto &k : m_InputState.keys_pressed)
    k = false;
  m_InputState.reset();

  int vp_width, vp_height;
  glfwGetWindowSize(m_Window, &vp_width, &vp_height);
  glfwMakeContextCurrent(m_Window);
  glfwSetKeyCallback(m_Window, glfw_key_callback);
  glfwSetWindowUserPointer(m_Window, this);
  glfwSetWindowSizeCallback(m_Window, window_size_callback);
  glfwSetCursorPosCallback(m_Window, glfw_cursor_pos_callback);

  return true;
}

ResourceManager &Application::getResourceManager() { return m_ResourceManager; }

int Application::getWidth() const { return m_Width; }

int Application::getHeight() const { return m_Height; }

int Application::on_key(int key) { return key; }

void Application::run() {
  before_run(m_InputState);
  float delta_time = glfwGetTime();
  int key;
  while (!glfwWindowShouldClose(m_Window)) {
    float current_time = glfwGetTime();
    this->update(m_InputState, current_time - delta_time);
    this->render();
    delta_time = current_time;

    m_InputState.reset();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
  }
}

void Application::capture_mouse() {
  glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  if (glfwRawMouseMotionSupported())
    glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void Application::key_callback(int key, int action) {
  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
  if (action == GLFW_PRESS || action == GLFW_REPEAT)
    m_InputState.keys_pressed[key] = true;
  else
    m_InputState.keys_pressed[key] = false;
  ;
}
void InputState::reset() {
  if (mouse_moved == true) {
    mouse_moved = false;
  }

  mouse_delta.x = 0;
  mouse_delta.y = 0;
}
