#include "Brush.h"
#include<iostream>

Brush::Brush(Color** colors) {
	this->colors = colors;
}

void Brush::setColor(int x, int y, float r, float g, float b, float a) {
	struct Color newColor = { r, g, b, a };
	colors[x][y] = newColor;
	glBegin(GL_POINTS);
	glColor3f(colors[x][y].r, colors[x][y].g, colors[x][y].b);
	glVertex2f(x, y); 
	std::cout << x << " " << y << " set to black\n";
	glEnd();

}

Color Brush::getColor(int x, int y) {
	return colors[x][y];
}