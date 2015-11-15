#pragma once
#include "MyButton.h"

class Sight : public MyButton
{
public:
	Sight(
		const int& givenCenterX,
		const int& givenCenterY);
	~Sight();

	void Paint(const HDC& hdc) const;
	void ChangeSight(int& xWindow, int& yWindow, const int& x1, const int& y1);
	void SetCoordDown(const int& x1, const int& y1);

private:
	int downX;
	int downY;
};


Sight::Sight(
	const int& givenCenterX,
	const int& givenCenterY) : MyButton(
		RGB(40, 57, 60),
		RGB(255, 255, 255),
		givenCenterX,
		givenCenterY,
		30, 30)
{	
}

Sight::~Sight()
{
}

void Sight::Paint(const HDC& hdc) const
{
	HPEN hPen = CreatePen(PS_SOLID, 1, GetPen());
	SelectObject(hdc, hPen);

	MoveToEx(hdc, GetCenterX(), GetCenterY() - 5, NULL);
	LineTo(hdc, GetCenterX(), GetCenterY() - 30);

	MoveToEx(hdc, GetCenterX(), GetCenterY() + 5, NULL);
	LineTo(hdc, GetCenterX(), GetCenterY() + 30);

	MoveToEx(hdc, GetCenterX() - 5, GetCenterY(), NULL);
	LineTo(hdc, GetCenterX() - 30, GetCenterY());

	MoveToEx(hdc, GetCenterX() + 5, GetCenterY(), NULL);
	LineTo(hdc, GetCenterX() + 30, GetCenterY());

	DeleteObject(hPen);
}

void Sight::ChangeSight(int& xWindow, int& yWindow, const int& x1, const int& y1)
{
	xWindow += x1 - downX;
	yWindow += y1 - downY;
	downX = x1;
	downY = y1;
}

void Sight::SetCoordDown(const int& x1, const int& y1)
{
	downX = x1;
	downY = y1;
}