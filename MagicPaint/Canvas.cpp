#include "Canvas.h"

Canvas::Canvas(int width, int height) {
    this->width = width;
    this->height = height;
    zoom = 1.0f;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    struct Color white = { 1.0f, 1.0f, 1.0f, 1.0f };
    pixels = new Color * [SCREEN_WIDTH];
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        pixels[x] = new Color[SCREEN_HEIGHT];
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            pixels[x][y] = white;
        }
    }
    brush = new Brush(pixels);
}

void Canvas::display(GLFWwindow* window) {
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            xpos = static_cast<int>(xpos);
            ypos = static_cast<int>(ypos);
            struct Color black = { 0.0, 0.0, 0.0, 1.0 };
            brush->setColor(xpos, ypos, black);
        }

        glBegin(GL_QUADS);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                // for each pixel draw a quad - size of quad is equal to the zoom
                pixels[x][y] = brush->getColor(x, y);
                glColor3f(pixels[x][y].r, pixels[x][y].g, pixels[x][y].b);
                normalizeCoordinate(x, y);
                glVertex2f(normalizedX, normalizedY);
                glVertex2f(normalizedX + normalizedWidth, normalizedY);
                glVertex2f(normalizedX + normalizedWidth, normalizedY + normalizedHeight);
                glVertex2f(normalizedX, normalizedY + normalizedHeight);
            }
        }

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Canvas::normalizeCoordinate(float x, float y) {
    normalizedX = (x / (float)SCREEN_WIDTH) * 2.0f - 1.0;
    normalizedY = (1.0 - y / (float)SCREEN_HEIGHT) * 2.0f - 1.0;
    normalizedWidth = (4.0 / (float)SCREEN_WIDTH) * 2.0f;
    normalizedHeight = (4.0 / (float)SCREEN_HEIGHT) * 2.0f;
}
