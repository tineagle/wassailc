#pragma once

#include "core.h"

vk::PhysicalDevice getPhysicalDevice(vk::Instance instance);

bool checkPhysicalDevice(const vk::PhysicalDeviceFeatures &features);