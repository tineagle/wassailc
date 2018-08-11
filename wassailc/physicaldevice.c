#include "physicaldevice.h"

VkPhysicalDevice getPhysicalDevice(VkInstance instance) {
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

    VkPhysicalDevice *devices = malloc(sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);

    for (uint32_t i = 0; i < deviceCount; ++i) {
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceFeatures(devices[i], &features);

        if (checkPhysicalDevice(features)) {
            physicalDevice = devices[i];
            break;
        }
    }

    return physicalDevice;
}

bool checkPhysicalDevice(VkPhysicalDeviceFeatures features) {
    return true;
}