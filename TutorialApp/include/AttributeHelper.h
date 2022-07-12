#pragma once
#include <OGL.h>

struct AttributeHelper {
  enum AttributeType { kPosition = 0, kColor, kAttributeCount };

  static const char *getAttributeName(const AttributeType t);
  static AttributeType getAttributeType(const char *attribute_name);
};
