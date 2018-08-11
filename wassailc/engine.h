#pragma once

typedef struct GraphicsEngine GraphicsEngine;

GraphicsEngine* createGraphicsEngine();
void destroyGraphicsEngine(GraphicsEngine* engine);