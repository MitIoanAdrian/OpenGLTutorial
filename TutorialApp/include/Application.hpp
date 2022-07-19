//
//  Application.hpp
//  TutorialApp
//
//  Created by Adrian Mit - (p) on 05.07.2022.
//

#pragma once

#include <Camera.h>
#include <ModelTrans.h>
#include <ShadersProgram.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <ogldev_math_3d.h>
#include <CameraController.h>

// file: Application.h
class Application {
public:
  Application() = default;
  Application &operator=(const Application &) = delete;

public:
  void first_innit();

  bool initialize(const char *window_name, std::size_t width,
                  std::size_t height);

  void update(const float delta_seconds);
  //^ called from run() function. delta seconds is the ammount of time (in
  // seconds) that passed since the last update() call. First call has 0 as
  // argument.

  void render();
  //^ called from run() function.

public:
  void run();
  //^ this functions keeps the application alive until user presses escape

  static char set_uniform(char);

private:
  void on_resize(int width, int height);
    void on_key(int key);

private:
  // add members here:
  GLFWwindow *m_Window = nullptr; // m_ -> memeber

  std::shared_ptr<VertexBuffer> v_Buff;

  std::shared_ptr<VertexLayout> v_Lay;

  std::shared_ptr<ShadersProgram> s_Prog;

  ModelTrans m_model_transform;

  Camera m_camera;
    
    CameraController m_control;


  bool innit = 0;

  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);
  //static void key_callback2(GLFWwindow *, int, int, int, int);
  static void window_size_callback(GLFWwindow *window, int width, int height);
};
