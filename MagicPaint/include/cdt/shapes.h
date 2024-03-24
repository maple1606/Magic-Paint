#pragma once
#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

struct Point {
    float x, y;
    Point(float x_, float y_) : x(x_), y(y_) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

struct Edge {
    Point start, end;
    Edge(Point start_, Point end_) : start(start_), end(end_) {}
};

struct Triangle {
    Point p1, p2, p3;
    Triangle(Point p1_, Point p2_, Point p3_) : p1(p1_), p2(p2_), p3(p3_) {}

    bool operator==(const Triangle& other) const {
        return p1 == other.p1 && p2 == other.p2 && p3 == other.p3;
    }

    bool operator!=(const Triangle& other) const {
        return !(*this == other);
    }
};

#endif // SHAPES_H_INCLUDED
