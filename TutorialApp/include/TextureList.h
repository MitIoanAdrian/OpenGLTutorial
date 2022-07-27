#pragma once

#include <Texture.h>
#include <UniformHelper.h>

struct TextureNode {
  TextureNode *next = nullptr;
  Texture *value;
  UniformHelper::UniformType target;

  uint64_t hash = 0;
  uint32_t slot;

  void xor_hash(uint64_t value);
  void set_value(Texture *texture);
  void add_texture_node(TextureNode *node);
};
