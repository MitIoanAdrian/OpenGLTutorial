//
//  VertexBuffer.h
//  TutorialApp
//
//  Created by Adrian Mit - (p) on 06.07.2022.
//

#pragma once

#include <OGL.h>
#include <VertexLayout.h>
#include <iostream>
#include <vector>

// vertex buffer.
class VertexBuffer {
public:
  VertexBuffer();
  ~VertexBuffer();

public:
  void bind();

public:
  void create(const void *data, const VertexLayout &vertex_layout,
              const std::size_t vertex_count);
  //^ this function needs to bind the VAO, bind the buffer, send the data to the
  // gpu and assign offsets with glVertexAttribPointer

private:
  GLuint m_VAO;
  GLuint m_Buff;
};
