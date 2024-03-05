#include "WhiteBoard.h"

void WhiteBoard::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int pixel_x = static_cast<int>(xpos);
        int pixel_y = static_cast<int>(ypos);

        if (pixel_x >= 0 && pixel_x < SCREEN_WIDTH && pixel_y >= 0 && pixel_y < SCREEN_HEIGHT) {
            glfwMakeContextCurrent(window);
            glClear(GL_COLOR_BUFFER_BIT);

            glPointSize(1.0f);
            glBegin(GL_POINTS);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2i(pixel_x, pixel_y);
            glEnd();

            glfwSwapBuffers(window);
        }
        std::cout << "Left mouse button clicked at (" << xpos << ", " << ypos << ")" << std::endl;
    }
}

void WhiteBoard::run(GLFWwindow* window) {
    // std::cout << "in progress\n";
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
