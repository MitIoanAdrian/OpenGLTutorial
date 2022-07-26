#pragma once

#include <IndexBuffer.h>
#include <OGL.h>
#include <ResourceManager.h>
#include <ogldev_math_3d.h>

// file: Application.h
class Application {
public:
  Application() = default;
  Application &operator=(const Application &) = delete;

  virtual void run();
  //^ this functions keeps the application alive until user presses escape

private:
  GLFWwindow *m_Window = nullptr;

  int m_Width = 0;
  int m_Height = 0;

  ResourceManager m_ResourceManager;

  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);

  static void window_size_callback(GLFWwindow *window, int with, int height);

protected:
  bool init_window(const char *window_name, std::size_t width,
                   std::size_t height);

  //  void update(const float delta_seconds);

  virtual void render() = 0;

  int getWidth() const;

  int getHeight() const;

  int on_key(int key);

  virtual void key_callback(Application *App, int key) {}

  virtual void window_callback(Application *App, int width, int height) {}

  ResourceManager &getResourceManager();
};
