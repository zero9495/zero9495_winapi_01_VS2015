/*///////////////////////////////////////////////////////////////////////////////////////

08.11.2015 -  1768 �����


������� �� ���������������� ��� Win32, 3 ����

1.��������� 20 ����� (�������������,�����������,���������������) � ����.���������� �
���� ������������.

2.�� �� � ������� MM_ISOTROPIC,MM_ANISOTROPIC.

3.�� ��, ������ ����������� �� ������� : ����� ������ ����-�������������,
������-����������.

4.�� ��,�� ��� �� �������� ������� �����-�����������.��� ���� �� ������
��������� ������������� � ���� �� �����.

5.�� ��, � �����������, ��������� o,t,p.

6.��������� ������ - �������������� ��������������.

7.�� ��, �� �����������.������ ��������� 1500*1000.

8. ������� � ����.

9.���������� � ���� ��������� ����������� ���� (edit, listbox, combobox, button)
� ������������ ����� ���� �������� ����������. ������ ��������� ��������������.

10.���������� ��� ���� ����������� ������ � ������.

11.������� � ���� ���� � �������� "����������" , "�������������", "�����������".
�� ������ ���������������� ������ ������� ����� ������ ���� ������ ��������
��������������� ������.

12.�� �� � �������  toolbar. ������� ����� ������ ������������ � statusbar.
����������� ��������� � ������� toolbar. ��������� ��������� � �������� "����-���".

13.������� � ���� ������� �����.

14.����������� ��������� WM_PAINT � ������� ������������ ������ (offscreen).

15. ������ � �������� ������� � ������� DIB. ������ �� ����� .bmp, ����� � ����
� ���������� ������� ����� DIB � �����.

16.�� ������ ���� ������� ������ � ������� ������� ���� (4-5 ����).
����� ������ ������� ����� �������� � ����.

17.����������� ������� (����� �����, �����, ������).
������ ��������� ��������������.

18.������ � ���������� trackbar , up-down, progressbar, animation.
������ ��������� ��������������.

19.������ � listview. ����������, �������� � ����� ��������. ����������� �����
����������.

20.������������� - ������ � treeview .

21.������������� - property sheet, tab control.


22.����������� ����������� ���� � Clipboard � ������� � ���� �� Clipboard.

23. GDI+
*//////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h> // ������������ ����, ���������� ������� API
#include "ListFigure.h"
//#include <vld.h>
#include "Sight.h"
#include "PanelMenu.h"
//#include <gdiplus.h>
//#pragma comment(lib, "gdiplus.lib")
//using namespace Gdiplus;

int Figure::count = 0;

HINSTANCE hInst; //���������� ���������� ����������. �� ����� handle instance
char szAppName[] = "zero9495_winapi_01";
char szAppTitle[] = "zero9495_winapi_01";

