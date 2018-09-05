#pragma once

#include "core.h"

VkInstance createInstance();
VkPhysicalDevice getPhysicalDevice(VkInstance instance);

StringArray getInstanceLayers();
StringArray getInstanceExtensions();

StringArray getDeviceLayers();
StringArray getDeviceExtensions();