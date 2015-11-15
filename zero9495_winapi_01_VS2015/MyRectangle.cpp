/*///////////////////////////////////////////////////////
MyRectangle
*////////////////////////////////////////////////////////

#include "MyRectangle.h"

MyRectangle::MyRectangle()
{
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
}

MyRectangle::MyRectangle(COLORREF cP, COLORREF cB,
	const int& givenLeft, const int& givenTop,
	const int& givenRight, const int& givenBottom) : Figure(cP, cB)
{
	left = givenLeft;
	right = givenRight;
	top = givenTop;
	bottom = givenBottom;
}

MyRectangle::MyRectangle(const MyRectangle& a) : Figure(a.GetPen(), a.GetBrush())
{
	left = a.left;
	right = a.right;
	top = a.top;
	bottom = a.bottom;
}

MyRectangle::~MyRectangle()
{
}

bool MyRectangle::IsOnButton(const int& x1, const int& y1) const
{
	if ((top < y1) && (y1 < bottom) &&
		(left < x1) && (x1 < right))
	{
		return true;
	}
	return false;
}

Figure* MyRectangle::Copy() const
{
	return new MyRectangle(*this);
}

void MyRectangle::Paint(const HDC& hdc) const
{
	HBRUSH hBrush = CreateSolidBrush(GetBrush());
	HPEN hPen = CreatePen(PS_SOLID, 1, GetPen());
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);

	Rectangle(hdc, left, top, right, bottom);

	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void MyRectangle::SetBottom(const int& givenBottom)
{
	bottom = givenBottom;
}

MyRectangle& MyRectangle::operator=(const Figure& a)
{
	const MyRectangle* ptr = dynamic_cast<const MyRectangle*>(&a);

	if (!ptr)
	{
		_DEBUG_ERROR("Попытка присвоить объекту класса MyRectangle, объект другого класса");
	}
	else
	{
		*this = *ptr;
	}
	return *this;
}

MyRectangle& MyRectangle::operator=(const MyRectangle& a)
{
	left = a.left;
	right = a.right;
	top = a.top;
	bottom = a.bottom;
	return *this;
}

bool MyRectangle::operator==(const Figure& a)
{
	const MyRectangle* ptr = dynamic_cast<const MyRectangle*>(&a);

	if (!ptr)
	{
		_DEBUG_ERROR("Попытка присвоить объекту класса MyRectangle, объект другого класса");
	}
	else
	{
		return (*this == *ptr);
	}
	return false;
}

bool MyRectangle::operator==(const MyRectangle& a)
{
	if ((left != a.left) ||
		(right != a.right) ||
		(top != a.top) ||
		(bottom != a.bottom))
	{
		return false;
	}
	return true;
}