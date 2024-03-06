#pragma once
#ifndef MAINCONTROL_H_INCLUDED
#define MAINCONTROL_H_INCLUDED

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "Canvas.h"
#include "constant.h"
#include<iostream>

class MainControl
{
public:
    MainControl();
    ~MainControl();

    bool init();
    void setMode();
    void close();
    bool isQuit() const;

private:
    GLFWwindow* window;
    bool quit;

    Canvas* canvas;
};

#endif // MAINCONTROL_H_INCLUDED