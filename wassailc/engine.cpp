#include "engine.h"

#include <stdlib.h>
#include <memory.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "instance.h"
#include "physicaldevice.h"
#include "device.h"

typedef enum EngineStage {
    eBegin,
    eEnd,
} eEngineStage;

struct GraphicsEngine {
    eEngineStage stage;
    vk::Instance instance;
    vk::PhysicalDevice physicalDevice;
    vk::Device device;
};

GraphicsEngine* createGraphicsEngine() {
    glfwInit();

    GraphicsEngine* engine = new GraphicsEngine();
    engine->instance = createInstance();
    engine->physicalDevice = getPhysicalDevice(engine->instance);
    engine->device = createDevice(engine->physicalDevice);

    return engine;
}

void destroyGraphicsEngine(GraphicsEngine* engine) {
    engine->device.destroy();
    engine->instance.destroy();
    delete engine;
    glfwTerminate();
}