/*
��������������� ���� ������ ������������ � ��������� ��������.
� ���������, ���������, ��������� ����, ������������ ��� ������ �
�������� ��������� ������ ������� ��������� ������ ����:

LRESULT CALLBACK ����������(HWND hWnd, UINT uMSg, WPARAM wParam, LPARAM lParam);

������ � ������ �������� ����� � ��������� ��������.
LPARAM � ��� ��� �������� lParam (long parameter). ������������ ������ � wparam � ��������� ��������.
LRESULT � ��������, ������������ ������� ���������� ����� ��� long.
WPARAM � ��� ��� �������� wParam (word parameter). ������������ ������ � lParam � ��������� ��������.
*/
LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �������� ������� - ������ int main() � ���������� ����������:
int APIENTRY WinMain(HINSTANCE hInstance, // ���������� ���������� ����������
	HINSTANCE hPrevInstance, // � Win32 �� ������������
	LPSTR lpCmdLine, // ����� ��� ������� ���� � ������ ��������� ������
	int nCmdShow) // ����� ����������� ����
{
	WNDCLASSEX wc; // ������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
	HWND hWnd; // ������ ���������� �������� ������
	MSG msg;

	hInst = hInstance;
	wc.cbSize = sizeof(wc); // �������� ��������� (� ������)
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���������� ������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // .... ������� ����
	wc.style = NULL; // ����� ������ ������
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���������� ����� ����
	wc.lpszMenuName = NULL; // ��������� �� const-������, ���������� ��� ����, ������������ ��� ������
	wc.lpszClassName = szAppName; // ��������� �� const-������, ���������� ��� ������
	wc.lpfnWndProc = (WNDPROC)WndProc; //��������� �� ������� ���������
	wc.cbClsExtra = 0; // ����� ������������� ������ ��� �������� ���������� ����������
	wc.cbWndExtra = 0; // ����� ������������� ������ � ����� ���������
	wc.hIconSm = 0;

	if (!RegisterClassEx(&wc))
	{
		// � ������ ���������� ����������� ������:
		MessageBox(NULL, "�� ���������� ���������������� �����!", "������", MB_OK);
		return NULL; // ����������, �������������, ������� �� WinMain
	}

	hWnd = CreateWindow(szAppName, // ��� ������
		szAppTitle, // ��� ���� (�� ��� ������)
		WS_OVERLAPPEDWINDOW, // ������ ����������� ������
		CW_USEDEFAULT, // ��������� ���� �� ��� � (�� ���������)
		CW_USEDEFAULT, // ������� ���� �� ��� � (��� ������ � �, �� ������ �� �����)
		CW_USEDEFAULT, // ������ ������ (�� ���������)
		CW_USEDEFAULT, // ������ ���� (��� ������ � ������, �� ������ �� �����)
		NULL, // ���������� ������������� ������ (� ��� ��� ���. ����)
		NULL, // ���������� ���� (� ��� ��� ���)
		hInst, // .... ���������� ����������
		NULL); // ������ �� ������� �� WndProc

	if (!hWnd)
	{
		// � ������ ������������� �������� ���� (�������� ��������� � ��):
		MessageBox(NULL, "�� ���������� ������� ����!", "������", MB_OK);
		return NULL; // ������� �� ����������
	}

	ShowWindow(hWnd, nCmdShow); //���������� ���� �� ������ ��. Ÿ ������ �������� � ����������  ������ (�� �����������  CreateWindow()). 
								//������ �������� � ����� �����������. ��� ������ ������� ���� ������ ���� ����� ���������� ��������� 
								//������� WinMain(), � � ����������� ���� ����� ��������� ���� ������
	UpdateWindow(hWnd); //�������� �� ���������� ������ �� ������ ��� ������������� ��� ��� ������������ ����������. 
						//��� �������� � �� ��� �� ���������� ����.

	while (GetMessage(&msg, // ��������� �� ��������� MSG
		NULL, // ���������� ������ 
		NULL, // �������
		NULL)) // ������� ��� ������� ���������
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

ListFigure* CreateFigures()
{
	ListFigure* a = new ListFigure[1];

	int width = 50;
	int space = width / 5;

	int x = 50;
	int y = 50;
	COLORREF hP = RGB(238, 238, 238);
	COLORREF hB = RGB(40, 57, 60);

	MyRectangle* myRect = 0;
	MyEllipse* myEll = 0;
	MyTriangle* myTri = 0;
	
	for (int i = 0; i < 4; i++)
	{
		myRect = new MyRectangle(hP,
			hB,
			x,
			y + i * (width + space),
			x + width,
			y + i * (width + space) + width);

		a->AddElemToEnd(myRect);
		delete[] myRect;
	}

	x += width + space;
	hB = RGB(224, 26, 79);
	for (int i = 0; i < 12; i++)
	{
		if (i == 4)
		{
			x += width + space;
			hB = RGB(241, 89, 70);
		}
		if (i == 8)
		{
			x += width + space;
			hB = RGB(249, 194, 46);
		}
		myEll = new MyEllipse(hP,
			hB,
			x,
			y + (i % 4) * (width + space),
			x + width,
			y + (i % 4) * (width + space) + width);
		a->AddElemToEnd(myEll);
		delete[] myEll;
	}

	x += (width * 1.5 + space);
	y += (width / 2);
	hB = RGB(83, 179, 203);
	for (int i = 16; i < 20; i++)
	{
		myTri = new MyTriangle(hP,
			hB,
			x - width / 2,
			y - width / 2 + (i - 16) * (width + space),
			x + width / 2,
			y + (i - 16) * (width + space),
			x - width / 2,
			y + width / 2 + (i - 16) * (width + space));
		a->AddElemToEnd(myTri);
		delete myTri;
	}

	return a;
}

LRESULT WINAPI WndProc(HWND hWnd, // ���������� ������
	UINT uMsg, // ���������, ���������� ��
	WPARAM wParam, // ���������
	LPARAM lParam) // ���������, ��� ������������ ���������
{
	PAINTSTRUCT ps; //� ��������� ���������� �� ���� ��� ����������
	//RECT rect; //������������� ������� ����
	COLORREF colorText = RGB(255, 0, 0); //���� ������										 
	HDC hdc; // ��������� �������� ����������.
	static ListFigure* a;
	static ListFigure* b;
	static int cxClient; // ������ ����
	static int cyClient; // ������ ����
	static COLORREF selectedColorBrush;
	static COLORREF selectedColorPen;
	static int radius;
	static int xWindow;
	static int yWindow;

	int x = 0;
	int y = 0;

	static PanelMenu* panelMenu;
	static Sight* sight;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		a = CreateFigures();
		b = new ListFigure[1];

		panelMenu = new PanelMenu(cyClient);
		sight = new Sight(100, 300);

		xWindow = 300;
		yWindow = 300;
		
		selectedColorBrush = RGB(40, 57, 60);
		selectedColorPen = RGB(238, 238, 238);
		radius = 50;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps); // ������������ �������� ���������� � ����.

		/*int k = GetDeviceCaps(hdc, HORZSIZE); //������, � �����������, ����������� ������. 
		k = GetDeviceCaps(hdc, VERTSIZE); //������, � �����������, ����������� ������. 
		k = GetDeviceCaps(hdc, HORZRES); //������, � �����������, ����������� ������. 
		k = GetDeviceCaps(hdc, VERTRES); //������, � �����������, ����������� ������. 
		k = GetMapMode(hdc);
		//SetMapMode(hdc, MM_ISOTROPIC);
		k = GetMapMode(hdc);*/

		/*SetMapMode(hdc, MM_ISOTROPIC);
		SetWindowExtEx(hdc, 10, 10, NULL);
		SetViewportExtEx(hdc, -10, -10, NULL);
		SetViewportOrgEx(hdc, 300, 300, NULL);*/

		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);

		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(40, 57, 60));
		SelectObject(hdc, hPen);

		Rectangle(hdc, -50, -50, 50, 50);

		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, 0, 10);
		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, 10, 0);

		DeleteObject(hPen);

		panelMenu->Paint(hdc);
		
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		hdc = GetDC(hWnd);

		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		b->Paint(hdc);

		panelMenu->SetCYClient(cyClient);
		//panelMenu->Paint(hdc);

		break;
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);		
		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);
				
		if ((x >= 0) && (x <= 140))
		{
			panelMenu->OnMenuDOWN(a, b, xWindow, yWindow, x, y, hdc);
		}
		else if (x > 140)
		{
			SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
			MyEllipse* t = new MyEllipse(
				selectedColorPen, 
				selectedColorBrush, 
				x - radius - xWindow,
				y - radius - yWindow,
				x + radius - xWindow,
				y + radius - yWindow);
			b->AddElemToEnd(t);
			b->Paint(hdc);
			delete t;
		}

		panelMenu->Paint(hdc);

		break;
	}
	case WM_LBUTTONUP:
	{
		panelMenu->OnMenuUP();
	}
	case WM_MOUSEMOVE:
	{
		HDC hdc = GetDC(hWnd);
		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		panelMenu->OnMenuMOVE(
			b, 
			xWindow, yWindow,
			cxClient,cyClient, 
			x, y, hdc);

		if (x > 140)
		{
			if (sight->GetState())
			{
				sight->ChangeSight(xWindow, yWindow, x, y);
				SetViewportOrgEx(hdc, xWindow, yWindow, NULL);

				HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
				SelectObject(hdc, hBrush);
				SelectObject(hdc, hPen);

				Rectangle(hdc, 140 - xWindow, -yWindow, cxClient, cyClient);

				DeleteObject(hBrush);
				DeleteObject(hPen);

				b->Paint(hdc);
				panelMenu->Paint(hdc);
			}
		}
		
		break;
	}
	case WM_MBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		if (x > 140)
		{
			sight->TurnOn();
			sight->SetCoordDown(x, y);
		}

		break;
	}
	case WM_MBUTTONUP:
	{
						 sight->TurnOff();
						 break;
	}
	case WM_DESTROY:
	{
		delete[] a;
		delete[] b;
		delete panelMenu;
		PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}