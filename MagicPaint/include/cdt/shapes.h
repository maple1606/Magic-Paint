#pragma once
#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <string>

using namespace std;

struct Vertex {
    float x, y;
    Vertex(float x_, float y_) : x(x_), y(y_) {}

    bool operator==(const Vertex& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vertex& other) const {
        return !(*this == other);
    }

    string to_string() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

struct Edge {
    Vertex start, end;
    Edge(Vertex start_, Vertex end_) : start(start_), end(end_) {}

    bool operator==(const Edge& other) const {
        return start == other.start && end == other.end;
    }

    bool operator!=(const Edge& other) const {
        return !(*this == other);
    }

    string to_string() const {
        return "[" + start.to_string() + ", " + end.to_string() + "]";
    }
};

struct Triangle {
    Vertex v1, v2, v3;
    Triangle(Vertex v1_, Vertex v2_, Vertex v3_) : v1(v1_), v2(v2_), v3(v3_) {}

    bool operator==(const Triangle& other) const {
        return v1 == other.v1 && v2 == other.v2 && v3 == other.v3;
    }

    bool operator!=(const Triangle& other) const {
        return !(*this == other);
    }

    pair<Vertex, float> circumCirc() {

        float D = 4 * (v1.x - v2.x) * (v1.y - v3.y) - 4 * (v1.x - v3.x) * (v1.y - v2.y);
        float Dx = 2 * (v1.x * v1.x + v1.y * v1.y - v2.x * v2.x - v2.y * v2.y) * (v1.y - v3.y)
            - 2 * (v1.x * v1.x + v1.y * v1.y - v3.x * v3.x - v3.y * v3.y) * (v1.y - v2.y);
        float Dy = 2 * (v1.x * v1.x + v1.y * v1.y - v3.x * v3.x - v3.y * v3.y) * (v1.x - v2.x)
            - 2 * (v1.x * v1.x + v1.y * v1.y - v2.x * v2.x - v2.y * v2.y) * (v1.x - v3.x);

        float centerX = Dx / D;
        float centerY = Dy / D;

        Vertex center(centerX, centerY);
        float radius = sqrt((v1.x - centerX) * (v1.x - centerX) +
                    (v1.y - centerY) * (v1.y - centerY));

        return make_pair(center, radius);
    }

    bool inCircumCirc(Vertex v) {
        pair <Vertex, float> _circumCirc = this->circumCirc();
        float dx = _circumCirc.first.x - v.x;
        float dy = _circumCirc.first.y - v.y;
        
        return sqrt(dx * dx + dy * dy) <= _circumCirc.second;
    }
};

#endif // SHAPES_H_INCLUDED
