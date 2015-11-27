#pragma once
#include <Windows.h>

class Workspace
{
public:
	Workspace();
	Workspace(const int& tLeft, const int& tTop, const int& tRight, const int& tBottom);
	~Workspace();

	void ChangeSize(const int& tRight, const int& tBottom);
	void Clear(HDC hdc,
		const int& xViewExt,
		const int& yViewExt,
		const int& xWinExt,
		const int& yWinExt);

private:
	int left;
	int top;
	int right;
	int bottom;
};

Workspace::Workspace()
{

}

Workspace::Workspace(const int& tLeft, const int& tTop, const int& tRight, const int& tBottom)
{
	left = tLeft;
	top = tTop;
	right = tRight;
	bottom = tBottom;
}

Workspace::~Workspace()
{

}

void Workspace::ChangeSize(const int& tRight, const int& tBottom)
{
	right = tRight;
	bottom = tBottom;
}

void Workspace::Clear(HDC hdc,
	const int& xViewExt,
	const int& yViewExt,
	const int& xWinExt,
	const int& yWinExt)
{
	int k = GetMapMode(hdc);
	POINT FAR* lppt = new POINT FAR;
	GetViewportOrgEx(hdc, lppt);
	SetViewportOrgEx(hdc, 0, 0, NULL);

	SetMapMode(hdc, MM_TEXT);

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);

	Rectangle(hdc, left, top, right, bottom);

	DeleteObject(hBrush);
	DeleteObject(hPen);

	SetViewportOrgEx(hdc, lppt->x, lppt->y, NULL);
	SetMapMode(hdc, k);
	SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
	SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
	delete lppt;
}