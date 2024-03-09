#pragma once

struct Color {
	float r, g, b;
	float a;

	bool operator==(const Color& other) const {
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	bool operator!=(const Color& other) const {
		return !(*this == other);
	}
};