// Author: Jake Rieger
// Created: 11/21/2025.
//

#pragma once

#include "common.h"

typedef struct {
    u32 width;
    u32 height;
} xRenderer;

xRenderer* xRendererCreate();
void xRendererDestroy(xRenderer* renderer);

void xRendererInitialize(xRenderer* renderer, u32 width, u32 height);
void xRendererShutdown(xRenderer* renderer);
void xRendererResize(xRenderer* renderer, u32 width, u32 height);

// TODO: Figure out what this is actually going to do
inline void xRendererFrameBegin(xRenderer* renderer) {}
inline void xRendererFrameEnd(xRenderer* renderer) {}
