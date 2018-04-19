#pragma once

struct Color
{
	float red;
	float green;
	float blue;
};

struct Point
{
	int x, y;
	Point() : x(0), y(0) {}
	Point(int x, int y) : x(x), y(y) {}
};