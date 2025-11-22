// Author: Jake Rieger
// Created: 11/21/2025.
//

#include <window.h>
#include <stdbool.h>

#include "renderer.h"

xWindow* gWindow;
xRenderer* gRenderer;

static void onResize(GLFWwindow* window, int width, int height) {
    X_UNUSED(window);
    if (gRenderer) { xRendererResize(gRenderer, width, height); }
    if (gWindow) { xWindowSetDimensions(gWindow, width, height); }
}

static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GLFW_TRUE); }
}

int main(void) {
    xWindowInfo window_info;
    window_info.title     = "XenC Window";
    window_info.width     = 800;
    window_info.height    = 600;
    window_info.resizable = true;

    gWindow = xWindowCreate(&window_info);
    X_ASSERT_MSG(gWindow != NULL, "Window creation returned null ptr");

    xWindowSetDimensions(gWindow, 1280, 720);
    xWindowSetResizeCallback(gWindow, onResize);
    xWindowSetKeyCallback(gWindow, onKey);

    gRenderer = xRendererCreate();
    xRendererInitialize(gRenderer, gWindow->width, gWindow->height);

    while (!glfwWindowShouldClose(gWindow->handle)) {
        xRendererFrameBegin(gRenderer);
        // Render stuff
        xRendererFrameEnd(gRenderer);

        glfwPollEvents();
        glfwSwapBuffers(gWindow->handle);
    }

    xRendererShutdown(gRenderer);
    xRendererDestroy(gRenderer);
    xWindowDestroy(gWindow);

    return 0;
}