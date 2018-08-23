#include "engineutils.h"

#include <iostream>

std::vector<const char*> toCStrings(const std::vector<std::string> &strings) {
    std::vector<const char*> cStrings;
    for (const auto &string : strings) {
        cStrings.push_back(string.c_str());
    }
    return cStrings;
}

bool checkLayer(const std::string &layerName, const std::vector<vk::LayerProperties> &layers) {
    bool foundLayer = false;
    for (const auto &layer : layers) {
        foundLayer |= layerName == layer.layerName;
    }
    return foundLayer;
}

bool checkLayers(const std::vector<std::string> &layers, const std::vector<vk::LayerProperties> &availLayers) {
    bool foundAll = true;
    for (const auto &layer : layers) {
        std::cout << '\t' << layer << "... ";
        bool foundLayer = checkLayer(layer, availLayers);
        std::cout << (foundLayer ? "FOUND" : "MISSING") << std::endl;
        foundAll &= foundLayer;
    }
    return foundAll;
}

bool checkExtension(const std::string &extensionName, const std::vector<vk::ExtensionProperties> &extensions) {
    bool foundExtension = false;
    for (const auto &extension : extensions) {
        foundExtension |= extensionName == extension.extensionName;
    }
    return foundExtension;
}

bool checkExtensions(const std::vector<std::string> &extensions, const std::vector<vk::ExtensionProperties> &availExtensions) {
    bool foundAll = true;
    for (const auto &extension : extensions) {
        std::cout << '\t' << extension << "... ";
        bool foundExtension = checkExtension(extension, availExtensions);
        std::cout << (foundExtension ? "FOUND" : "MISSING") << std::endl;
        foundAll &= foundExtension;
    }
    return foundAll;
}

std::vector<vk::ExtensionProperties> flattenExtPropArrays(const std::vector<vk::ExtensionProperties> &defaultExtensions, const std::vector<std::vector<vk::ExtensionProperties>> &totalLayerExtensions) {
    std::vector<vk::ExtensionProperties> totalExtensions;
    totalExtensions.insert(totalExtensions.end(), defaultExtensions.begin(), defaultExtensions.end());
    for (const auto& layerExtensions : totalLayerExtensions) {
        totalExtensions.insert(totalExtensions.end(), layerExtensions.begin(), layerExtensions.end());
    }
    return totalExtensions;
}