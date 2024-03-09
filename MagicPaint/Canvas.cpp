#include "Canvas.h"

Canvas::Canvas(int width, int height) {
    this->width = width;
    this->height = height;
    zoom = 3.0f;
    isDrawing = false;
    previousX = previousY = 0;
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

Canvas::~Canvas() {
    for (int x = 0; x < width; x++) {
        delete[] pixels[x];
    }
    delete[] pixels;
}

void Canvas::display(GLFWwindow* window) {
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        handleMouseMotion(window);

        glBegin(GL_QUADS);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                renderPixel(x, y);
            }
        }

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Canvas::renderPixel(int x, int y) {
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

void Canvas::normalizeCoordinate(float x, float y, float& normalizedX, float& normalizedY, float& normalizedWidth, float& normalizedHeight) {
    normalizedX = (x / (float)width) * 2.0f - 1.0f;
    normalizedY = 1.0f - (y / (float)height) * 2.0f;

    // for each pixel draw a quad - size of quad is equal to the zoom
    normalizedWidth = zoom / (float)width;
    normalizedHeight = zoom / (float)height;
}

void Canvas::handleMouseMotion(GLFWwindow* window) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int canvasX = static_cast<int>(xpos);
        int canvasY = static_cast<int>(ypos);

        if (isDrawing) {
            struct Color black = { 0.0f, 0.0f, 0.0f, 1.0f };
            brush->setColor(xpos, ypos, zoom, black);
            drawLine(previousX, previousY, canvasX, canvasY, black);
        }

        previousX = canvasX;
        previousY = canvasY;

        isDrawing = true;
    }
    else {
        isDrawing = false;
    }
}


void Canvas::drawLine(int x1, int y1, int x2, int y2, Color color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        brush->setColor(x1, y1, zoom, color);
        renderPixel(x1, y1);

        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}
