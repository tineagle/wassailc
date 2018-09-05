#include "physicaldevice.h"

VkPhysicalDevice getPhysicalDevice(VkInstance instance) {
    PhysicalDeviceArray devices;
    VK_ENUMERATE_ARGS(devices, vkEnumeratePhysicalDevices, instance);

    VkPhysicalDevice device = VK_NULL_HANDLE;
    for (uint32_t i = 0; i < devices.count; ++i) {
        if (checkDevice(devices.data[i])) {
            device = devices.data[i];
            break;
        }
    }
    FREE_ARRAY(devices);
    return device;
}
bool checkDevice(VkPhysicalDevice device) {
    bool suitable = true;

    suitable &= checkFeatures(device);

    StringArray layers = getDeviceLayers();
    suitable &= checkDeviceLayers(device, layers);

    StringArray extensions = getDeviceExtensions();
    suitable &= checkDeviceExtensions(device, extensions, layers);

    FREE_ARRAY(extensions);
    FREE_ARRAY(layers);
    return suitable;
}

bool checkFeatures(VkPhysicalDevice device) {
    return true;
}

bool checkDeviceLayers(VkPhysicalDevice device, StringArray layers) {
    bool* found = calloc(layers.count, sizeof(bool));

    LayerArray availLayers;
    VK_ENUMERATE_ARGS(availLayers, vkEnumerateDeviceLayerProperties, device);
    CHECK_ARRAYS(found, layers, availLayers, layerName);
    FREE_ARRAY(availLayers);

    bool foundAll;
    VERIFY_ARRAYS(foundAll, found, layers);

    free(found);
    return foundAll;
}

bool checkDeviceExtensions(VkPhysicalDevice device, StringArray extensions, StringArray layers) {
    bool* found = calloc(extensions.count, sizeof(bool));

    ExtensionArray availDefaultExtensions;
    VK_ENUMERATE_ARGS(availDefaultExtensions, vkEnumerateDeviceExtensionProperties, device, NULL);
    CHECK_ARRAYS(found, extensions, availDefaultExtensions, extensionName);
    FREE_ARRAY(availDefaultExtensions);

    for (uint32_t i = 0; i < layers.count; ++i) {
        ExtensionArray availLayerExtensions;
        VK_ENUMERATE_ARGS(availLayerExtensions, vkEnumerateDeviceExtensionProperties, device, layers.data[i]);
        CHECK_ARRAYS(found, extensions, availLayerExtensions, extensionName);
        FREE_ARRAY(availLayerExtensions);
    }

    bool foundAll;
    VERIFY_ARRAYS(foundAll, found, extensions);

    free(found);
    return foundAll;
}