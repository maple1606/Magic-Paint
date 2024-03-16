#include "Brush.h"
#include<queue>
#include<iostream>

Brush::Brush(Color** colors) {
    this->colors = colors;
    brushSize = 3.0f;
    currentSizeIndex = 0;
}

Brush::~Brush() {
    delete[] colors;
    colors = NULL;
}

void Brush::setBrushColor(Color color) {
    this->brushColor = color;
}

void Brush::setBrushSize() {
    const float sizes[] = { 1.0f, 3.0f, 5.0f, 8.0f };
    ImGui::NewLine();
    ImGui::Text("Brush Size");
    if (ImGui::Combo("##Brush Size", &currentSizeIndex, " 1.0\0 3.0\0 5.0\0 8.0\0")) {
        this->brushSize = sizes[currentSizeIndex];
    }
}

void Brush::setPixelColor(int x, int y) {
    colors[x][y] = this->brushColor;
    floodFill(x, y, x, y);
}

Color Brush::getPixelColor(int x, int y) {
    return colors[x][y];
}

bool Brush::checkInside(int x, int y, int xStart, int yStart) {
    if (x < xStart || x >= xStart + this->brushSize || y < yStart || y >= yStart + this->brushSize)
        return false;
    return true;
}

void Brush::floodFill(int x, int y, int xStart, int yStart) {
    if (!checkInside(x, y, xStart, yStart))
        return;

    std::queue<std::pair<int, int>> q;

    q.push({ x, y });

    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();
        int cx = current.first;
        int cy = current.second;

        colors[cx][cy] = this->brushColor;

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (checkInside(nx, ny, xStart, yStart) && colors[nx][ny] != this->brushColor) {
                q.push({ nx, ny });
            }
        }
    }
}

void Brush::drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixelColor(x1, y1);

        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { 
            err -= dy; 
            x1 += sx; 
        }
        if (e2 < dx) { 
            err += dx; 
            y1 += sy; 
        }
    }
}