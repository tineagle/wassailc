#include "instance.h"

#include <string>
#include <iostream>

#include "engineutils.h"

vk::Instance createInstance() {
    vk::ApplicationInfo appInfo{
        "Test App", VK_MAKE_VERSION(1, 0, 0),
        "Test Engine", VK_MAKE_VERSION(1, 0, 0),
        VK_API_VERSION_1_1
    };

    auto layers = getInstanceLayers();
    checkInstanceLayers(layers);
    auto pLayers = toCStrings(layers);

    auto extensions = getInstanceExtensions();
    checkInstanceExtensions(extensions, layers);
    auto pExtensions = toCStrings(extensions);

    vk::InstanceCreateInfo createInfo{
        vk::InstanceCreateFlags(), &appInfo,
        (uint32_t) pLayers.size(), pLayers.data(),
        (uint32_t) pExtensions.size(), pExtensions.data()
    };

    return vk::createInstance(
        createInfo
    );
}

std::vector<std::string> getInstanceLayers() {
    std::vector<std::string> layers;

    std::vector<std::string> debugLayers = {
        "VK_LAYER_LUNARG_standard_validation",
    };

    layers.insert(layers.end(), debugLayers.begin(), debugLayers.end());
    return layers;
}

bool checkInstanceLayers(const std::vector<std::string> &layerNames) {
    auto availLayers = vk::enumerateInstanceLayerProperties();
    std::cout << "Checking for " << layerNames.size() << " instance layer(s)...\n" << std::flush;
    bool foundLayers = checkLayers(layerNames, availLayers);
    std::cout << (foundLayers ? "FOUND ALL" : "MISSING") << " instance layers.\n\n" << std::flush;
    return foundLayers;
}

std::vector<std::string> getInstanceExtensions() {
    auto debugExtensions = {
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
    };

    uint32_t glfwExtensionCount = 0;
    const char** pGlfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    //std::vector<std::string> glfwExtensions(pGlfwExtensions, pGlfwExtensions + glfwExtensionCount);

    std::vector<std::string> totalExtensions;
    totalExtensions.insert(totalExtensions.end(), debugExtensions.begin(), debugExtensions.end());
    totalExtensions.insert(totalExtensions.end(), pGlfwExtensions, pGlfwExtensions + glfwExtensionCount);
    return totalExtensions;
}

std::vector<vk::ExtensionProperties> enumerateAllInstanceExtensionProperties(const std::vector<std::string> &layers) {
    // Get default extensions associated with NULL
    auto totalExtensions = vk::enumerateInstanceExtensionProperties();


    // Get extensions associated with each layer
    for (const auto &layer : layers) {
        // TODO: Add layer to enumerations (pass in dispatch)
        auto layerExtensions = vk::enumerateInstanceExtensionProperties();
        totalExtensions.insert(totalExtensions.end(), layerExtensions.begin(), layerExtensions.end());
    }
    return totalExtensions;
}

bool checkInstanceExtensions(const std::vector<std::string> &extensions, const std::vector<std::string> &layers) {
    std::vector<vk::ExtensionProperties> availExtensions = enumerateAllInstanceExtensionProperties(layers);

    std::cout << "Checking for " << extensions.size() << " instance extensions(s)...\n" << std::flush;
    bool foundAll = checkExtensions(extensions, availExtensions);
    std::cout << (foundAll ? "FOUND ALL" : "MISSING") << " instance extensions.\n\n" << std::flush;
    return foundAll;
}