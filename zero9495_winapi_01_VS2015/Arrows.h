#pragma once
#include "ListFigure.h"
#include "MyButton.h"

class Arrows : public MyButton
{
public:
	Arrows(
		const int& givenCenterX,
		const int& givenCenterY);
	~Arrows();

	void Paint(const HDC& hdc) const;
	void ChangeDirection(const int& x1, const int& y1);
	POINT GetDirection();

private:
	int dirX;
	int dirY;

	int CenterX;
	int CenterY;
};

Arrows::Arrows(
	const int& givenCenterX,
	const int& givenCenterY) : MyButton(
		RGB(40, 57, 60),
		RGB(255, 255, 255),
		givenCenterX,
		givenCenterY,
		40,	40)
{	
	dirX = 3;
	dirY = 6;

	CenterX = givenCenterX;
	CenterY = givenCenterY;
}

Arrows::~Arrows()
{
}

void DrawArrow(HDC hdc, int x, int y, int oclock, const COLORREF& pen)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, pen);
	SelectObject(hdc, hPen);

	MoveToEx(hdc, x, y, NULL);

	switch (oclock)
	{
	case 12:
	{
		LineTo(hdc, x, y - 30);
		LineTo(hdc, x - 5, y - 25);
		LineTo(hdc, x, y - 30);
		LineTo(hdc, x + 5, y - 25);
		break;
	}
	case 3:
	{
		LineTo(hdc, x + 30, y);
		LineTo(hdc, x + 25, y - 5);
		LineTo(hdc, x + 30, y);
		LineTo(hdc, x + 25, y + 5);
		break;
	}
	case 6:
	{
		LineTo(hdc, x, y + 30);
		LineTo(hdc, x - 5, y + 25);
		LineTo(hdc, x, y + 30);
		LineTo(hdc, x + 5, y + 25);
		break;
	}
	case 9:
	{
		LineTo(hdc, x - 30, y);
		LineTo(hdc, x - 25, y - 5);
		LineTo(hdc, x - 30, y);
		LineTo(hdc, x - 25, y + 5);
		break;
	}
	}

	DeleteObject(hPen);
}

void Arrows::Paint(const HDC& hdc) const
{
	DrawArrow(hdc,
		GetCenterX(), 
		GetCenterY(), 
		dirX, GetPen());
	DrawArrow(hdc, 
		GetCenterX(), 
		GetCenterY(), 
		dirY, GetPen());
}

void Arrows::ChangeDirection(const int& x1, const int& y1)
{
	if (x1 > CenterX)
	{
		if (y1 > CenterY)
		{
			dirX = 3;
			dirY = 6;
		}
		else
		{
			dirX = 3;
			dirY = 12;
		}
	}
	else
	{
		if (y1 > CenterY)
		{
			dirX = 9;
			dirY = 6;
		}
		else
		{
			dirX = 9;
			dirY = 12;
		}
	}
}

POINT Arrows::GetDirection()
{
	POINT direction;
	direction.x = dirX;
	direction.y = dirY;
	return direction;
}