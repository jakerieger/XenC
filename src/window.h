// Author: Jake Rieger
// Created: 11/21/2025.
//

#pragma once

#include "common.h"
#include <GLFW/glfw3.h>

typedef struct {
    u32 width;
    u32 height;
    const char* title;
    GLFWwindow* handle;
} xWindow;

typedef struct {
    u32 width;
    u32 height;
    const char* title;
    bool resizable;
} xWindowInfo;

typedef void (*xWindowKeyCallback)(GLFWwindow* window, int key, int scancode, int action, int mods);
typedef void (*xWindowMouseCallback)(GLFWwindow* window, int button, int, int);
typedef void (*xWindowMouseScrollCallback)(GLFWwindow* window, double xoffset, double yoffset);
typedef void (*xWindowResizeCallback)(GLFWwindow* window, int width, int height);
typedef void (*xWindowCursorPositionCallback)(GLFWwindow* window, double xpos, double ypos);

xWindow* xWindowCreate(const xWindowInfo* info);
void xWindowDestroy(xWindow* window);

bool xWindowSetTitle(xWindow* window, const char* title);
bool xWindowSetWidth(xWindow* window, u32 width);
bool xWindowSetHeight(xWindow* window, u32 height);
bool xWindowSetDimensions(xWindow* window, u32 width, u32 height);

bool xWindowSetKeyCallback(const xWindow* window, xWindowKeyCallback callback);
bool xWindowSetMouseCallback(const xWindow* window, xWindowMouseCallback callback);
bool xWindowSetMouseScrollCallback(const xWindow* window, xWindowMouseScrollCallback callback);
bool xWindowSetResizeCallback(const xWindow* window, xWindowResizeCallback callback);
bool xWindowSetCursorPositionCallback(const xWindow* window, xWindowCursorPositionCallback callback);