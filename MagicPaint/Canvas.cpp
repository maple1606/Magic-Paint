#include "Canvas.h"

Canvas::Canvas() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    struct Color white = { 1.0f, 1.0f, 1.0f, 1.0f };
    pixels = new Color * [SCREEN_WIDTH];
    for (int x = 0; x < SCREEN_WIDTH; ++x) {
        pixels[x] = new Color[SCREEN_HEIGHT];
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            pixels[x][y] = white;
        }
    }
    brush = new Brush(pixels);
}

void Canvas::display(GLFWwindow* window) {
    // std::cout << "in progress\n";
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            xpos = static_cast<int>(xpos);
            ypos = static_cast<int>(ypos);
            brush->setColor(xpos, ypos, 1.0, 1.0, 1.0, 1.0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
