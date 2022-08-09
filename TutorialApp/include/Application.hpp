#pragma once

#include <array>
#include <iostream>

#include <IndexBuffer.h>
#include <OGL.h>
#include <ResourceManager.h>
#include <ogldev_math_3d.h>

struct InputState {
public:
  Vector2f mouse_pos{0.0f, 0.0f};
  Vector2f mouse_delta{0.0f, 0.0f};
  bool mouse_moved = false;

  std::array<bool, 512> keys_pressed;

  void reset();
};

class Application {
public:
  Application() = default;
  Application &operator=(const Application &) = delete;

  virtual void before_run(InputState &input_state) {}

  virtual void run();
  //^ this functions keeps the application alive until user presses escape

public:
  GLFWwindow *m_Window = nullptr;
  InputState m_InputState;

  friend struct InputState;

  int m_Width = 0;
  int m_Height = 0;
  int m_mouseX = 0;
  int m_mouseY = 0;

  ResourceManager m_ResourceManager;

  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);

  static void window_size_callback(GLFWwindow *window, int with, int height);

public:
  void capture_mouse();

  bool init_window(const char *window_name, std::size_t width,
                   std::size_t height);

  virtual void update(const InputState &input_state, float delta_seconds) = 0;

  virtual void render() = 0;

  int getWidth() const;

  int getHeight() const;

  int on_key(int key);

  virtual void cursor_pos_callback(double x, double y);
  virtual void key_callback(int key, int action);
  virtual void window_callback(int width, int height);

  ResourceManager &getResourceManager();
};
