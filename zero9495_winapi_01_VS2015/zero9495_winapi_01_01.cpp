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
#include "Workspace.h"
#include <tchar.h>
//#include <gdiplus.h>
//#pragma comment(lib, "gdiplus.lib")
//using namespace Gdiplus;

int Figure::count = 0;

HINSTANCE hInst; //���������� ���������� ����������. �� ����� handle instance
TCHAR szAppName[] = _T("zero9495_winapi_01");
TCHAR szAppTitle[] = _T("zero9495_winapi_01");

HWND hWndPanelMenu;
HWND hWndWorkspace;

static COLORREF selectedColorBrush;
static COLORREF selectedColorPen;
static int xWindow;
static int yWindow;
static int currentMode;
static int xViewExt;
static int yViewExt;
static int xWinExt;
static int yWinExt;

#define WIDTH_PANEL_MENU 140
#define CX_CLIENT_START 1000
#define CY_CLIENT_START 500
#define IDT_TIMER1 1

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
LRESULT CALLBACK PanelMenuProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WorkspaceProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �������� ������� - ������ int main() � ���������� ����������:
int APIENTRY _tWinMain(HINSTANCE hInstance, // ���������� ���������� ����������
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
	wc.style = CS_DBLCLKS; // ����� ������ ������
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
		MessageBox(NULL, _T("�� ���������� ���������������� �����!"), _T("������"), MB_OK);
		return NULL; // ����������, �������������, ������� �� WinMain
	}
	
	hWnd = CreateWindow(szAppName, // ��� ������
		szAppTitle, // ��� ���� (�� ��� ������)
		WS_OVERLAPPEDWINDOW, // ������ ����������� ������
		CW_USEDEFAULT, // ��������� ���� �� ��� � (�� ���������)
		CW_USEDEFAULT, // ������� ���� �� ��� � (��� ������ � �, �� ������ �� �����)
		CX_CLIENT_START, // ������ ������ (�� ���������)
		CY_CLIENT_START, // ������ ���� (��� ������ � ������, �� ������ �� �����)
		NULL, // ���������� ������������� ������ (� ��� ��� ���. ����)
		NULL, // ���������� ���� (� ��� ��� ���)
		hInst, // .... ���������� ����������
		NULL); // ������ �� ������� �� WndProc

	if (!hWnd)
	{
		// � ������ ������������� �������� ���� (�������� ��������� � ��):
		MessageBox(NULL, _T("�� ���������� ������� ����!"), _T("������"), MB_OK);
		return NULL; // ������� �� ����������
	}

	ShowWindow(hWnd, nCmdShow); //���������� ���� �� ������ ��. Ÿ ������ �������� � ����������  ������ (�� �����������  CreateWindow()). 
								//������ �������� � ����� �����������. ��� ������ ������� ���� ������ ���� ����� ���������� ��������� 
								//������� WinMain(), � � ����������� ���� ����� ��������� ���� ������
	UpdateWindow(hWnd); //�������� �� ���������� ������ �� ������ ��� ������������� ��� ��� ������������ ����������. 
						//��� �������� � �� ��� �� ���������� ����.

	//////////////////////////////////////////////////////////////////////////////////
	
	WNDCLASSEX wcPanelMenu;
	wcPanelMenu.lpfnWndProc = (WNDPROC)PanelMenuProc;
	wcPanelMenu.hInstance = hInstance;
	wcPanelMenu.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcPanelMenu.lpszClassName = "WClassPanelMenu";
	wcPanelMenu.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcPanelMenu.cbSize = sizeof(wc); // �������� ��������� (� ������)
	wcPanelMenu.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���������� ������
	wcPanelMenu.style = NULL; // ����� ������ ������
	wcPanelMenu.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���������� ����� ����
	wcPanelMenu.lpszMenuName = NULL; // ��������� �� const-������, ���������� ��� ����, ������������ ��� ������
	wcPanelMenu.cbClsExtra = 0; // ����� ������������� ������ ��� �������� ���������� ����������
	wcPanelMenu.cbWndExtra = 0; // ����� ������������� ������ � ����� ���������
	wcPanelMenu.hIconSm = 0;

	if (!RegisterClassEx(&wcPanelMenu))
	{
		// � ������ ���������� ����������� ������:
		MessageBox(NULL, _T("�� ���������� ���������������� �����!"), _T("������"), MB_OK);
		return NULL; // ����������, �������������, ������� �� WinMain
	}

	hWndPanelMenu = CreateWindowEx(0, _T("WClassPanelMenu"), (LPCTSTR)NULL,
		WS_CHILD,
		0, 0,
		WIDTH_PANEL_MENU, 
		CY_CLIENT_START, 
		hWnd, 0, hInst, NULL);

	if (!hWndPanelMenu)
	{
		// � ������ ������������� �������� ���� (�������� ��������� � ��):
		MessageBox(NULL, _T("�� ���������� ������� ����!"), _T("������"), MB_OK);
		return NULL; // ������� �� ����������
	}

	ShowWindow(hWndPanelMenu, SW_NORMAL);
	UpdateWindow(hWndPanelMenu);

	///////////////////////////////////////////////////////////////////////////////////

	WNDCLASSEX wcWorkspace;
	wcWorkspace.lpfnWndProc = (WNDPROC)WorkspaceProc;
	wcWorkspace.hInstance = hInstance;
	wcWorkspace.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcWorkspace.lpszClassName = _T("WClassWorkspace");
	wcWorkspace.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcWorkspace.cbSize = sizeof(wc); // �������� ��������� (� ������)
	wcWorkspace.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���������� ������
	wcWorkspace.style = CS_DBLCLKS; // ����� ������ ������
	wcWorkspace.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���������� ����� ����
	wcWorkspace.lpszMenuName = NULL; // ��������� �� const-������, ���������� ��� ����, ������������ ��� ������
	wcWorkspace.cbClsExtra = 0; // ����� ������������� ������ ��� �������� ���������� ����������
	wcWorkspace.cbWndExtra = 0; // ����� ������������� ������ � ����� ���������
	wcWorkspace.hIconSm = 0;

	if (!RegisterClassEx(&wcWorkspace))
	{
		// � ������ ���������� ����������� ������:
		MessageBox(NULL, _T("�� ���������� ���������������� �����!"), _T("������"), MB_OK);
		return NULL; // ����������, �������������, ������� �� WinMain
	}

	hWndWorkspace = CreateWindowEx(0, _T("WClassWorkspace"), (LPCTSTR)NULL,
		WS_CHILD | CS_DBLCLKS,
		WIDTH_PANEL_MENU, 0,
		CX_CLIENT_START, 
		CY_CLIENT_START, 
		hWnd, 0, hInst, NULL);

	if (!hWndWorkspace)
	{
		// � ������ ������������� �������� ���� (�������� ��������� � ��):
		MessageBox(NULL, _T("�� ���������� ������� ����!"), _T("������"), MB_OK);
		return NULL; // ������� �� ����������
	}

	ShowWindow(hWndWorkspace, SW_NORMAL);
	UpdateWindow(hWndWorkspace);

	///////////////////////////////////////////////////////////////////////////////////

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

	int x = 0;
	int y = 0;
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

