#include "instance.h"

VkInstance createInstance() {
    VkInstance instance;

    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .apiVersion = VK_API_VERSION_1_1,
    };

    StringArray layers = getInstanceLayers();
    checkInstanceLayers(layers);

    StringArray extensions = getInstanceExtensions();
    checkInstanceExtensions(extensions, layers);

    VkInstanceCreateInfo instanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = layers.count,
        .ppEnabledLayerNames = layers.data,
        .enabledExtensionCount = extensions.count,
        .ppEnabledExtensionNames = extensions.data,
    };

    vkCreateInstance(
        &instanceCreateInfo, NULL, &instance
    );

    FREE_ARRAY(extensions);
    FREE_ARRAY(layers);
    return instance;
}

bool checkInstanceLayers(StringArray layers) {
    bool* found = calloc(layers.count, sizeof(bool));

    LayerArray availLayers;
    VK_ENUMERATE(availLayers, vkEnumerateInstanceLayerProperties);
    CHECK_ARRAYS(found, layers, availLayers, layerName);
    FREE_ARRAY(availLayers);

    bool foundAll;
    VERIFY_ARRAYS(foundAll, found, layers);

    free(found);
    return foundAll;
}

bool checkInstanceExtensions(StringArray extensions, StringArray layers) {
    bool* found = calloc(extensions.count, sizeof(bool));

    ExtensionArray availDefaultExtensions;
    VK_ENUMERATE_ARGS(availDefaultExtensions, vkEnumerateInstanceExtensionProperties, NULL);
    CHECK_ARRAYS(found, extensions, availDefaultExtensions, extensionName);
    FREE_ARRAY(availDefaultExtensions);

    for (uint32_t i = 0; i < layers.count; ++i) {
        ExtensionArray availLayerExtensions;
        VK_ENUMERATE_ARGS(availLayerExtensions, vkEnumerateInstanceExtensionProperties, layers.data[i]);
        CHECK_ARRAYS(found, extensions, availLayerExtensions, extensionName);
        FREE_ARRAY(availLayerExtensions);
    }

    bool foundAll;
    VERIFY_ARRAYS(foundAll, found, extensions);

    free(found);
    return foundAll;
}