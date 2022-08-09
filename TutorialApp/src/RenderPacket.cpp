#include <RenderPacket.h>

bool RenderPacket::compare(RenderPacket const &packet1,
                           RenderPacket const &packet2) {

  if (packet1.shader != packet2.shader)
    return *(packet1.shader) < *(packet2.shader);

  if (packet1.priority != packet2.priority)
    return packet1.priority > packet2.priority;

  if (packet1.vbuff != packet2.vbuff)
    return packet1.vbuff < packet2.vbuff;

  return packet1.first_texture < packet2.first_texture;
}

bool operator<(RenderPacket const &packet1, RenderPacket const &packet2) {
  return RenderPacket::compare(packet1, packet2);
}
