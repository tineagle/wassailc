#pragma once

#include "core.h"
#include "engineutils.h"

DEFINE_ARRAY(QueueCreateInfo, VkDeviceQueueCreateInfo)
DEFINE_ARRAY(QueuePriority, float)

VkDevice createDevice(VkPhysicalDevice physicalDevice);

QueuePriorityArray getQueuePriority(VkQueueFamilyProperties family);
VkDeviceQueueCreateInfo getQueueCreateInfo(uint32_t index, VkQueueFamilyProperties *families);
QueueCreateInfoArray getQueueCreateInfos(VkPhysicalDevice physicalDevice);

StringArray getDeviceLayers();
VkResult enumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, VkLayerPropArray* layerArray);
bool checkDeviceLayers(VkPhysicalDevice physicalDevice, StringArray layers);

StringArray getDeviceExtensions();
VkResult enumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, char* layerName, VkExtPropArray *extensionArray);
VkExtPropArray enumerateAllDeviceExtensionProperties(VkPhysicalDevice physicalDevice, StringArray layers);
bool checkDeviceExtensions(VkPhysicalDevice physicalDevice, StringArray extensions, StringArray layers);