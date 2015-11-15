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

	void OnMenuDOWN(
		ListFigure* a,
		ListFigure* b,
		int& xWindow,
		int& yWindow,
		const int& posX,
		const int& posY,
		const HDC& hdc);
	void OnMenuMOVE(
		ListFigure* b,
		int& xWindow,
		int& yWindow,
		int& cxClient, 
		int& cyClient,
		const int& posX,
		const int& posY,
		const HDC& hdc);
	void OnMenuUP();
	void Paint(const HDC& hdc) const;
	void AddButton(const MyButton& button);
	void SetCYClient(const int& cyClient);

private:
	ButtonWithText* txt;
	ButtonWithText* isotr;
	ButtonWithText* anisotr;
	Arrows* arrows;
	Sight* sight;
	MyRectangle* rect;

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
	//txt->TurnOn();
	isotr = new ButtonWithText(70, 100, "MM_ISOTROPIC");
	anisotr = new ButtonWithText(70, 150, "MM_ANISOTROPIC");
	arrows = new Arrows(35, 300);
	sight = new Sight(100, 300);
	rect = new MyRectangle(Pen, Brush, 0, 0, 140, cyClient);
}

PanelMenu::~PanelMenu()
{
	delete txt;
	delete isotr;
	delete anisotr;
}

void PanelMenu::OnMenuDOWN(
	ListFigure* a,
	ListFigure* b,
	int& xWindow,
	int& yWindow,
	const int& posX,
	const int& posY,
	const HDC& hdc)
{
	if (txt->IsOnButton(posX, posY))
	{
		SetMapMode(hdc, MM_TEXT);
		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		ListFigure* t = new ListFigure(*a);
		b->AddElemToEnd(t);
		b->Paint(hdc);

		txt->TurnOn();
		isotr->TurnOff();
		anisotr->TurnOff();
	}
	else if (isotr->IsOnButton(posX, posY))
	{
		SetMapMode(hdc, MM_ISOTROPIC);
		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		ListFigure* t = new ListFigure(*a);
		b->AddElemToEnd(t);
		b->Paint(hdc);

		txt->TurnOff();
		isotr->TurnOn();
		anisotr->TurnOff();
	}
	else if (anisotr->IsOnButton(posX, posY))
	{
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		ListFigure* t = new ListFigure(*a);
		b->AddElemToEnd(t);
		b->Paint(hdc);

		txt->TurnOff();
		isotr->TurnOff();
		anisotr->TurnOn();
	}
	else if (arrows->IsOnButton(posX, posY))
	{
		arrows->TurnOn();
		arrows->ChangeDirection(posX, posY);
	}
	else if (sight->IsOnButton(posX, posY))
	{
		sight->TurnOn();
		sight->SetCoordDown(posX, posY);
	}
}

void PanelMenu::OnMenuMOVE(
	ListFigure* b,
	int& xWindow,
	int& yWindow,
	int& cxClient,
	int& cyClient,
	const int& posX,
	const int& posY,
	const HDC& hdc)
{
	if (arrows->GetState())
	{
		arrows->ChangeDirection(posX, posY);
		arrows->Paint(hdc);
	}
	else if (sight->GetState())
	{
		sight->ChangeSight(xWindow, yWindow, posX, posY);
		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);

		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);

		Rectangle(hdc, 140 - xWindow, -yWindow, cxClient, cyClient);
		
		DeleteObject(hBrush);
		DeleteObject(hPen);

		b->Paint(hdc);
		Paint(hdc);
	}
}

void PanelMenu::OnMenuUP()
{
	arrows->TurnOff();
	sight->TurnOff();
}

void PanelMenu::Paint(const HDC& hdc) const
{
	int k = GetMapMode(hdc);
	POINT FAR* lppt = new POINT FAR;
	GetViewportOrgEx(hdc, lppt);
	SetViewportOrgEx(hdc, 0, 0, NULL);

	SetMapMode(hdc, MM_TEXT);
	
	rect->Paint(hdc);
	txt->Paint(hdc);
	isotr->Paint(hdc);
	anisotr->Paint(hdc);
	arrows->Paint(hdc);
	//sight->Paint(hdc);

	SetViewportOrgEx(hdc, lppt->x, lppt->y, NULL);
	SetMapMode(hdc, k);	
	delete lppt;
}

void PanelMenu::AddButton(const MyButton& button)
{
}

void PanelMenu::SetCYClient(const int& cyClient)
{
	rect->SetBottom(cyClient);
}