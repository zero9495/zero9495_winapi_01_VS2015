#include "Figure.h"

/*///////////////////////////////////////////////////////
Figure
*////////////////////////////////////////////////////////

Figure::Figure()
{
	cBrush = RGB(255, 255, 255);
	cPen = RGB(0, 0, 0);

	count++;
}

Figure::Figure(const COLORREF& cP, const COLORREF& cB)
{
	cPen = cP;
	cBrush = cB;

	count++;
}

Figure::Figure(const Figure& a)
{
	cBrush = a.cBrush;
	cPen = a.cPen;

	count++;
}

Figure::~Figure()
{
	count--;
}

Figure* Figure::Copy() const
{
	return new Figure(*this);
}

ostream& operator<<(ostream& os, const Figure& a)
{
	return os;
}

void Figure::Paint(const HDC& hdc) const
{
}

COLORREF Figure::GetPen() const
{
	return cPen;
}

COLORREF Figure::GetBrush() const
{
	return cBrush;
}

Figure& Figure::operator=(const Figure& a)
{
	cBrush = a.cBrush;
	cPen = a.cPen;

	return *this;
}

bool Figure::operator==(const Figure& a)
{
	if ((cBrush != a.cBrush) ||
		(cPen != cPen))
	{
		return false;
	}
	return true;
}