#pragma once
#include "Figure.h"

class MyTriangle : public Figure
{
public:
	MyTriangle();
	MyTriangle(COLORREF cPen, COLORREF cBrush,
		const int& x1, const int& y1,
		const int& x2, const int& y2,
		const int& x3, const int& y3);
	MyTriangle(const MyTriangle& a);
	~MyTriangle();

	Figure* Copy() const;
	void Paint(const HDC& hdc) const;

	MyTriangle& operator=(const Figure& a);
	MyTriangle& operator=(const MyTriangle& a);

	bool operator==(const Figure& a);
	bool operator==(const MyTriangle& a);

private:
	POINT poly[3];
};