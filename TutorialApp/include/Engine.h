#pragma once

#include <Application.hpp>
#include <Camera.h>
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

  RenderingQueue m_RenderQueue;

  std::shared_ptr<HeightMap> m_HeightMap;
  std::shared_ptr<Terrain> m_Terrain;

  Vector2f m_Mouse;

  void initModel();
  void initCamera();
  void initTerrain();

  void cursor_callback(InputState &input_state, const float detla);

  void window_callback(int Width, int Height) override;

  void update(const InputState &input_state, const float delta_time) override;

  void render() override;

public:
  Engine() = default;
  Engine &operator=(const Engine &) = delete;

  bool initialize(const char *window_name, std::size_t width,
                  std::size_t height);

  void before_run(InputState &input_state) override;
};
