/*///////////////////////////////////////////////////////
MyTriangle
*////////////////////////////////////////////////////////

#include "MyTriangle.h"

MyTriangle::MyTriangle()
{
	poly[0].x = 0;	poly[0].y = 0;
	poly[1].x = 0;	poly[1].y = 0;
	poly[2].x = 0;	poly[2].y = 0;
}

MyTriangle::MyTriangle(COLORREF cP, COLORREF cB,
	const int& givenx1, const int& giveny1,
	const int& givenx2, const int& giveny2,
	const int& givenx3, const int& giveny3) : Figure(cP, cB)
{
	poly[0].x = givenx1;	poly[0].y = giveny1;
	poly[1].x = givenx2;	poly[1].y = giveny2;
	poly[2].x = givenx3;	poly[2].y = giveny3;
}

MyTriangle::MyTriangle(const MyTriangle& a) : Figure(a.GetPen(), a.GetBrush())
{
	poly[0].x = a.poly[0].x;	poly[0].y = a.poly[0].y;
	poly[1].x = a.poly[1].x;	poly[1].y = a.poly[1].y;
	poly[2].x = a.poly[2].x;	poly[2].y = a.poly[2].y;
}

MyTriangle::~MyTriangle()
{
}

Figure* MyTriangle::Copy() const
{
	return new MyTriangle(*this);
}

void MyTriangle::Paint(const HDC& hdc) const
{
	HBRUSH hBrush = CreateSolidBrush(GetBrush());
	HPEN hPen = CreatePen(PS_SOLID, 1, GetPen());
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);

	Polygon(hdc, poly, 3);

	DeleteObject(hBrush);
	DeleteObject(hPen);
}

MyTriangle& MyTriangle::operator=(const Figure& a)
{
	const MyTriangle* ptr = dynamic_cast<const MyTriangle*>(&a);

	if (!ptr)
	{
		_DEBUG_ERROR("Попытка присвоить объекту класса MyTriangle, объект другого класса");
	}
	else
	{
		*this = *ptr;
	}
	return *this;
}

MyTriangle& MyTriangle::operator=(const MyTriangle& a)
{
	poly[0].x = a.poly[0].x;	poly[0].y = a.poly[0].y;
	poly[1].x = a.poly[1].x;	poly[1].y = a.poly[1].y;
	poly[2].x = a.poly[2].x;	poly[2].y = a.poly[2].y;
	return *this;
}

bool MyTriangle::operator==(const Figure& a)
{
	const MyTriangle* ptr = dynamic_cast<const MyTriangle*>(&a);

	if (!ptr)
	{
		_DEBUG_ERROR("Попытка присвоить объекту класса MyTriangle, объект другого класса");
	}
	else
	{
		return (*this == *ptr);
	}
	return false;
}

bool MyTriangle::operator==(const MyTriangle& a)
{
	if ((poly[0].x = a.poly[0].x) || (poly[0].y = a.poly[0].y) ||
		(poly[1].x = a.poly[1].x) || (poly[1].y = a.poly[1].y) ||
		(poly[2].x = a.poly[2].x) || (poly[2].y = a.poly[2].y))
	{
		return false;
	}
	return true;
}