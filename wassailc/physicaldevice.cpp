#include "physicaldevice.h"

void GraphicsEngine::setPhysicalDevice() {
    auto devices = instance.enumeratePhysicalDevices();
    for (const auto &device : devices) {
        auto features = device.getFeatures();
        if (checkPhysicalDevice(features)) {
            physicalDevice = device;
            break;
        }
    }
}

bool checkPhysicalDevice(const vk::PhysicalDeviceFeatures &features) {
    return true;
}