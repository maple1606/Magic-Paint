#include "ColorPalette.h"

ColorPalette::ColorPalette() {
    struct Color black = { 0.0, 0.0, 0.0, 1.0 };
    selectedColor = black;
}

Color ColorPalette::getSelectedColor() {
    return selectedColor;
}

void ColorPalette::display() {
    ImGui::NewLine();
    ImGui::ColorPicker3("", (float*)&colorPalette);
    struct Color newColor = { colorPalette.x, colorPalette.y, colorPalette.z, colorPalette.w };
    selectedColor = newColor;
}