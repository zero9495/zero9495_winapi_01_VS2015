/*///////////////////////////////////////////////////////
MyEllipse
*////////////////////////////////////////////////////////

#include "MyEllipse.h"

MyEllipse::MyEllipse()
{
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
}

MyEllipse::MyEllipse(const COLORREF& cPen, const COLORREF& cBrush,
	const int& givenLeft, const int& givenTop,
	const int& givenRight, const int& givenBottom) : Figure(cPen, cBrush)
{
	left = givenLeft;
	right = givenRight;
	top = givenTop;
	bottom = givenBottom;
}

MyEllipse::MyEllipse(const MyEllipse& a) : Figure(a.GetPen(), a.GetBrush())
{
	left = a.left;
	right = a.right;
	top = a.top;
	bottom = a.bottom;
}

MyEllipse::~MyEllipse()
{
}

Figure* MyEllipse::Copy() const
{
	return new MyEllipse(*this);
}

void MyEllipse::Paint(const HDC& hdc) const
{
	HBRUSH hBrush = CreateSolidBrush(GetBrush());
	HPEN hPen = CreatePen(PS_SOLID, 1, GetPen());
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);

	Ellipse(hdc, left, top, right, bottom);

	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void MyEllipse::Set(const int& givenLeft, const int& givenTop,
	const int& givenRight, const int& givenBottom)
{
	left = givenLeft;
	right = givenRight;
	top = givenTop;
	bottom = givenBottom;
}

MyEllipse& MyEllipse::operator=(const Figure& a)
{
	const MyEllipse* ptr = dynamic_cast<const MyEllipse*>(&a);

	if (!ptr)
	{
		_DEBUG_ERROR("Попытка присвоить объекту класса MyEllipse, объект другого класса");
	}
	else
	{
		*this = *ptr;
	}
	return *this;
}

MyEllipse& MyEllipse::operator=(const MyEllipse& a)
{
	left = a.left;
	right = a.right;
	top = a.top;
	bottom = a.bottom;
	return *this;
}

bool MyEllipse::operator==(const Figure& a)
{
	const MyEllipse* ptr = dynamic_cast<const MyEllipse*>(&a);

	if (!ptr)
	{
		_DEBUG_ERROR("Попытка присвоить объекту класса MyEllipse, объект другого класса");
	}
	else
	{
		return (*this == *ptr);
	}
	return false;
}

bool MyEllipse::operator==(const MyEllipse& a)
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