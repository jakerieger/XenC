// Author: Jake Rieger
// Created: 11/21/2025.
//

#include "renderer.h"

xRenderer* xRendererCreate() {
    xRenderer* renderer = X_MALLOC(xRenderer, sizeof(xRenderer));
    X_ASSERT_MSG(renderer != NULL, "Failed to create renderer");
    return renderer;
}

void xRendererDestroy(xRenderer* renderer) {
    X_FREE(renderer);
}

void xRendererInitialize(xRenderer* renderer, u32 width, u32 height) {
    renderer->width  = width;
    renderer->height = height;
}

void xRendererShutdown(xRenderer* renderer) {}

void xRendererResize(xRenderer* renderer, u32 width, u32 height) {
    renderer->width  = width;
    renderer->height = height;
}