#pragma once

#include <string>

#include "core.h"

std::vector<const char*> toCStrings(const std::vector<std::string> &strings);

bool checkLayer(const std::string &layer, const std::vector<vk::LayerProperties> &layers);
bool checkLayers(const std::vector<std::string> &layers, const std::vector<vk::LayerProperties> &availLayers);
bool checkExtension(const std::string &extension, const std::vector<vk::ExtensionProperties> &extensions);
bool checkExtensions(const std::vector<std::string> &extensions, const std::vector<vk::ExtensionProperties> &availExtensions);
std::vector<vk::ExtensionProperties> flattenExtPropArrays(const std::vector<vk::ExtensionProperties> &defaultExtensions, const std::vector<std::vector<vk::ExtensionProperties>> &totalLayerExtensions);