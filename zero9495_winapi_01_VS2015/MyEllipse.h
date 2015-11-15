#pragma once
#include "Figure.h"

class MyEllipse : public Figure
{
public:
	MyEllipse();
	MyEllipse(const COLORREF& cPen, const COLORREF& cBrush,
		const int& givenLeft, const int& givenTop,
		const int& givenRight, const int& givenBottom);
	MyEllipse(const MyEllipse& a);
	~MyEllipse();

	Figure* Copy() const;
	void Paint(const HDC& hdc) const;
	void Set(const int& left, const int& right, const int& top, const int& bottom);

	MyEllipse& operator=(const Figure& a);
	MyEllipse& operator=(const MyEllipse& a);

	bool operator==(const Figure& a);
	bool operator==(const MyEllipse& a);

private:
	int left;
	int right;
	int top;
	int bottom;
};