#include "device.h"

#include <iostream>

vk::Device createDevice(vk::PhysicalDevice physicalDevice) {
    vk::Device device;

    auto queueCreateInfos = getQueueCreateInfos(physicalDevice);

    auto layers = getDeviceLayers();
    checkDeviceLayers(physicalDevice, layers);
    auto pLayers = toCStrings(layers);

    auto extensions = getDeviceExtensions();
    checkDeviceExtensions(physicalDevice, extensions, layers);
    auto pExtensions = toCStrings(extensions);

    vk::DeviceCreateInfo createInfo{
        vk::DeviceCreateFlags(),
        (uint32_t) queueCreateInfos.size(), queueCreateInfos.data(),
        (uint32_t) pLayers.size(), pLayers.data(),
        (uint32_t) pExtensions.size(), pExtensions.data()
    };

    return physicalDevice.createDevice(createInfo);
}

std::vector<float> getQueuePriority(vk::QueueFamilyProperties family) {
    return {
        1.0f
    };
}

typedef bool (*fFamilySuitable)(const vk::QueueFamilyProperties&);

uint32_t getQueueIndex(const std::vector<vk::QueueFamilyProperties> &families, fFamilySuitable pred) {
    uint32_t graphicsIndex = ~0;

    uint32_t currentIndex = 0;
    for (const auto& family : families) {
        // Check for suitability
        if (pred(family)) {
            graphicsIndex = currentIndex;
        }
        ++currentIndex;
    }
    return graphicsIndex;
}

bool isGraphicsFamilySuitable(const vk::QueueFamilyProperties &family) {
    return true;
}

bool isPresentFamilySuitable(const vk::QueueFamilyProperties &family) {
    return true;
}

std::vector<vk::DeviceQueueCreateInfo> getQueueCreateInfos(vk::PhysicalDevice physicalDevice) {
    auto families = physicalDevice.getQueueFamilyProperties();
    // Select graphics/present queues
    uint32_t graphicsQueueFamilyIndex = getQueueIndex(families, isGraphicsFamilySuitable);
    uint32_t presentQueueFamilyIndex = getQueueIndex(families, isPresentFamilySuitable);

    return {};
}

std::vector<std::string> getDeviceLayers() {
    return {};
}

bool checkDeviceLayers(vk::PhysicalDevice physicalDevice, const std::vector<std::string> &layers) {
    auto availLayers = physicalDevice.enumerateDeviceLayerProperties();

    std::cout << "Checking for " << layers.size() << " device layers(s)...\n" << std::flush;
    bool foundLayers = checkLayers(layers, availLayers);
    std::cout << (foundLayers ? "FOUND ALL" : "MISSING") << " device layer(s)\n\n" << std::flush;
    return foundLayers;
}

std::vector<std::string> getDeviceExtensions() {
    return {};
}

std::vector<vk::ExtensionProperties> enumerateAllDeviceExtensionProperties(vk::PhysicalDevice physicalDevice, const std::vector<std::string> &layers) {
    // Get default extensions associated with NULL
    auto totalExtensions = physicalDevice.enumerateDeviceExtensionProperties(nullptr);

    // Add extensions associated with each layer
    for (const auto &layer : layers) {
        auto layerExtensions = physicalDevice.enumerateDeviceExtensionProperties(layer);
        totalExtensions.insert(totalExtensions.end(), layerExtensions.begin(), layerExtensions.end());
    }
    return totalExtensions;
}

bool checkDeviceExtensions(vk::PhysicalDevice physicalDevice, const std::vector<std::string> &extensions, const std::vector<std::string> &layers) {
    auto availExtensions = enumerateAllDeviceExtensionProperties(physicalDevice, layers);

    std::cout << "Checking for " << extensions.size() << " device extension(s)...\n" << std::flush;
    bool foundAll = checkExtensions(extensions, availExtensions);
    std::cout << (foundAll ? "FOUND ALL" : "MISSING") << " device extensions.\n\n" << std::flush;
    return foundAll;
}