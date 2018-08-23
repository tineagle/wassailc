#pragma once

#include "core.h"

vk::Instance createInstance();

std::vector<std::string> getInstanceLayers();
bool checkInstanceLayers(const std::vector<std::string> &layerNames);


std::vector<std::string> getInstanceExtensions();
std::vector<vk::ExtensionProperties> enumerateAllInstanceExtensionProperties(const std::vector<std::string> &layers);
bool checkInstanceExtensions(const std::vector<std::string> &extensions, const std::vector<std::string> &layers);