#pragma once

#include <Application.hpp>
#include <Camera.h>
#include <CameraController.h>
#include <HeightMap.h>
#include <ModelTrans.h>
#include <OGL.h>
#include <RenderingQueue.h>
#include <ResourceManager.h>
#include <ShadersProgram.h>
#include <Terrain.h>
#include <Texture.h>
#include <VertexBuffer.h>
#include <VertexLayout.h>
#include <iostream>
#include <memory>
#include <ogldev_math_3d.h>

class Engine : public Application {

private:
  Camera m_Camera;
  ModelTrans m_Model;
  CameraController m_Control;

  RenderingQueue m_RenderQueue;

  // std::shared_ptr<VertexBuffer> m_VertexBuffer;
  // std::shared_ptr<VertexLayout> m_VertexLayout;
  // std::shared_ptr<IndexBuffer> m_IndexBuffer;
  std::shared_ptr<HeightMap> m_HeightMap;
  std::shared_ptr<Terrain> m_Terrain;

  Vector2f m_Mouse;

  // std::shared_ptr<ShadersProgram> m_Shaders;
  // std::shared_ptr<Texture> m_Texture;

  /*void initBuffer();
  void initShader();
  void initTexture();*/
  void initModel();
  void initCamera();
  void initTerrain();

  void cursor_callback(Application *App, double xpos, double ypos);

  // void key_callback(Application *App, int key);

  void window_callback(Application *App, int Width, int Height);

  void key_callback(Application *App, int key);

  void update(const float delta_time);

  void render();

public:
  Engine() = default;
  Engine &operator=(const Engine &) = delete;

  bool initialize(const char *window_name, std::size_t width,
                  std::size_t height);
};
