#include "FillTool.h"
#include <queue>
#include <iostream>

FillTool::FillTool() {
    enabled = false;
}

bool FillTool::isEnabled() {
    return enabled;
}

void FillTool::display() {
    ImGui::NewLine();
    ImGui::Checkbox("Fill Tool", &enabled);
}

void FillTool::fillColor(Color** pixels, int x, int y, Color newColor) {
    Color oldColor = pixels[x][y];
    if (oldColor == newColor)
        return; 

    floodFill(pixels, x, y, oldColor, newColor);
}


bool FillTool::checkValidity(Color** pixels, int x, int y, Color oldColor, Color newColor) {
    if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
        return false;
    if (pixels[x][y] == newColor)
        return false;
    if (pixels[x][y] != oldColor)
        return false;
    
    return true;
}

void FillTool::floodFill(Color** pixels, int x, int y, Color oldColor, Color newColor) {
    if (!checkValidity(pixels, x, y, oldColor, newColor))
        return;

    std::queue<std::pair<int, int>> q;

    q.push({ x, y });

    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };

    pixels[x][y] = newColor;

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();
        int cx = current.first;
        int cy = current.second;

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (checkValidity(pixels, nx, ny, oldColor, newColor)) {
                pixels[nx][ny] = newColor;
                q.push({ nx, ny });
            }
        }
    }
}
