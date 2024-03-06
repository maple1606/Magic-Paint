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
	Canvas();
	void display(GLFWwindow* window);

private:
	Brush* brush;
	Color** pixels;
};

#endif // CANVAS_H_INCLUDED