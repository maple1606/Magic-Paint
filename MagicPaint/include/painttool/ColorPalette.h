#pragma once
#ifndef COLORPALETTE_H_INCLUDED
#define COLORPALETTE_H_INCLUDED

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "Brush.h"
#include "Color.h"

#define PALETTE_ROWS 1
#define PALETTE_COLS 1

class ColorPalette {
public:
	ColorPalette();
	void display();
	Color getSelectedColor();

private:
	ImVec4 colorPalette;
	Color selectedColor;
};

#endif // COLORPALETTE_H_INCLUDED