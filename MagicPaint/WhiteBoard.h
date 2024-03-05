#pragma once
#ifndef WHITEBOARD_H_INCLUDED
#define WHITEBOARD_H_INCLUDED

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

class WhiteBoard {
public:
	void run(GLFWwindow* window);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};

#endif // WHITEBOARD_H_INCLUDED