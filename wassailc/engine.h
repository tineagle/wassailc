#pragma once

#include "vulkan/vulkan.hpp"

class GraphicsEngine {
private:
    vk::Instance instance;
    vk::PhysicalDevice physicalDevice;
    vk::Device device;
    vk::Queue graphicsQueue;
    vk::Queue presentQueue;

public:
    GraphicsEngine();
    ~GraphicsEngine();
private:
    void createInstance();
    void setPhysicalDevice();
    void createDevice();
};