#pragma once

#include "core.h"
#include "engine.h"

typedef bool(*fFamilySuitable)(const vk::QueueFamilyProperties&);
uint32_t getQueueIndex(const std::vector<vk::QueueFamilyProperties> &families, fFamilySuitable pred);
bool isGraphicsFamilySuitable(const vk::QueueFamilyProperties &family);
bool isPresentFamilySuitable(const vk::QueueFamilyProperties &family);

std::vector<vk::DeviceQueueCreateInfo> getQueueCreateInfos(uint32_t graphicsIndex, uint32_t presentIndex, const std::vector<float> &priorities);

std::vector<std::string> getDeviceLayers();
bool checkDeviceLayers(vk::PhysicalDevice physicalDevice, const std::vector<std::string> &layers);

std::vector<std::string> getDeviceExtensions();
std::vector<vk::ExtensionProperties> enumerateAllDeviceExtensionProperties(vk::PhysicalDevice physicalDevice, const std::vector<std::string> &layers);
bool checkDeviceExtensions(vk::PhysicalDevice physicalDevice, const std::vector<std::string> &extensions, const std::vector<std::string> &layers);