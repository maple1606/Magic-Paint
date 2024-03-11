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
    colorPalette = new ColorPalette();
    fillTool = new FillTool();
}

Canvas::~Canvas() {
    for (int x = 0; x < width; x++) {
        delete[] pixels[x];
        pixels[x] = NULL;
    }
    delete[] pixels;
    pixels = NULL;
    delete brush;
    brush = NULL;
    delete colorPalette;
    colorPalette = NULL;
    delete fillTool;
    fillTool = NULL;
}

void Canvas::display(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL a new frame is about to begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("ImGUI showtime!");
        ImGui::Text("Hello there adventurer!");
        brush->setBrushSize();
        fillTool->display();
        colorPalette->display();
        brush->setBrushColor(colorPalette->getSelectedColor());
        ImGui::End();

        handleMouseMotion(window);

        glBegin(GL_QUADS);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                renderPixel(x, y);
            }
        }

        glEnd();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Canvas::renderPixel(int x, int y) {
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
    if (ImGui::IsAnyItemActive()) {
        isDrawing = false; // Disable drawing if interacting with ImGui UI
        return;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int canvasX = static_cast<int>(xpos);
        int canvasY = static_cast<int>(ypos);

        if (!fillTool->isEnabled()) 
        {
            if (isDrawing) {
                brush->setPixelColor(xpos, ypos);
                brush->drawLine(previousX, previousY, canvasX, canvasY);
            }

            previousX = canvasX;
            previousY = canvasY;

            isDrawing = true;
            pixels[canvasX][canvasY] = brush->getPixelColor(canvasX, canvasY);
        } 
        else {
            fillTool->fillColor(pixels, xpos, ypos, colorPalette->getSelectedColor());
        }
    }
    else {
        isDrawing = false;
    }
}