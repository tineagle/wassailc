#pragma once

#include "core.h"
#include "engineutils.h"

vk::Device createDevice(vk::PhysicalDevice physicalDevice);

std::vector<float> getQueuePriority(vk::QueueFamilyProperties family);
std::vector<vk::DeviceQueueCreateInfo> getQueueCreateInfos(vk::PhysicalDevice physicalDevice);

std::vector<std::string> getDeviceLayers();
bool checkDeviceLayers(vk::PhysicalDevice physicalDevice, const std::vector<std::string> &layers);

std::vector<std::string> getDeviceExtensions();
std::vector<vk::ExtensionProperties> enumerateAllDeviceExtensionProperties(vk::PhysicalDevice physicalDevice, const std::vector<std::string> &layers);
bool checkDeviceExtensions(vk::PhysicalDevice physicalDevice, const std::vector<std::string> &extensions, const std::vector<std::string> &layers);