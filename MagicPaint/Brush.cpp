#include "Brush.h"
#include<iostream>

Brush::Brush(Color** colors) {
	this->colors = colors;
}

void Brush::setColor(int x, int y, Color color) {
	struct Color newColor = { color.r, color.g, color.b, color.a };
	colors[x][y] = newColor;
}

Color Brush::getColor(int x, int y) {
	return colors[x][y];
}