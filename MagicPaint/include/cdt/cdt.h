#pragma once
#ifndef CDT_H_INCLUDED
#define CDT_H_INCLUDED

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <sstream>

#include "shapes.h"
#include "error.h"

using namespace std;

class CDT {
public:
    void display();
    const bool isEnabled();
    vector<Triangle> triangulate(const vector<Vertex>& vertices);

private:
    Triangle superTriangle(const vector<Vertex>& vertices);

    // // Update array of triangles by adding a new vertex
    vector<Triangle> addVertex(Vertex vertex, vector <Triangle>& triangles);
    vector<Edge> uniqueEdges(vector<Edge>& edges);

    bool enabled = false;
};

#endif // CDT_H_INCLUDED
