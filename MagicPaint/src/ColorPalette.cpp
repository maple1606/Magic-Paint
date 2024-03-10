#include "ColorPalette.h"

ColorPalette::ColorPalette() {
    
}

void ColorPalette::display() {
    for (int row = 0; row < PALETTE_ROWS; ++row) {
        for (int col = 0; col < PALETTE_COLS; ++col) {
            ImVec4& color = paletteColors[row][col];
            ImGui::ColorPicker3("", (float*)&color);
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }
}