#pragma once
#include "MyButton.h"

class ButtonWithText : public MyButton
{
public:
	ButtonWithText(
		const int& givenCenterX,
		const int& givenCenterY,
		const char* givenStr,
		const int& givenHeight,
		const int& givenWidth);
	~ButtonWithText();

	void Paint(const HDC& hdc) const;

private:
	char* str;

	COLORREF textColorOn = RGB(238, 238, 238);
	COLORREF textColorOff = RGB(145, 153, 166);
};

ButtonWithText::ButtonWithText(
	const int& givenCenterX,
	const int& givenCenterY,
	const char* givenStr,
	const int& givenHeight = 50,
	const int& givenWidth = 140) : MyButton(
		RGB(40, 57, 60),
		RGB(40, 57, 60),
		givenCenterX,
		givenCenterY,
		givenHeight,
		givenWidth)
{


	int lengthStr = strlen(givenStr);
	str = new char[lengthStr + 1];
	strcpy_s(str, lengthStr + 1, givenStr);
}

ButtonWithText::~ButtonWithText()
{
	delete[] str;
}

void ButtonWithText::Paint(const HDC& hdc) const
{
	this->MyButton::Paint(hdc);
	int k = GetMapMode(hdc);
	SetMapMode(hdc, MM_TEXT);

	CHOOSEFONT cf;
	static LOGFONT lf;
	lf.lfHeight = -15;
	lf.lfWeight = 400;
	lf.lfOutPrecision = 3;
	lf.lfClipPrecision = 2;
	lf.lfQuality = 1;
	lf.lfPitchAndFamily = 34;
	strcpy_s(lf.lfFaceName, sizeof("Corbel"), "Corbel");

	HFONT hFont = CreateFontIndirect(&lf); //Cоздали шрифт
	SelectObject(hdc, hFont); //Он будет иметь силу только когда мы его выберем

	if (GetState() == true)
	{
		SetTextColor(hdc, textColorOn); //зададим цвет текста
	}
	else
	{
		SetTextColor(hdc, textColorOff);
	}

	SetBkColor(hdc, GetBrush()); //зададим цвет фона
	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
	TextOut(
		hdc, 
		GetCenterX(), 
		GetCenterY() + 4, 
		str, 
		strlen(str)); //выведем текст

	SetMapMode(hdc, k);
}