#include "instance.h"

#include <string.h>
#include <stdio.h>

VkInstance createInstance() {
    VkInstance instance = VK_NULL_HANDLE;

    VkApplicationInfo applicationInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Test App",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "Test Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_1,
    };

    StringArray layers = getInstanceLayers();
    checkInstanceLayers(layers);

    StringArray extensions = getInstanceExtensions();
    checkInstanceExtensions(extensions, layers);

    VkInstanceCreateInfo instanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &applicationInfo,
        .enabledLayerCount = layers.count,
        .ppEnabledLayerNames = layers.data,
        .enabledExtensionCount = extensions.count,
        .ppEnabledExtensionNames = extensions.data,
    };

    vkCreateInstance(&instanceCreateInfo, NULL, &instance);

    for (uint32_t i = 0; i < extensions.count; ++i) {
        free(extensions.data[i]);
    }
    free(extensions.data);
    for (uint32_t i = 0; i < layers.count; ++i) {
        free(layers.data[i]);
    }
    free(layers.data);

    //TODO: Check errors
    return instance;
}

StringArray getInstanceLayers() {
    uint32_t debugLayerCount = 1;
    const char* debugLayers[] = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    uint32_t totalLayers = debugLayerCount;
    char** layers = malloc(sizeof(char*) * totalLayers);

    char** currentLayer = layers;
    for (uint32_t i = 0; i < debugLayerCount; ++i) {
        *currentLayer = malloc(strlen(debugLayers[i]) + 1);
        strcpy(*currentLayer, debugLayers[i]);
        ++currentLayer;
    }

    StringArray arr = {
        .count = totalLayers,
        .data = layers,
    };
    return arr;
}

VkResult enumerateInstanceLayerProperties(VkLayerPropArray* layerArray) {
    VkResult result;
    uint32_t layerCount;
    VkLayerProperties *layers;

    // Attempt to fill array until success
    do {
        result = vkEnumerateInstanceLayerProperties(&layerCount, NULL);
        layers = malloc(sizeof(VkLayerProperties) * layerCount);
        result = vkEnumerateInstanceLayerProperties(&layerCount, layers);

        // Free memory if failed
        if (result != VK_SUCCESS) {
            free(layers);
        }
        // Check for error
        if (result < 0) {
            printf("VkError: %d\n", result);
            return result;
        }
    } while (result == VK_INCOMPLETE);

    layerArray->count = layerCount;
    layerArray->data = layers;
    return VK_SUCCESS;
}

bool checkInstanceLayers(StringArray layerNames) {
    VkLayerPropArray availLayers;
    enumerateInstanceLayerProperties(&availLayers);

    printf("Checking for %d instance layer(s)...\n", layerNames.count);
    bool foundLayers = checkLayers(layerNames, availLayers);
    printf("%s instance layers.\n\n", foundLayers ? "FOUND ALL" : "MISSING");

    free(availLayers.data);
    return foundLayers;
}

StringArray getInstanceExtensions() {
    uint32_t debugExtensionCount = 1;
    const char* debugExtensions[] = {
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
    };

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    uint32_t totalExtensions = debugExtensionCount + glfwExtensionCount;
    char** extensions = malloc(sizeof(char*) * totalExtensions);

    char** currentExtension = extensions;
    for (uint32_t i = 0; i < debugExtensionCount; ++i) {
        *currentExtension = malloc(strlen(debugExtensions[i]) + 1);
        strcpy(*currentExtension, debugExtensions[i]);
        ++currentExtension;
    }
    for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
        *currentExtension = malloc(strlen(glfwExtensions[i]) + 1);
        strcpy(*currentExtension, glfwExtensions[i]);
        ++currentExtension;
    }

    StringArray arr = {
        .count = totalExtensions,
        .data = extensions,
    };
    return arr;
}

VkResult enumerateInstanceExtensionProperties(const char* layerName, VkExtPropArray* extensionArray) {
    VkResult result;
    uint32_t extensionCount;
    VkExtensionProperties *extensions;

    // Attempt to fill array until success
    do {
        result = vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, NULL);
        extensions = malloc(sizeof(VkExtensionProperties) * extensionCount);
        result = vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, extensions);

        // Free memory if failed
        if (result != VK_SUCCESS) {
            free(extensions);
        }
        // Check for error
        if (result < 0) {
            printf("VkError: %d\n", result);
            return result;
        }
    } while (result == VK_INCOMPLETE);

    extensionArray->count = extensionCount;
    extensionArray->data = extensions;
    return VK_SUCCESS;
}

VkExtPropArray enumerateAllInstanceExtensionProperties(StringArray layers) {
    VkResult result;

    // Get default extensions associated with NULL
    VkExtPropArray defaultExtensions;
    result = enumerateInstanceExtensionProperties(NULL, &defaultExtensions);

    // Get extensions associated with each layer
    VkExtPropArrayArray layerExtensions = {
        .count = layers.count,
        .data = malloc(sizeof(VkExtPropArray) * layers.count),
    };
    for (uint32_t i = 0; i < layers.count; ++i) {
        result = enumerateInstanceExtensionProperties(layers.data[i], &layerExtensions.data[i]);
    }

    // Flatten arrays
    VkExtPropArray extensions = flattenExtPropArrays(defaultExtensions, layerExtensions);
    return extensions;
}

bool checkInstanceExtensions(StringArray extensions, StringArray layers) {
    VkExtPropArray availExtensions = enumerateAllInstanceExtensionProperties(layers);

    printf("Checking for %u instance extension(s)...\n", extensions.count);
    bool foundAll = checkExtensions(extensions, availExtensions);
    printf("%s instance extensions.\n\n", foundAll ? "FOUND ALL" : "MISSING");

    free(availExtensions.data);
    return foundAll;
}