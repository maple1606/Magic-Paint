#pragma once
#ifndef BRUSH_H_INCLUDED
#define BRUSH_H_INCLUDED

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "Color.h"
#include "constant.h"

class Brush {
public:
	Brush(Color** colors);
	~Brush();
	void setPixelColor(int x, int y);
	Color getPixelColor(int x, int y);
	void drawLine(int x1, int y1, int x2, int y2);
	void setBrushColor(Color color);
	void setBrushSize();

private:
	Color brushColor;
	int currentSizeIndex;
	float brushSize;
	Color** colors;
	bool checkInside(int x, int y, int xStart, int yStart);
	void floodFill(int x, int y, int xStart, int yStart);
};

#endif // CANVAS_H_INCLUDED