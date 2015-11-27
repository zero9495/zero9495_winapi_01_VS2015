#pragma once
#include "MyButton.h"
#include "ButtonWithText.h"
#include "Arrows.h"
#include "ListFigure.h"

class PanelMenu
{
public:
	PanelMenu();
	PanelMenu(int cyClient);
	~PanelMenu();

	int OnSetMapModeDOWN(int& xWindow,
		int& yWindow,
		const int& posX,
		const int& posY,
		const HDC& hdc);
	POINT OnChangeDirectionDOWN(
		const int& posX,
		const int& posY,
		const HDC& hdc);
	int OnMenuMOVE(
		const int& posX,
		const int& posY,
		const HDC& hdc);
	void OnMenuUP();
	void PanelMenu::Paint(const HDC& hdc) const;
	void AddButton(const MyButton& button);
	void SetCYClient(const int& cyClient);

private:
	ButtonWithText* txt;
	ButtonWithText* isotr;
	ButtonWithText* anisotr;
	Arrows* arrows;
	MyRectangle* rect;
	MyRectangle* smallRect;

	COLORREF Brush = RGB(40, 57, 60);
	COLORREF Pen = RGB(40, 57, 60);
	COLORREF TextColorOn = RGB(238, 238, 238);
	COLORREF TextColorOff = RGB(145, 153, 166);
};

PanelMenu::PanelMenu() : PanelMenu(1000)
{
}

PanelMenu::PanelMenu(int cyClient)
{
	txt = new ButtonWithText(70, 50, "MM_TEXT");
	txt->TurnOn();
	isotr = new ButtonWithText(70, 100, "MM_ISOTROPIC");
	anisotr = new ButtonWithText(70, 150, "MM_ANISOTROPIC");
	arrows = new Arrows(70, 220);
	rect = new MyRectangle(Pen, Brush, 0, 0, 140, cyClient);
	smallRect = new MyRectangle(Pen, RGB(0,0,0), 40, 190, 100, 250);
}

PanelMenu::~PanelMenu()
{
	delete txt;
	delete isotr;
	delete anisotr;
	delete rect;
	delete smallRect;
}

int PanelMenu::OnSetMapModeDOWN(int& xWindow,
	int& yWindow,
	const int& posX,
	const int& posY,
	const HDC& hdc)
{
	if (txt->IsOnButton(posX, posY))
	{
		SetMapMode(hdc, MM_TEXT);

		txt->TurnOn();
		isotr->TurnOff();
		anisotr->TurnOff();

		return MM_TEXT;
	}
	else if (isotr->IsOnButton(posX, posY))
	{
		SetMapMode(hdc, MM_ISOTROPIC);

		txt->TurnOff();
		isotr->TurnOn();
		anisotr->TurnOff();

		return MM_ISOTROPIC;
	}
	else if (anisotr->IsOnButton(posX, posY))
	{
		SetMapMode(hdc, MM_ANISOTROPIC);

		txt->TurnOff();
		isotr->TurnOff();
		anisotr->TurnOn();

		return MM_ANISOTROPIC;
	}

	return 0;
}

POINT PanelMenu::OnChangeDirectionDOWN(
	const int& posX,
	const int& posY,
	const HDC& hdc)
{	
	if (arrows->IsOnButton(posX, posY))
	{
		arrows->TurnOn();
		arrows->ChangeDirection(posX, posY);
	}

	return arrows->GetDirection();
}

int PanelMenu::OnMenuMOVE(
	const int& posX,
	const int& posY,
	const HDC& hdc)
{
	if (arrows->GetState())
	{
		arrows->ChangeDirection(posX, posY);
		return 1;
	}
	return 0;
}

void PanelMenu::OnMenuUP()
{
	arrows->TurnOff();
}

void PanelMenu::Paint(const HDC& hdc) const
{
	rect->Paint(hdc);
	txt->Paint(hdc);
	isotr->Paint(hdc);
	anisotr->Paint(hdc);
	smallRect->Paint(hdc);
	arrows->Paint(hdc);
}

void PanelMenu::AddButton(const MyButton& button)
{
}

void PanelMenu::SetCYClient(const int& cyClient)
{
	rect->SetBottom(cyClient);
}