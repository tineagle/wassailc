#include "device.h"

#include <iostream>
#include <set>

#include "engineutils.h"

void GraphicsEngine::getQueueInfos() {
    auto families = physicalDevice.getQueueFamilyProperties();

    // Select graphics/present queues
    uint32_t graphicsIndex = getQueueIndex(families, isGraphicsFamilySuitable);
    uint32_t presentIndex = getQueueIndex(families, isPresentFamilySuitable);
    std::set<uint32_t> indices{ { graphicsIndex, presentIndex } };

    queueInfos.clear();
    for (const auto &index : indices) {
        std::vector<float> priorities = getQueuePriorities(families[index]);
        queueInfos.push_back(QueueInfo{ index, priorities });
    }
}

void GraphicsEngine::createDevice() {
    auto queueCreateInfos = getQueueCreateInfos(queueInfos);

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

    device = physicalDevice.createDevice(createInfo);
}

std::vector<float> getQueuePriorities(const vk::QueueFamilyProperties &family) {
    return {
        1.0f
    };
}


uint32_t getQueueIndex(const std::vector<vk::QueueFamilyProperties> &families, fFamilySuitable pred) {
    uint32_t currentIndex = 0;
    for (const auto& family : families) {
        // Check for suitability
        if (pred(family)) {
            return currentIndex;
        }
        ++currentIndex;
    }
    return ~0;
}

bool isGraphicsFamilySuitable(const vk::QueueFamilyProperties &family) {
    return true;
}

bool isPresentFamilySuitable(const vk::QueueFamilyProperties &family) {
    return true;
}

std::vector<vk::DeviceQueueCreateInfo> getQueueCreateInfos(const std::vector<QueueInfo> &queueInfos) {
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
    for (const auto &queueInfo : queueInfos) {
        vk::DeviceQueueCreateInfo createInfo{
            vk::DeviceQueueCreateFlags(), queueInfo.index,
            (uint32_t) queueInfo.priorities.size(), queueInfo.priorities.data()
        };
        queueCreateInfos.push_back(createInfo);
    }
    return queueCreateInfos;
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