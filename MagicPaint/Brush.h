#pragma once
#ifndef BRUSH_H_INCLUDED
#define BRUSH_H_INCLUDED

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "Color.h"
#include "constant.h"

class Brush {
public:
	Brush(Color** colors);
	void setColor(int x, int y, int zoom, Color color);
	Color getColor(int x, int y);

private:
	Color** colors;
	bool checkInside(int x, int y, int xStart, int yStart, int zoom);
	void floodfill(int x, int y, int xStart, int yStart, int zoom, Color color);
};

#endif // CANVAS_H_INCLUDED