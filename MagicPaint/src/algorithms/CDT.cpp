#include "CDT.h"

using namespace std;

float distance(const Point& p1, const Point& p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

bool inCircumcircle(const Point& p, const Point& p1, const Point& p2, const Point& p3) {
    float d = (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    float dx = (p.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p.y - p3.y);
    float dy = (p1.x - p3.x) * (p.y - p3.y) - (p.x - p3.x) * (p1.y - p3.y);
    float s = dx * dx + dy * dy;
    return d * s > 0;
}

vector<Triangle> CDT::delaunayTriangulation(const vector<Point>& points) {
    vector<Triangle> triangles;

    float minX = points[0].x, minY = points[0].y;
    float maxX = minX, maxY = minY;
    for (const Point& p : points) {
        minX = min(minX, p.x);
        minY = min(minY, p.y);
        maxX = max(maxX, p.x);
        maxY = max(maxY, p.y);
    }
    float dx = maxX - minX, dy = maxY - minY;
    float deltaMax = max(dx, dy);
    float midx = (minX + maxX) / 2, midy = (minY + maxY) / 2;
    Point p1 = { midx - 20 * deltaMax, midy - deltaMax };
    Point p2 = { midx, midy + 20 * deltaMax };
    Point p3 = { midx + 20 * deltaMax, midy - deltaMax };
    triangles.push_back(Triangle(p1, p2, p3));

    for (int i = 0; i < points.size(); ++i) {
        vector<Triangle> badTriangles;

        for (const auto& t : triangles) {
            const Point& p1 = t.p1;
            const Point& p2 = t.p2;
            const Point& p3 = t.p3;
            if (inCircumcircle(points[i], p1, p2, p3)) {
                badTriangles.push_back(t);
            }
        }
        vector<Edge> polygonEdges;
        for (const auto& t : badTriangles) {
            for (int j = 0; j < 3; ++j) {
                int nextIndex = (j + 1) % 3;
                bool sharedEdge = false;
                for (const auto& t2 : badTriangles) {
                    if (t != t2 && (t.p1 == t2.p1 && t.p2 == t2.p2) || (t.p2 == t2.p1 && t.p3 == t2.p2) ||
                        (t.p3 == t2.p1 && t.p1 == t2.p2)) {
                        sharedEdge = true;
                        break;
                    }
                }
                if (!sharedEdge) {
                    polygonEdges.push_back(Edge(t.p1, t.p2));
                }
            }
        }
        for (const auto& t : badTriangles) {
            triangles.erase(remove(triangles.begin(), triangles.end(), t), triangles.end());
        }
        for (const auto& e : polygonEdges) {
            triangles.push_back({ e.start, e.end, points[i] });
        }
    }
    vector<Triangle> result;

    for (const auto& t : triangles) {
        if (t.p1 != p1 && t.p1 != p2 && t.p1 != p3 && t.p2 != p1 && t.p2 != p2 && t.p2 != p3 &&
            t.p3 != p1 && t.p3 != p2 && t.p3 != p3) {
            result.push_back(t);
        }
    }
    return result;
}