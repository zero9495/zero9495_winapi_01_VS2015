#include "ListFigure.h"

/*///////////////////////////////////////////////////////
ListElem
*////////////////////////////////////////////////////////

ListElem::ListElem()
{
	data = 0;
	next = 0;
}

ListElem::~ListElem()
{
	delete data;
}

/*///////////////////////////////////////////////////////
ListFigure
*////////////////////////////////////////////////////////

ListFigure::ListFigure()
{
	size = 0;
	begin = 0;
	end = 0;
}

ListFigure::ListFigure(const ListFigure& a)
{
	size = 0;
	begin = 0;
	end = 0;

	ListElem* t = a.begin;

	while (t)
	{
		AddElemToEnd(t->data);
		t = t->next;
	}
}

ListFigure::ListFigure(const Figure& a)
{
	size = 0;
	begin = 0;
	end = 0;
	Figure* r = new Figure(a);
	AddElemToEnd(r);
}

ListFigure::~ListFigure()
{
	Clear();
}

Figure* ListFigure::Copy() const
{
	ListFigure* newt = new ListFigure[1];
	ListElem* t = this->begin;

	while (t)
	{
		newt->AddElemToEnd(t->data);
		t = t->next;
	}

	return newt;
}

void ListFigure::AddElemToEnd(const Figure* a)
{
	ListElem* t = new ListElem;
	t->data = a->Copy();
	t->next = 0;

	if (size == 0)
	{
		begin = t;
		end = t;
	}
	else
	{
		end = end->next = t;
	}

	size++;
}

void ListFigure::AddElemToEnd(const ListFigure* a)
{
	ListElem* t = a->begin;

	while (t)
	{
		this->AddElemToEnd(t->data);
		t = t->next;
	}
}

void ListFigure::DelElem(const Figure* a)
{
	if (begin == 0)
	{
		return;
	}

	if (*(begin->data) == *a)
	{
		ListElem* t1 = begin;
		begin = begin->next;
		delete t1;
		size--;
		return;
	}

	ListElem* t = begin;


	while (t->next)
	{
		if (*(t->next->data) == *a)
		{
			ListElem* t1 = t->next;
			t->next = t->next->next;
			delete t1;
			size--;
			return;
		}
		t = t->next;
	}
}

void ListFigure::Paint(const HDC& hdc) const
{
	ListElem* t = begin;

	while (t)
	{
		t->data->Paint(hdc);
		t = t->next;
	}

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(40, 57, 60));
	SelectObject(hdc, hPen);

	Rectangle(hdc, -50, -50, 50, 50);

	MoveToEx(hdc, 0, 0, NULL);
	LineTo(hdc, 0, 10);
	MoveToEx(hdc, 0, 0, NULL);
	LineTo(hdc, 10, 0);

	DeleteObject(hPen);
}

void ListFigure::Clear()
{
	while (begin) {
		ListElem * next = begin->next;
		delete begin;
		begin = next;
	}
}

int ListFigure::GetSize() const
{
	return size;
}

ListFigure& ListFigure::operator=(const ListFigure& a)
{
	if (this == &a)
	{
		return *this;
	}

	Clear();

	size = 0;
	begin = 0;
	end = 0;

	ListElem* t = a.begin;

	while (t)
	{
		AddElemToEnd(t->data);
		t = t->next;
	}

	return *this;
}