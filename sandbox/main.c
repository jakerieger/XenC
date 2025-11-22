// Author: Jake Rieger
// Created: 11/21/2025.
//

#include <window.h>
#include <stdbool.h>

static void on_resize(GLFWwindow* window, int width, int height) {
    // do some stuff
}

static void on_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GLFW_TRUE); }
}

int main(void) {
    xWindowInfo window_info;
    window_info.title     = "XenC Window";
    window_info.width     = 800;
    window_info.height    = 600;
    window_info.resizable = true;

    xWindow* window = xWindowCreate(&window_info);
    X_ASSERT_MSG(window != NULL, "Window creation returned null ptr");

    xWindowSetDimensions(window, 1280, 720);
    xWindowSetResizeCallback(window, on_resize);
    xWindowSetKeyCallback(window, on_key);

    while (!glfwWindowShouldClose(window->handle)) {
        glfwPollEvents();
        glfwSwapBuffers(window->handle);
    }

    xWindowDestroy(window);

    return 0;
}