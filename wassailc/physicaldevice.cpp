#include "physicaldevice.h"

vk::PhysicalDevice getPhysicalDevice(vk::Instance instance) {
    vk::PhysicalDevice physicalDevice;

    auto devices = instance.enumeratePhysicalDevices();
    for (const auto &device : devices) {
        auto features = device.getFeatures();
        if (checkPhysicalDevice(features)) {
            physicalDevice = device;
            break;
        }
    }
    return physicalDevice;
}

bool checkPhysicalDevice(const vk::PhysicalDeviceFeatures &features) {
    return true;
}