#pragma once

#include "core.h"

DEFINE_ARRAY(String, char*)
DEFINE_ARRAY(VkExtProp, VkExtensionProperties)
DEFINE_ARRAY(VkExtPropArray, VkExtPropArray)
DEFINE_ARRAY(VkLayerProp, VkLayerProperties)

bool checkLayer(char* layerName, VkLayerPropArray layers);
bool checkLayers(StringArray layers, VkLayerPropArray availLayers);
bool checkExtension(char* extensionName, VkExtPropArray extensions);
bool checkExtensions(StringArray extensions, VkExtPropArray availExtensions);
VkExtPropArray flattenExtPropArrays(VkExtPropArray defaultExtensions, VkExtPropArrayArray layerExtensions);