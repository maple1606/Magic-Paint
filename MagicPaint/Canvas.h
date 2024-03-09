#pragma once
#ifndef CANVAS_H_INCLUDED
#define CANVAS_H_INCLUDED

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "Brush.h"
#include "Color.h"
#include "constant.h"
#include<iostream>

class Canvas {
public:
	Canvas(int width, int height);
	void display(GLFWwindow* window);

private:
	Brush* brush;
	Color** pixels;
	int width, height;
	int xOffset, yOffset, zoom;
	void normalizeCoordinate(float x, float y, float& normalizedX, float& normalizedY, float& normalizedWidth, float& normalizedHeight);
};

#endif // CANVAS_H_INCLUDED