void SetDirection(POINT direction)
{
	if (direction.x == 3)
	{
		xWinExt = 1;
	}
	else
	{
		xWinExt = -1;
	}

	if (direction.y == 6)
	{
		yWinExt = 1;
	}
	else
	{
		yWinExt = -1;
	}
	//xViewExt = 1; !!!!!!!!!!!!!!!!!������������ ��� ��������� ��������!!!!!!!!!!!!!!!!!!!!!!!!!!
	//yViewExt = 1;
}

LRESULT CALLBACK WorkspaceProc(HWND hWnd, // ���������� ������
	UINT uMsg, // ���������, ���������� ��
	WPARAM wParam, // ���������
	LPARAM lParam) // ���������, ��� ������������ ���������
{
	PAINTSTRUCT ps; //� ��������� ���������� �� ���� ��� ����������	
	HDC hdc; // ��������� �������� ����������.
	static ListFigure* a;
	static ListFigure* b;
	static int cxClient; // ������ ����
	static int cyClient; // ������ ����
	
	static int radius;

	static int x;
	static int y;

	static Sight* sight;
	static Workspace* workspace;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		a = CreateFigures();
		b = new ListFigure[1];

		sight = new Sight(0,0);
		workspace = new Workspace(
			-CX_CLIENT_START, 
			-CY_CLIENT_START, 
			CX_CLIENT_START, 
			CY_CLIENT_START);

		xWindow = CX_CLIENT_START / 3;
		yWindow = CY_CLIENT_START / 2;

		xViewExt = 1;
		yViewExt = 1;
		xWinExt = 1;
		yWinExt = 1;

		x = 0;
		y = 0;

		currentMode = MM_TEXT;

		selectedColorBrush = RGB(40, 57, 60);
		selectedColorPen = RGB(238, 238, 238);
		radius = 70;
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps); // ������������ �������� ���������� � ����.
		SetMapMode(hdc, currentMode);
		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
		{
			SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
			SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
		}

		b->Paint(hdc);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		hdc = GetDC(hWnd);
		SetMapMode(hdc, currentMode);
		if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
		{
			SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
			SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
		}

		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		b->Paint(hdc);

		workspace->ChangeSize(cxClient - WIDTH_PANEL_MENU, cyClient);

		break;
	}
	case WM_PASTE:
	{
		b->AddElemToEnd(a);
		break;
	}
	case WM_KEYDOWN:
	{
		WORD nKey = LOWORD(wParam);
		switch (nKey)
		{
		case _T('o'):
		{
			SendMessage(hWndWorkspace, WM_TIMER, IDT_TIMER1, lParam);
			break;
		}
		}
	}
	case WM_TIMER:
	{
		switch (wParam)
		{
		case IDT_TIMER1:
		{
			HDC hdc = GetDC(hWnd);
			SetMapMode(hdc, currentMode);
			SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
			SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);

			//x = LOWORD(lParam); //����� ����������
			//y = HIWORD(lParam);

			SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
			MyRectangle* t = 0;
			if (currentMode == MM_TEXT)
			{
				t = new MyRectangle(
					selectedColorPen,
					selectedColorBrush,
					x - radius - xWindow,
					y - radius - yWindow,
					x + radius - xWindow,
					y + radius - yWindow);
			}
			else if (currentMode == MM_ISOTROPIC)
			{
				t = new MyRectangle(
					selectedColorPen,
					selectedColorBrush,
					(x - radius - xWindow) * xWinExt,
					(y - radius - yWindow) * yWinExt,
					(x + radius - xWindow) * xWinExt,
					(y + radius - yWindow) * yWinExt);
			}
			else if (currentMode == MM_ANISOTROPIC)
			{
				t = new MyRectangle(
					selectedColorPen,
					selectedColorBrush,
					(x - radius - xWindow) * xWinExt,
					(y - radius - yWindow) * yWinExt,
					(x + radius - xWindow) * xWinExt,
					(y + radius - yWindow) * yWinExt);
			}
			b->AddElemToEnd(t);
			delete t;

			b->Paint(hdc);
			KillTimer(hWnd, IDT_TIMER1);
			break;
		}
		}
		break;
	}
	case WM_LBUTTONDBLCLK:
	{
		HDC hdc = GetDC(hWnd);
		SetMapMode(hdc, currentMode);
		SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
		SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);

		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		MyTriangle* t = 0;
		if (currentMode == MM_TEXT)
		{
			t = new MyTriangle(selectedColorPen,
				selectedColorBrush,
				x - radius - xWindow,
				y - radius - yWindow,
				x + radius - xWindow,
				y - yWindow,
				x - radius - xWindow,
				y + radius - yWindow);

			/*t = new MyRectangle(
				selectedColorPen,
				selectedColorBrush,
				x - radius - xWindow,
				y - radius - yWindow,
				x + radius - xWindow,
				y + radius - yWindow);*/
		}
		else if (currentMode == MM_ISOTROPIC)
		{
			t = new MyTriangle(selectedColorPen,
				selectedColorBrush,
				(x - radius - xWindow) * xWinExt,
				(y - radius - yWindow) * yWinExt,
				(x + radius - xWindow) * xWinExt,
				(y - yWindow) * yWinExt,
				(x - radius - xWindow) * xWinExt,
				(y + radius - yWindow) * yWinExt);

			/*t = new MyRectangle(
				selectedColorPen,
				selectedColorBrush,
				(x - radius - xWindow) * xWinExt,
				(y - radius - yWindow) * yWinExt,
				(x + radius - xWindow) * xWinExt,
				(y + radius - yWindow) * yWinExt);*/
		}
		else if (currentMode == MM_ANISOTROPIC)
		{
			t = new MyTriangle(selectedColorPen,
				selectedColorBrush,
				(x - radius - xWindow) * xWinExt,
				(y - radius - yWindow) * yWinExt,
				(x + radius - xWindow) * xWinExt,
				(y - yWindow) * yWinExt,
				(x - radius - xWindow) * xWinExt,
				(y + radius - yWindow) * yWinExt);

			/*t = new MyRectangle(
				selectedColorPen,
				selectedColorBrush,
				(x - radius - xWindow) * xWinExt,
				(y - radius - yWindow) * yWinExt,
				(x + radius - xWindow) * xWinExt,
				(y + radius - yWindow) * yWinExt);*/
		}
		b->AddElemToEnd(t);
		delete t;

		b->Paint(hdc);

		KillTimer(hWnd, IDT_TIMER1);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		SetTimer(hWnd,             // ���������� �������� ����
			IDT_TIMER1,            // ������������� �������
			200,                 // 10-��������� ��������
			(TIMERPROC)NULL);	
		
		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		break;
	}
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		SetMapMode(hdc, currentMode);
		SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
		SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);

		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		MyEllipse* t = 0;
		if (currentMode == MM_TEXT)
		{
			t = new MyEllipse(
				selectedColorPen,
				selectedColorBrush,
				x - radius - xWindow,
				y - radius - yWindow,
				x + radius - xWindow,
				y + radius - yWindow);
		}
		else if (currentMode == MM_ISOTROPIC)
		{
			t = new MyEllipse(
				selectedColorPen,
				selectedColorBrush,
				(x - radius - xWindow) * xWinExt,
				(y - radius - yWindow) * yWinExt,
				(x + radius - xWindow) * xWinExt,
				(y + radius - yWindow) * yWinExt);
		}
		else if (currentMode == MM_ANISOTROPIC)
		{
			t = new MyEllipse(
				selectedColorPen,
				selectedColorBrush,
				(x - radius - xWindow) * xWinExt,
				(y - radius - yWindow) * yWinExt,
				(x + radius - xWindow) * xWinExt,
				(y + radius - yWindow) * yWinExt);
		}
		b->AddElemToEnd(t);
		delete t;

		b->Paint(hdc);
		break;
	}
	case WM_LBUTTONUP:
	{
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (sight->GetState())
		{
			HDC hdc = GetDC(hWnd);
			SetMapMode(hdc, currentMode);
			if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
			{
				SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
				SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
			}

			x = LOWORD(lParam); //����� ����������
			y = HIWORD(lParam);

			sight->ChangeSight(xWindow, yWindow, x, y);
			InvalidateRect(hWndWorkspace, NULL, TRUE);
		}

		break;
	}
	case WM_MBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		SetMapMode(hdc, currentMode);
		if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
		{
			SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
			SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
		}

		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		sight->TurnOn();
		sight->SetCoordDown(x, y);

		break;
	}
	case WM_MBUTTONUP:
	{
		sight->TurnOff();
		break;
	}
	case WM_CLEAR:
	{
		HDC hdc = GetDC(hWnd);

		SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
		SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);

		workspace->Clear(hdc, xViewExt, yViewExt, xWinExt, yWinExt);
		break;
	}
	case WM_DESTROY:
	{
		delete[] a;
		delete[] b;
		delete[] sight;
		delete workspace;
		PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK PanelMenuProc(HWND hWnd, // ���������� ������
	UINT uMsg, // ���������, ���������� ��
	WPARAM wParam, // ���������
	LPARAM lParam) // ���������, ��� ������������ ���������
{
	PAINTSTRUCT ps; //� ��������� ���������� �� ���� ��� ����������									 
	HDC hdc; // ��������� �������� ����������.
	static int cxClient; // ������ ����
	static int cyClient; // ������ ����
	static COLORREF selectedColorBrush;
	static COLORREF selectedColorPen;
	
	int x = 0;
	int y = 0;

	static PanelMenu* panelMenu;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		panelMenu = new PanelMenu(cyClient);
		
		xWindow = 0;
		yWindow = 0;

		xViewExt = -10;
		yViewExt = 10;
		xWinExt = 10;
		yWinExt = -10;

		selectedColorBrush = RGB(40, 57, 60);
		selectedColorPen = RGB(238, 238, 238);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps); // ������������ �������� ���������� � ����.
		SetMapMode(hdc, MM_TEXT);

		panelMenu->Paint(hdc);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_SIZE:
	{
		cyClient = HIWORD(lParam);

		hdc = GetDC(hWnd);
		SetMapMode(hdc, MM_TEXT);
		
		panelMenu->SetCYClient(cyClient);
		panelMenu->Paint(hdc);
		
		break;
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		SetMapMode(hdc, MM_TEXT);

		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		if (panelMenu->OnSetMapModeDOWN(xWindow, yWindow, x, y, hdc))
		{
			currentMode = GetMapMode(hdc);
			SetMapMode(hdc, MM_TEXT);
			SendMessage(hWndWorkspace, WM_PASTE, wParam, lParam);
			InvalidateRect(hWndWorkspace, NULL, TRUE);
		}
		else
		{
			SetDirection(panelMenu->OnChangeDirectionDOWN(x, y, hdc));
			InvalidateRect(hWndWorkspace, NULL, TRUE);
		}
		panelMenu->Paint(hdc);
		SendMessage(hWndWorkspace, WM_PAINT, wParam, lParam);

		break;
	}
	case WM_LBUTTONUP:
	{
		panelMenu->OnMenuUP();
		panelMenu->Paint(hdc);
		SendMessage(hWndWorkspace, WM_PAINT, wParam, lParam);
		break;
	}
	case WM_MOUSEMOVE:
	{
		HDC hdc = GetDC(hWnd);
		SetMapMode(hdc, MM_TEXT);
		
		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		if (panelMenu->OnMenuMOVE(x, y, hdc))
		{
			panelMenu->Paint(hdc);
			SetDirection(panelMenu->OnChangeDirectionDOWN(x, y, hdc));
			InvalidateRect(hWndWorkspace, NULL, TRUE);
		}
		
		break;
	}
	case WM_MBUTTONDOWN:
	{			
		break;
	}
	case WM_MBUTTONUP:
	{		
		break;
	}
	case WM_DESTROY:
	{
		delete panelMenu;
		PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

LRESULT WINAPI WndProc(HWND hWnd, // ���������� ������
	UINT uMsg, // ���������, ���������� ��
	WPARAM wParam, // ���������
	LPARAM lParam) // ���������, ��� ������������ ���������
{
	PAINTSTRUCT ps; //� ��������� ���������� �� ���� ��� ����������
	//COLORREF colorText = RGB(255, 0, 0); //���� ������										 
	HDC hdc; // ��������� �������� ����������.
	//static ListFigure* a;
	//static ListFigure* b;
	//static int cxClient; // ������ ����
	//static int cyClient; // ������ ����
	//static COLORREF selectedColorBrush;
	//static COLORREF selectedColorPen;
	//static int radius;		

	//int x = 0;
	//int y = 0;

	//static PanelMenu* panelMenu;
	//static Sight* sight;
	//static Workspace* workspace;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		/*a = CreateFigures();
		b = new ListFigure[1];

		//panelMenu = new PanelMenu(cyClient);
		ShowWindow(hWndPanelMenu, SW_NORMAL);
		sight = new Sight(100, 300);
		workspace = new Workspace(-cxClient, -cyClient, cxClient, cyClient);

		xWindow = 0;
		yWindow = 0;

		xViewExt = -10;
		yViewExt = 10;
		xWinExt = 10;
		yWinExt = -10;

		currentMode = MM_TEXT;
		
		selectedColorBrush = RGB(40, 57, 60);
		selectedColorPen = RGB(238, 238, 238);
		radius = 70;*/
		break;
	}
	case WM_PAINT:
	{
		/*hdc = BeginPaint(hWnd, &ps); // ������������ �������� ���������� � ����.
		SetMapMode(hdc, currentMode);
		if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
		{
			SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
			SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
		}*/

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

		/*SetViewportOrgEx(hdc, xWindow, yWindow, NULL);

		//panelMenu->Paint(hdc, xViewExt,	yViewExt, xWinExt, yWinExt);
		
		EndPaint(hWnd, &ps);*/
		break;
	}
	case WM_SIZE:
	{
		int cxClient = LOWORD(lParam);
		int cyClient = HIWORD(lParam);
				
		/*SetWindowPos(hWndPanelMenu, HWND_TOP, 0, 0, cxClient, cyClient, SWP_NOOWNERZORDER); // SWP_NOMOVE | SWP_NOZORDER);
		SetWindowPos(hWndWorkspace, HWND_TOP, 0, 0, cxClient, cyClient, SWP_NOOWNERZORDER);// SWP_NOMOVE | SWP_NOZORDER);
		//InvalidateRect(hWndWorkspace, NULL, TRUE);

		SendMessage(hWndWorkspace, WM_SIZE, wParam, lParam);
		SendMessage(hWndPanelMenu, WM_SIZE, wParam, lParam);*/

		MoveWindow(hWndPanelMenu, 0, 0, WIDTH_PANEL_MENU, cyClient, TRUE);
		MoveWindow(hWndWorkspace, WIDTH_PANEL_MENU, 0, cxClient - WIDTH_PANEL_MENU, cyClient, TRUE);

		/*cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		hdc = GetDC(hWnd);
		SetMapMode(hdc, currentMode);
		if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
		{
			SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
			SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
		}

		SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		b->Paint(hdc);

		//panelMenu->SetCYClient(cyClient);
		workspace->ChangeSize(cxClient, cyClient);*/

		break;
	}
	case WM_KEYDOWN:
	{
		WORD nKey = LOWORD(wParam);
		switch (nKey)
		{
		case 79:
		{
			SendMessage(hWndWorkspace, WM_TIMER, IDT_TIMER1, lParam);
			break;
		}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		/*HDC hdc = GetDC(hWnd);		
		SetMapMode(hdc, currentMode);
		SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
		SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
		
		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);
				
		if ((x >= 0) && (x <= WIDTH_PANEL_MENU))
		{*/
			/*if (!panelMenu->OnMenuDOWN(a, b, xWindow, yWindow, x, y, hdc))
			{
				currentMode = GetMapMode(hdc);
				if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
				{
					SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
					SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
				}
				workspace->Clear(hdc, xViewExt, yViewExt, xWinExt, yWinExt);
			}*/
		/*}
		else if (x > WIDTH_PANEL_MENU)
		{			
			SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
			MyEllipse* t = 0;
			if (currentMode == MM_TEXT)
			{
				t = new MyEllipse(
					selectedColorPen,
					selectedColorBrush,
					x - radius - xWindow,
					y - radius - yWindow,
					x + radius - xWindow,
					y + radius - yWindow);
			}
			else if (currentMode == MM_ISOTROPIC)
			{
				t = new MyEllipse(
					selectedColorPen,
					selectedColorBrush,
					-(x - radius - xWindow),
					-(y - radius - yWindow),
					-(x + radius - xWindow),
					-(y + radius - yWindow));
			}
			else if (currentMode == MM_ANISOTROPIC)
			{
				t = new MyEllipse(
					selectedColorPen,
					selectedColorBrush,
					-(x - radius - xWindow),
					-(y - radius - yWindow),
					-(x + radius - xWindow),
					-(y + radius - yWindow));
			}			
			b->AddElemToEnd(t);
			delete t;
		}

		b->Paint(hdc);
		//panelMenu->Paint(hdc, xViewExt, yViewExt, xWinExt, yWinExt);

		currentMode = GetMapMode(hdc);*/

		break;
	}
	case WM_LBUTTONUP:
	{
		//panelMenu->OnMenuUP();

		break;
	}
	case WM_MOUSEMOVE:
	{
		/*HDC hdc = GetDC(hWnd);
		SetMapMode(hdc, currentMode);
		if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
		{
			SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
			SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
		}

		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);*/

		/*panelMenu->OnMenuMOVE(
			b, 
			xWindow, yWindow,
			cxClient,cyClient, 
			x, y, hdc);*/

		/*if (x > WIDTH_PANEL_MENU)
		{
			if (sight->GetState())
			{
				sight->ChangeSight(xWindow, yWindow, x, y);
				SetViewportOrgEx(hdc, xWindow, yWindow, NULL);

				workspace->Clear(hdc, xViewExt, yViewExt, xWinExt, yWinExt);

				if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
				{
					SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
					SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
				}

				b->Paint(hdc);
				//panelMenu->Paint(hdc, xViewExt, yViewExt, xWinExt, yWinExt);
			}
		}*/
		
		break;
	}
	case WM_MBUTTONDOWN:
	{
		/*HDC hdc = GetDC(hWnd);
		SetMapMode(hdc, currentMode);
		if ((currentMode == MM_ISOTROPIC) || (currentMode == MM_ANISOTROPIC))
		{
			SetWindowExtEx(hdc, xWinExt, yWinExt, NULL);
			SetViewportExtEx(hdc, xViewExt, yViewExt, NULL);
		}

		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		if (x > WIDTH_PANEL_MENU)
		{
			sight->TurnOn();
			sight->SetCoordDown(x, y);
		}*/

		break;
	}
	case WM_MBUTTONUP:
	{
		 /*sight->TurnOff();*/
		 break;
	}
	case WM_DESTROY:
	{
		/*delete[] a;
		delete[] b;
		delete[] sight;
		delete workspace;*/
		//delete panelMenu;
		PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}