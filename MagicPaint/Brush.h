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
	void setColor(int x, int y, Color color);
	Color getColor(int x, int y);

private:
	Color** colors;
};

#endif // CANVAS_H_INCLUDED