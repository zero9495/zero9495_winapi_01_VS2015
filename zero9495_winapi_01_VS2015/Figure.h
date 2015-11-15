#pragma once
#include <windows.h>
#include <iostream>
using namespace std;

class Figure
{
public:
	Figure();
	Figure(const COLORREF& cPen, const COLORREF& cBrush);
	Figure(const Figure& a);
	virtual ~Figure();

	static int count;

	virtual Figure* Copy() const;
	virtual void Paint(const HDC& hdc) const;
	COLORREF GetPen() const;
	COLORREF GetBrush() const;

	Figure& operator=(const Figure& a);
	bool operator==(const Figure& a);
private:
	COLORREF cBrush;
	COLORREF cPen;
};