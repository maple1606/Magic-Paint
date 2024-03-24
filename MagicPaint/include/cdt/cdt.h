#pragma once
#ifndef CDT_H_INCLUDED
#define CDT_H_INCLUDED

#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include "shapes.h"
using namespace std;

class CDT {
public:
    vector<Triangle> delaunayTriangulation(const vector<Point>& points);
};

#endif // CDT_H_INCLUDED
