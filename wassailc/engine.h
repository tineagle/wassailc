#pragma once

#include "vulkan/vulkan.hpp"

struct QueueInfo {
    uint32_t index;
    std::vector<float> priorities;
};

class GraphicsEngine {
private:
    vk::Instance instance;
    vk::PhysicalDevice physicalDevice;
    std::vector<QueueInfo> queueInfos;
    vk::Device device;

public:
    GraphicsEngine();
    ~GraphicsEngine();
private:
    void createInstance();
    void setPhysicalDevice();
    void getQueueInfos();
    void createDevice();
};