#pragma once

#include "engine.h"

bool checkDevice(VkPhysicalDevice device);

StringArray getDeviceLayers();
StringArray getDeviceExtensions();

bool checkDevice(VkPhysicalDevice device);
bool checkFeatures(VkPhysicalDevice device);
bool checkDeviceLayers(VkPhysicalDevice device, StringArray layers);
bool checkDeviceExtensions(VkPhysicalDevice device, StringArray extensions, StringArray layers);