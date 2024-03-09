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
	~Canvas();
	void display(GLFWwindow* window);

private:
	Brush* brush;
	Color** pixels;
	int width, height, zoom;
	bool isDrawing;
	int previousX, previousY;
	void renderPixel(int x, int y);
	void drawLine(int x1, int y1, int x2, int y2, Color color);
	void handleMouseMotion(GLFWwindow* window);
	void normalizeCoordinate(float x, float y, float& normalizedX, float& normalizedY, float& normalizedWidth, float& normalizedHeight);
};

#endif // CANVAS_H_INCLUDED