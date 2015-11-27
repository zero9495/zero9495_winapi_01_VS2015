#pragma once
#include <iostream>
#include <Windows.h>
#include "ListFigure.h"
using namespace std;

class MyButton
{
public:
	MyButton();
	MyButton(
		const COLORREF& brush,
		const COLORREF& pen,
		const int& givenCenterX,
		const int& givenCenterY,
		const int& givenHeight,
		const int& givenWidth);
	virtual ~MyButton();

	void TurnOn();
	void TurnOff();

	bool GetState() const;
	int GetCenterX() const;
	int GetCenterY() const;
	COLORREF GetBrush() const;
	COLORREF GetPen() const;
	
	bool IsOnButton(
		const int& posX, 
		const int& posY) const;
	virtual void Paint(const HDC& hdc) const;

private:
	int centerX;
	int centerY;
	
	MyRectangle* fillButton;
	int height;
	int width;

	COLORREF brush;
	COLORREF pen;

	bool state;	
};

MyButton::MyButton()
{
	brush = RGB(40, 57, 60);
	pen = RGB(40, 57, 60);

	centerX = 0;
	centerY = 0;

	fillButton = new MyRectangle(
		brush, brush, 
		centerX - width / 2, centerY - height / 2, 
		centerX + width / 2, centerY + height / 2);	

	state = false;
}

MyButton::MyButton(
	const COLORREF& givenBrush,
	const COLORREF& givenPen,
	const int& givenCenterX,
	const int& givenCenterY,
	const int& givenHeight,
	const int& givenWidth)
{
	brush = givenBrush;
	pen = givenPen;

	centerX = givenCenterX;
	centerY = givenCenterY;
	height = givenHeight;
	width = givenWidth;

	fillButton = new MyRectangle(
		brush, brush,
		centerX - width / 2, centerY - height / 2,
		centerX + width / 2, centerY + height / 2);

	state = false;
}

MyButton::~MyButton()
{
	delete fillButton;
}

void MyButton::TurnOn()
{
	state = true;
}

void MyButton::TurnOff()
{
	state = false;
}

bool MyButton::GetState() const
{
	return state;
}

int MyButton::GetCenterX() const
{
	return centerX;
}

int MyButton::GetCenterY() const
{
	return centerY;
}

COLORREF MyButton::GetBrush() const
{
	return brush;
}

COLORREF MyButton::GetPen() const
{
	return pen;
}

bool MyButton::IsOnButton(const int& givenx, const int& giveny) const
{
	/*if ((centerX - width / 2 < givenx) && (givenx < centerX + width / 2) &&
		(centerY - height / 2 < giveny) && (giveny < centerY + height / 2))*/
	if (fillButton->IsOnButton(givenx, giveny))		
	{
		return true;
	}
	return false;
}

void MyButton::Paint(const HDC& hdc) const
{
	fillButton->Paint(hdc);
}