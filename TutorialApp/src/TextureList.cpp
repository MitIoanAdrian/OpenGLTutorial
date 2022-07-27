#include <Texture.h>
#include <TextureList.h>

void TextureNode::xor_hash(uint64_t value) { hash ^= value; }

void TextureNode::set_value(Texture *texture) {
  hash ^= texture->get_hash();

  value = texture;
}

void TextureNode::add_texture_node(TextureNode *add_node) {
  auto add_hash = add_node->hash;

  auto node = this;

  while (node->next != nullptr) {
    node->xor_hash(add_hash);
    node = node->next;
  }

  node->next = add_node;
}
