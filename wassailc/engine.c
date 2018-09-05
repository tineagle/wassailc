#include "engine.h"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

typedef struct Engine {
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
} Engine;

StringArray getInstanceLayers() {
    StringArray layers = {
        .count = 0,
        .data = NULL,
    };
    return layers;
}

StringArray getInstanceExtensions() {
    StringArray extensions = {
        .count = 0,
        .data = NULL,
    };
    return extensions;
}

StringArray getDeviceLayers() {
    StringArray layers = {
        .count = 0,
        .data = NULL,
    };
    return layers;
}

StringArray getDeviceExtensions() {
    StringArray extensions = {
        .count = 0,
        .data = NULL,
    };
    return extensions;
}

int main() {

    //VkDeviceCreateInfo deviceCreateInfo = {
    //    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    //    .queueCreateInfoCount = 1,
    //    .pQueueCreateInfos = queueCreateInfos,
    //    .enabledLayerCount = deviceLayerCount,
    //    .ppEnabledLayerNames = deviceLayers,
    //    .enabledExtensionCount = deviceExtensionCount,
    //    .ppEnabledExtensionNames = deviceExtensions,
    //};

    //VkDevice device;
    //result = vkCreateDevice(physicalDevice, &deviceCreateInfo, NULL, &device);

    //VkQueue graphicsQueue;
    //vkGetDeviceQueue(device, 0, 0, &graphicsQueue);

    //VkQueue presentQueue;
    //vkGetDeviceQueue(device, 0, 0, &presentQueue);

    //VkSwapchainCreateInfoKHR swapchainCreateInfo = {
    //    .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
    //};

    //VkSwapchainKHR swapchain;
    //result = vkCreateSwapchainKHR(device, &swapchainCreateInfo, NULL, &swapchain);

    //uint32_t imageCount;
    //vkGetSwapchainImagesKHR(device, swapchain, &imageCount, NULL);
    //VkImage *images = malloc(sizeof(VkImage) * imageCount);
    //vkGetSwapchainImagesKHR(device, swapchain, &imageCount, NULL);

    //VkImageView *imageViews = malloc(sizeof(VkImageView) * imageCount);
    //for (uint32_t i = 0; i < imageCount; ++i) {
    //    VkImageViewCreateInfo viewCreateInfo = {
    //        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    //        .image = images[i],
    //    };

    //    vkCreateImageView(device, &viewCreateInfo, NULL, imageViews + i);
    //}
    //free(images);


    //for (uint32_t i = 0; i < imageCount; ++i) {
    //    vkDestroyImageView(device, imageViews[i], NULL);
    //}
    //free(imageViews);

    //vkDestroySwapchainKHR(device, swapchain, NULL);
    //vkDestroyDevice(device, NULL);
    //vkDestroyInstance(engine.instance, NULL);
    //glfwTerminate();
    return 0;
}