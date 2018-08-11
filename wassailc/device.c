#include "device.h"

#include <stdlib.h>
#include <stdio.h>

VkDevice createDevice(VkPhysicalDevice physicalDevice) {
    VkDevice device = VK_NULL_HANDLE;

    QueueCreateInfoArray queueCreateInfos = getQueueCreateInfos(physicalDevice);

    StringArray layers = getDeviceLayers();
    checkDeviceLayers(physicalDevice, layers);

    StringArray extensions = getDeviceExtensions();
    checkDeviceExtensions(physicalDevice, extensions, layers);

    VkDeviceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = queueCreateInfos.count,
        .pQueueCreateInfos = queueCreateInfos.data,
        .enabledLayerCount = layers.count,
        .ppEnabledLayerNames = layers.data,
        .enabledExtensionCount = extensions.count,
        .ppEnabledExtensionNames = extensions.data,
        .pEnabledFeatures = NULL,
    };

    // vkCreateDevice(physicalDevice, &createInfo, NULL, &device);

    for (uint32_t i = 0; i < extensions.count; ++i) {
        free(extensions.data[i]);
    }
    free(extensions.data);
    for (uint32_t i = 0; i < layers.count; ++i) {
        free(layers.data[i]);
    }
    free(layers.data);
    for (uint32_t i = 0; i < queueCreateInfos.count; ++i) {
        free(queueCreateInfos.data[i].pQueuePriorities);
    }
    free(queueCreateInfos.data);
    return device;
}

QueuePriorityArray getQueuePriority(VkQueueFamilyProperties family) {
    uint32_t queuePriorityCount = 0;
    float* queuePriorities = NULL;

    QueuePriorityArray arr = {
        .count = queuePriorityCount,
        .data = queuePriorities,
    };
    return arr;
}

VkDeviceQueueCreateInfo getQueueCreateInfo(uint32_t index, VkQueueFamilyProperties *families) {
    QueuePriorityArray priorities = getQueuePriority(families[index]);
    VkDeviceQueueCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = index,
        .queueCount = priorities.count,
        .pQueuePriorities = priorities.data,
    };
    return createInfo;
}

QueueCreateInfoArray getQueueCreateInfos(VkPhysicalDevice physicalDevice) {
    uint32_t familyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, NULL);
    VkQueueFamilyProperties *families = malloc(sizeof(VkQueueFamilyProperties) * familyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, families);

    // Select graphics queue
    uint32_t graphicsQueueFamilyIndex = ~0;
    for (uint32_t i = 0; i < familyCount; ++i) {

    }
    // Select present queue
    uint32_t presentQueueFamilyIndex = ~0;
    for (uint32_t i = 0; i < familyCount; ++i) {

    }

    uint32_t createInfoCount = 0;
    VkDeviceQueueCreateInfo *createInfos = malloc(sizeof(VkDeviceQueueCreateInfo) * createInfoCount);

    QueueCreateInfoArray arr = {
        .count = createInfoCount,
        .data = createInfos,
    };
    return arr;
}

StringArray getDeviceLayers() {
    StringArray arr = {
        .count = 0,
        .data = NULL,
    };
    return arr;
}

VkResult enumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, VkLayerPropArray* layerArray) {
    VkResult result;
    uint32_t layerCount;
    VkLayerProperties *layers;

    // Attempt to fill array until success
    do {
        result = vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, NULL);
        layers = malloc(sizeof(VkLayerProperties) * layerCount);
        result = vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, layers);

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

bool checkDeviceLayers(VkPhysicalDevice physicalDevice, StringArray layers) {
    VkLayerPropArray availLayers;
    enumerateDeviceLayerProperties(physicalDevice, &availLayers);

    printf("Checking for %d device layer(s)...\n", layers.count);
    bool foundLayers = checkLayers(layers, availLayers);
    printf("%s device layers.\n\n", foundLayers ? "FOUND ALL" : "MISSING");

    free(availLayers.data);
    return foundLayers;
}

StringArray getDeviceExtensions() {
    StringArray arr = {
        .count = 0,
        .data = NULL,
    };
    return arr;
}

VkResult enumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, char* layerName, VkExtPropArray *extensionArray) {
    VkResult result;
    uint32_t extensionCount;
    VkExtensionProperties *extensions;

    // Attempt to fill array until success
    do {
        result = vkEnumerateDeviceExtensionProperties(physicalDevice, layerName, &extensionCount, NULL);
        extensions = malloc(sizeof(VkExtensionProperties) * extensionCount);
        result = vkEnumerateDeviceExtensionProperties(physicalDevice, layerName, &extensionCount, extensions);

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

VkExtPropArray enumerateAllDeviceExtensionProperties(VkPhysicalDevice physicalDevice, StringArray layers) {
    VkResult result;

    // Get default extensions associated with NULL
    VkExtPropArray defaultExtensions;
    result = enumerateDeviceExtensionProperties(physicalDevice, NULL, &defaultExtensions);

    // Get extensions associated with each layer
    VkExtPropArrayArray layerExtensions = {
        .count = layers.count,
        .data = malloc(sizeof(VkExtPropArray) * layers.count),
    };
    for (uint32_t i = 0; i < layers.count; ++i) {
        result = enumerateDeviceExtensionProperties(physicalDevice, layers.data[i], &layerExtensions.data[i]);
    }

    // Flatten arrays
    VkExtPropArray extensions = flattenExtPropArrays(defaultExtensions, layerExtensions);
    return extensions;
}

bool checkDeviceExtensions(VkPhysicalDevice physicalDevice, StringArray extensions, StringArray layers) {
    VkExtPropArray availExtensions = enumerateAllDeviceExtensionProperties(physicalDevice, layers);

    printf("Checking for %d device extension(s)...\n", extensions.count);
    bool foundAll = checkExtensions(extensions, availExtensions);
    printf("%s device extensions.\n\n", foundAll ? "FOUND ALL" : "MISSING");

    free(availExtensions.data);
    return foundAll;
}