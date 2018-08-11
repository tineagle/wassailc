#include "engineutils.h"

#include <string.h>
#include <stdio.h>

bool checkLayer(char* layerName, VkLayerPropArray layers) {
    bool foundLayer = false;
    for (uint32_t i = 0; i < layers.count; ++i) {
        foundLayer |= strcmp(layerName, layers.data[i].layerName) == 0;
    }
    return foundLayer;
}

bool checkLayers(StringArray layers, VkLayerPropArray availLayers) {
    bool foundAll = true;
    for (uint32_t i = 0; i < layers.count; ++i) {
        printf("\t""%s... ", layers.data[i]);
        bool foundLayer = checkLayer(layers.data[i], availLayers);
        printf("%s\n", foundLayer ? "FOUND" : "MISSING");
        foundAll &= foundLayer;
    }
    return foundAll;
}

bool checkExtension(char* extensionName, VkExtPropArray extensions) {
    bool foundLayer = false;
    for (uint32_t i = 0; i < extensions.count; ++i) {
        foundLayer |= strcmp(extensionName, extensions.data[i].extensionName) == 0;
    }
    return foundLayer;
}

bool checkExtensions(StringArray extensions, VkExtPropArray availExtensions) {
    bool foundAll = true;
    for (uint32_t i = 0; i < extensions.count; ++i) {
        printf("\t""%s... ", extensions.data[i]);
        bool foundExtension = checkExtension(extensions.data[i], availExtensions);
        printf("%s\n", foundExtension ? "FOUND" : "MISSING");
        foundAll &= foundExtension;
    }
    return foundAll;
}

VkExtPropArray flattenExtPropArrays(VkExtPropArray defaultExtensions, VkExtPropArrayArray layerExtensions) {
    // Calculate extension total
    uint32_t totalExtensions = defaultExtensions.count;
    for (uint32_t i = 0; i < layerExtensions.count; ++i) {
        totalExtensions += layerExtensions.data[i].count;
    }

    // Flatten arrays
    VkExtPropArray extensions = {
        .count = totalExtensions,
        .data = malloc(sizeof(VkExtensionProperties) * totalExtensions),
    };

    // Copy over default extensions
    VkExtensionProperties* currentExtension = extensions.data;
    memcpy(currentExtension, defaultExtensions.data, sizeof(VkExtensionProperties) * defaultExtensions.count);
    currentExtension += defaultExtensions.count;

    // Copy over layer extensions
    for (uint32_t i = 0; i < layerExtensions.count; ++i) {
        memcpy(currentExtension, layerExtensions.data[i].data, sizeof(VkExtensionProperties) * layerExtensions.data[i].count);
        currentExtension += layerExtensions.data[i].count;
    }

    // Free unflattened arrays
    for (uint32_t i = 0; i < layerExtensions.count; ++i) {
        free(layerExtensions.data[i].data);
    }
    free(layerExtensions.data);
    free(defaultExtensions.data);
    return extensions;
}