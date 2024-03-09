#include "Brush.h"
#include<queue>
#include<iostream>

Brush::Brush(Color** colors) {
	this->colors = colors;
}

void Brush::setColor(int x, int y, int zoom, Color color) {
	struct Color newColor = { color.r, color.g, color.b, color.a };
	colors[x][y] = newColor;
    floodfill(x, y, x, y, zoom, color);
}

Color Brush::getColor(int x, int y) {
	return colors[x][y];
}

bool Brush::checkInside(int x, int y, int xStart, int yStart, int zoom) {
    return (x >= xStart && x < xStart + zoom && y >= yStart && y < yStart + zoom);
}

void Brush::floodfill(int x, int y, int xStart, int yStart, int zoom, Color color) {
    if (!checkInside(x, y, xStart, yStart, zoom))
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

        colors[cx][cy] = color;

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (checkInside(nx, ny, xStart, yStart, zoom) && colors[nx][ny] != color) {
                q.push({ nx, ny });
            }
        }
    }
}
