#include "engine.h"

#include <stdlib.h>
#include <memory.h>

GraphicsEngine::GraphicsEngine() {
    createInstance();
    setPhysicalDevice();
    createDevice();
}

GraphicsEngine::~GraphicsEngine() {
    device.destroy();
    instance.destroy();
}