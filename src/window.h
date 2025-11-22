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
} Window;

typedef struct {
    u32 width;
    u32 height;
    const char* title;
    bool resizable;
} WindowInfo;

typedef void (*window_key_callback)(GLFWwindow* window, int key, int scancode, int action, int mods);
typedef void (*window_mouse_callback)(GLFWwindow* window, int button, int, int);
typedef void (*window_mouse_scroll_callback)(GLFWwindow* window, double xoffset, double yoffset);
typedef void (*window_resize_callback)(GLFWwindow* window, int width, int height);
typedef void (*window_cursor_position_callback)(GLFWwindow* window, double xpos, double ypos);

Window* window_create(const WindowInfo* info);
void window_destroy(Window* window);

bool window_set_title(Window* window, const char* title);
bool window_set_width(Window* window, u32 width);
bool window_set_height(Window* window, u32 height);
bool window_set_dimensions(Window* window, u32 width, u32 height);

bool window_set_key_callback(const Window* window, window_key_callback callback);
bool window_set_mouse_callback(const Window* window, window_mouse_callback callback);
bool window_set_mouse_scroll_callback(const Window* window, window_mouse_scroll_callback callback);
bool window_set_resize_callback(const Window* window, window_resize_callback callback);
bool window_set_cursor_position_callback(const Window* window, window_cursor_position_callback callback);