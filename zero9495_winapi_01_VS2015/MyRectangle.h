#pragma once
#include "Figure.h"

class MyRectangle : public Figure
{
public:
	MyRectangle();
	MyRectangle(COLORREF cPen, COLORREF cBrush, const int& left, const int& top, const int& right, const int& bottom);
	MyRectangle(const MyRectangle& a);
	~MyRectangle();

	bool IsOnButton(const int& x1, const int& y1) const;
	Figure* Copy() const;
	void Paint(const HDC& hdc) const;
	void SetBottom(const int& givenBottom);

	MyRectangle& operator=(const Figure& a);
	MyRectangle& operator=(const MyRectangle& a);
	bool operator==(const Figure& a);
	bool operator==(const MyRectangle& a);

private:
	int left;
	int right;
	int top;
	int bottom;
};