#pragma once
#ifndef FILLTOOL_H_INCLUDED
#define FILLTOOL_H_INCLUDED

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "Color.h"
#include "constant.h"

class FillTool {
public:
	FillTool();
	void display();
	void fillColor(Color** pixels, int x, int y, Color color);
	bool isEnabled();

private:
	bool enabled;
	void floodFill(Color** pixels, int x, int y, Color oldColor, Color newColor);
	bool checkValidity(Color** pixels, int x, int y, Color oldColor, Color newColor);
};

#endif // FILLTOOL_H_INCLUDED