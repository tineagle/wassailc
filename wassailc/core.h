#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "array.h"

DEFINE_ARRAY(BoolArray, bool)
DEFINE_ARRAY(StringArray, const char*)
DEFINE_ARRAY(LayerArray, VkLayerProperties)
DEFINE_ARRAY(ExtensionArray, VkExtensionProperties)
DEFINE_ARRAY(PhysicalDeviceArray, VkPhysicalDevice)