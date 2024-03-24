#include "CDT.h"
#include <iostream>

using namespace std;

const bool CDT::isEnabled() {
    return enabled;
}

void CDT::display() {
    ImGui::NewLine();
    ImGui::Checkbox("Show CDT", &enabled);
}

Triangle CDT::superTriangle(const vector<Vertex>& vertices) {
    float minX = vertices[0].x, minY = vertices[0].y;
    float maxX = minX, maxY = minY;
    for (const Vertex& v : vertices) {
        minX = min(minX, v.x);
        minY = min(minY, v.y);
        maxX = max(maxX, v.x);
        maxY = max(maxY, v.y);
    }

    float dx = (maxX - minX) * 10, dy = (maxY - minY) * 10;
    Vertex v1 = { minX - dx, minY - dy };
    Vertex v2 = { minX - dx, maxY + dy };
    Vertex v3 = { maxX + dx, maxY + dy };

    return Triangle(v1, v2, v3);
}
vector<Edge> CDT::uniqueEdges(vector<Edge>& edges) {
    vector<Edge> uniqueEdges;
    for (int i = 0; i < edges.size(); i++) {
        bool isUnique = true;

        for (int j = 0; j < edges.size(); ++j) {
            if (i != j && edges[i] == edges[j]) {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
            uniqueEdges.push_back(edges[i]);
    }

    return uniqueEdges;
}

vector<Triangle> CDT::addVertex(Vertex vertex, vector<Triangle>& triangles) {
    vector<Edge> edges;

    vector<Triangle> trianglesToRemove;
    for (auto& t : triangles) {
        if (t.inCircumCirc(vertex)) {
            edges.emplace_back(t.v1, t.v2);
            edges.emplace_back(t.v2, t.v3);
            edges.emplace_back(t.v3, t.v1);
            trianglesToRemove.push_back(t);
        }
    }
    for (const auto& t : trianglesToRemove) {
        triangles.erase(remove(triangles.begin(), triangles.end(), t), triangles.end());
    }

    edges = uniqueEdges(edges);

    for (const auto& e : edges) {
        triangles.push_back(Triangle(e.start, e.end, vertex));
    }

    return triangles;
}

vector<Triangle> CDT::triangulate(const vector<Vertex>& vertices) {
    vector<Triangle> triangles;

    Triangle _superTriangle = superTriangle(vertices);

    triangles.push_back(_superTriangle);

    for (const auto &v : vertices) {
        triangles = addVertex(v, triangles);
    }

    vector<Triangle> result;

    for (const auto& t : triangles) {
        if (t.v1 != _superTriangle.v1 && t.v1 != _superTriangle.v2 && t.v1 != _superTriangle.v3 
            && t.v2 != _superTriangle.v1 && t.v2 != _superTriangle.v2 && t.v2 != _superTriangle.v3 
            && t.v3 != _superTriangle.v1 && t.v3 != _superTriangle.v2 && t.v3 != _superTriangle.v3) {
            result.push_back(t);
        }
    }

    return result;
}