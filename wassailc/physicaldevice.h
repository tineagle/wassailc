#pragma once

#include "core.h"

VkPhysicalDevice getPhysicalDevice(VkInstance instance);

bool checkPhysicalDevice(VkPhysicalDeviceFeatures features);