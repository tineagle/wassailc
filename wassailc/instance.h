#pragma once

#include "core.h"
#include "engineutils.h"

VkInstance createInstance();

StringArray getInstanceLayers();
VkResult enumerateInstanceLayerProperties(VkLayerPropArray* layerArray);
bool checkInstanceLayers(StringArray layerNames);


StringArray getInstanceExtensions();
VkResult enumerateInstanceExtensionProperties(const char* layerName, VkExtPropArray* extensionArray);
VkExtPropArray enumerateAllInstanceExtensionProperties(StringArray layers);
bool checkInstanceExtensions(StringArray extensions, StringArray layers);