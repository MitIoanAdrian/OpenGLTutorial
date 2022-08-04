#include <AttributeHelper.h>
#include <iostream>

const char *AttributeHelper::getAttributeName(const AttributeType t) {
  switch (t) {
  case AttributeHelper::AttributeType::kColor:
    return "Color";
    break;
  case AttributeHelper::AttributeType::kPosition:
    return "Position";
    break;
  case AttributeHelper::AttributeType::kUV:
    return "UV";
    break;
  case AttributeHelper::AttributeType::kNormal:
    return "Normal";
    break;
  case AttributeHelper::AttributeType::kAttributeCount:
    return "AttributeCount"; // also used for "invalid" attribute
    break;
  default:
    break;
    return nullptr;
  }
}

AttributeHelper::AttributeType
AttributeHelper::getAttributeType(const char *attribute_name) {
  if (strcmp(attribute_name, "Color") == 0)
    return AttributeHelper::AttributeType::kColor;
  if (strcmp(attribute_name, "Position") == 0)
    return AttributeHelper::AttributeType::kPosition;
  if (strcmp(attribute_name, "UV") == 0)
    return AttributeHelper::AttributeType::kUV;
  if(strcmp(attribute_name, "Normal") == 0)
    return AttributeHelper::AttributeType::kNormal;
  return AttributeHelper::AttributeType::kAttributeCount;
}
