#include "WhiteBoard.h"

void WhiteBoard::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "Left mouse button clicked at (" << xpos << ", " << ypos << ")" << std::endl;
    }
}

void WhiteBoard::run(GLFWwindow* window) {
    // std::cout << "in progress\n";
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
