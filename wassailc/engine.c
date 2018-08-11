#include "engine.h"

#include <stdlib.h>
#include <memory.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "instance.h"
#include "physicaldevice.h"
#include "device.h"

void* copyToHeap(void* obj, size_t objSize) {
    return memcpy(malloc(objSize), obj, objSize);
}
#define COPY_TO_HEAP(obj) copyToHeap(&obj, sizeof(obj))

typedef enum EngineStage {
    eBegin,
    eEnd,
} eEngineStage;

struct GraphicsEngine {
    eEngineStage stage;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
};

GraphicsEngine* createGraphicsEngine() {
    glfwInit();
    GraphicsEngine engine = {
        .stage = eBegin,
        .instance = VK_NULL_HANDLE,
        .physicalDevice = VK_NULL_HANDLE,
        .device = VK_NULL_HANDLE,
    };

    engine.instance = createInstance();
    engine.physicalDevice = getPhysicalDevice(engine.instance);
    engine.device = createDevice(engine.physicalDevice);

    return COPY_TO_HEAP(engine);
}

void destroyGraphicsEngine(GraphicsEngine* engine) {
    free(engine);
    glfwTerminate();
}