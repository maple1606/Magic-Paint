#include "Canvas.h"

Canvas::Canvas(int width, int height) {
    this->width = width;
    this->height = height;
    zoom = 3.0f;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    struct Color white = { 1.0f, 1.0f, 1.0f, 1.0f };
    pixels = new Color * [width];
    for (int x = 0; x < width; x++) {
        pixels[x] = new Color[height];
        for (int y = 0; y < height; y++) {
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
            struct Color black = { 0.0f, 0.0f, 0.0f, 1.0f };
            brush->setColor(xpos, ypos, zoom, black);
        }

        glBegin(GL_QUADS);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                pixels[x][y] = brush->getColor(x, y);
                float normalizedX, normalizedY, normalizedWidth, normalizedHeight;
                x = static_cast<float>(x);
                y = static_cast<float>(y);
                normalizeCoordinate(x, y, normalizedX, normalizedY, normalizedWidth, normalizedHeight);
                glColor3f(pixels[x][y].r, pixels[x][y].g, pixels[x][y].b);
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

void Canvas::normalizeCoordinate(float x, float y, float& normalizedX, float& normalizedY, float& normalizedWidth, float& normalizedHeight) {
    normalizedX = (x / (float)width) * 2.0f - 1.0f;
    normalizedY = 1.0f - (y / (float)height) * 2.0f;
    // for each pixel draw a quad - size of quad is equal to the zoom

    normalizedWidth =  zoom / (float)width;
    normalizedHeight = zoom / (float)height;
}
