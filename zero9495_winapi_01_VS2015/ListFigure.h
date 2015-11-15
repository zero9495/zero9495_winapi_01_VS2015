#pragma once
#include "Figure.h"
#include "MyEllipse.h"
#include "MyRectangle.h"
#include "MyTriangle.h"

class ListElem
{
public:
	ListElem();
	~ListElem();

	Figure* data;

	ListElem* next;
};

class ListFigure : public Figure
{
public:
	ListFigure();
	ListFigure(const ListFigure& a);
	ListFigure(const Figure& a);
	~ListFigure();

	Figure* Copy() const;
	void AddElemToEnd(const Figure* a);
	void AddElemToEnd(const ListFigure* a);
	void DelElem(const Figure* a);
	void Paint(const HDC& hdc) const;
	void Clear();
	int GetSize() const;

	ListFigure& operator=(const ListFigure& a);

private:
	ListElem* begin;
	ListElem* end;
	int size;
};