// Author: Jake Rieger
// Created: 11/21/2025.
//

#pragma warning(disable : 4090)

#if defined(_MSC_VER)
    #define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "window.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

static void cleanup(xWindow* window) {
    X_FREE(window->title);
    X_FREE(window);
}

xWindow* xWindowCreate(const xWindowInfo* info) {
    X_ASSERT_MSG(info != NULL, "info is NULL");
    X_ASSERT_MSG(info->width > 0, "width <= 0");
    X_ASSERT_MSG(info->height > 0, "height <= 0");

    xWindow* window = X_MALLOC(xWindow, sizeof(xWindow));
    if (window == NULL) {
        X_PRINT_ERROR("Failed to allocate window struct memory\n");
        return NULL;
    }

    const size_t title_len = strlen(info->title);
    window->title          = X_MALLOC(char, title_len + 1);
    if (window->title == NULL) {
        free(window);
        X_PRINT_ERROR("Failed to allocate window title buffer\n");
        return NULL;
    }

    X_STRCPY_SAFE((char*)window->title, title_len, (char*)info->title);

    window->width  = info->width;
    window->height = info->height;

    // Create GLFW window
    if (!glfwInit()) {
        cleanup(window);
        X_PRINT_ERROR("Failed to initialize GLFW3\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window->handle = glfwCreateWindow(info->width, info->height, info->title, NULL, NULL);
    if (window->handle == NULL) {
        X_PRINT_ERROR("Failed to create GLFW window\n");
        glfwTerminate();
        cleanup(window);
        return NULL;
    }

    glfwMakeContextCurrent(window->handle);
    glfwSetWindowUserPointer(window->handle, window);
    glfwSwapInterval(1);  // V-Sync

    return window;
}

void xWindowDestroy(xWindow* window) {
    glfwDestroyWindow(window->handle);
    glfwTerminate();
    cleanup(window);
}

bool xWindowSetTitle(xWindow* window, const char* title) {
    glfwSetWindowTitle(window->handle, title);
    X_FREE(window->title);
    window->title = X_MALLOC(char, strlen(title) + 1);
    if (window->title == NULL) {
        X_PRINT_ERROR("Failed to allocate title buffer\n");
        return false;
    }
    X_STRCPY_SAFE((char*)window->title, strlen(title), title);
    return true;
}

bool xWindowSetWidth(xWindow* window, u32 width) {
    window->width = width;
    glfwSetWindowSize(window->handle, window->width, window->height);
    return true;
}

bool xWindowSetHeight(xWindow* window, u32 height) {
    window->height = height;
    glfwSetWindowSize(window->handle, window->width, window->height);
    return true;
}

bool xWindowSetDimensions(xWindow* window, u32 width, u32 height) {
    window->width  = width;
    window->height = height;
    glfwSetWindowSize(window->handle, window->width, window->height);
    return true;
}

bool xWindowSetKeyCallback(const xWindow* window, xWindowKeyCallback callback) {
    glfwSetKeyCallback(window->handle, callback);
    return true;
}

bool xWindowSetMouseCallback(const xWindow* window, xWindowMouseCallback callback) {
    glfwSetMouseButtonCallback(window->handle, callback);
    return true;
}

bool xWindowSetMouseScrollCallback(const xWindow* window, xWindowMouseScrollCallback callback) {
    glfwSetScrollCallback(window->handle, callback);
    return true;
}

bool xWindowSetResizeCallback(const xWindow* window, xWindowResizeCallback callback) {
    glfwSetWindowSizeCallback(window->handle, callback);
    return true;
}

bool xWindowSetCursorPositionCallback(const xWindow* window, xWindowCursorPositionCallback callback) {
    glfwSetCursorPosCallback(window->handle, callback);
    return true;
}