/*///////////////////////////////////////////////////////////////////////////////////////

08.11.2015 -  1768 строк


Задания по программированию для Win32, 3 курс

1.Рисование 20 фигур (треугольников,окружностей,прямоугольников) в окне.Координаты и
цвет произвольные.

2.То же в режимах MM_ISOTROPIC,MM_ANISOTROPIC.

3.То же, фигуры добавляются по нажатию : левой кнопки мыши-прямоугольник,
правой-окружности.

4.То же,но еще по двойному нажатию левой-треугольник.При этом не должен
появлятся прямоугольник в этом же месте.

5.То же, с клавиатурой, клавишами o,t,p.

6.Резиновый контур - перетаскивание прямоугольника.

7.То же, со скроллингом.Размер документа 1500*1000.

8. Регионы и пути.

9.Разместить в окне несколько управляющих окон (edit, listbox, combobox, button)
и организовать между ними передачу информации. Детали продумать самостоятельно.

10.Установить для окна собственные иконку и курсор.

11.Создать в окне меню с пунктами "окружность" , "прямоугольник", "треугольник".
По выбору соответствующего пункта нажатие левой кнопки мыши должно рисовать
соответствующую фигуру.

12.То же с помощью  toolbar. Текущий режим должен отображаться в statusbar.
Реализовать подсказки к кнопкам toolbar. Рисование перенести в дочернее "окно-вид".

13.Вывести в окне битовую карту.

14.Реализовать обработку WM_PAINT с помощью внеэкранного буфера (offscreen).

15. Работа с битовыми картами в формате DIB. Чтение из файла .bmp, вывод в окно
и сохранение битовой карты DIB в файле.

16.По пункту меню открыть диалог с выбором битовых карт (4-5 штук).
После выбора битовая карта рисуется в окне.

17.Стандартные диалоги (выбор файла, цвета, шрифта).
Пример придумать самостоятельно.

18.Диалог с элементами trackbar , up-down, progressbar, animation.
Пример придумать самостоятельно.

19.Диалог с listview. Добавление, удаление и выбор элемента. Перемещение между
элементами.

20.Факультативно - диалог с treeview .

21.Факультативно - property sheet, tab control.


22.Запоминание содержимого окна в Clipboard и вставка в него из Clipboard.

23. GDI+
*//////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h> // заголовочный файл, содержащий функции API
#include "ListFigure.h"
//#include <vld.h>
#include "Sight.h"
#include "PanelMenu.h"
//#include <gdiplus.h>
//#pragma comment(lib, "gdiplus.lib")
//using namespace Gdiplus;

int Figure::count = 0;

HINSTANCE hInst; //дескриптор экземпляра приложения. От фразы handle instance
char szAppName[] = "zero9495_winapi_01";
char szAppTitle[] = "zero9495_winapi_01";

/*
Вспомогательные типы данных используются в некоторых функциях.
В частности, параметры, описанные ниже, используются при работе с
функцией обратного вызова оконной процедуры такого вида:

LRESULT CALLBACK ИмяФункции(HWND hWnd, UINT uMSg, WPARAM wParam, LPARAM lParam);

Работа с данной функцией будет в следующих разделах.
LPARAM – тип для описания lParam (long parameter). Используются вместе с wparam в некоторых функциях.
LRESULT – значение, возвращаемое оконной процедурой имеет тип long.
WPARAM – тип для описания wParam (word parameter). Используются вместе с lParam в некоторых функциях.
*/
LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Основная функция - аналог int main() в консольном приложении:
int APIENTRY WinMain(HINSTANCE hInstance, // дескриптор экземпляра приложения
	HINSTANCE hPrevInstance, // в Win32 не используется
	LPSTR lpCmdLine, // нужен для запуска окна в режиме командной строки
	int nCmdShow) // режим отображения окна
{
	WNDCLASSEX wc; // создаём экземпляр, для обращения к членам класса WNDCLASSEX
	HWND hWnd; // создаём дескриптор будущего окошка
	MSG msg;

	hInst = hInstance;
	wc.cbSize = sizeof(wc); // величина структуры (в байтах)
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // дескриптор значка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // .... курсора мыши
	wc.style = NULL; // стиль класса окошка
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Дескриптор кисти фона
	wc.lpszMenuName = NULL; // указатель на const-строку, содержащюю имя меню, применяемого для класса
	wc.lpszClassName = szAppName; // указатель на const-строку, содержащюю имя класса
	wc.lpfnWndProc = (WNDPROC)WndProc; //Указатель на оконную процедуру
	wc.cbClsExtra = 0; // число освобождаемых байтов при создании экземпляра приложения
	wc.cbWndExtra = 0; // число освобождаемых байтов в конце структуры
	wc.hIconSm = 0;

	if (!RegisterClassEx(&wc))
	{
		// в случае отсутствия регистрации класса:
		MessageBox(NULL, "Не получилось зарегистрировать класс!", "Ошибка", MB_OK);
		return NULL; // возвращаем, следовательно, выходим из WinMain
	}

	hWnd = CreateWindow(szAppName, // имя класса
		szAppTitle, // имя окна (то что сверху)
		WS_OVERLAPPEDWINDOW, // режимы отображения окошка
		CW_USEDEFAULT, // положение окна по оси х (по умолчанию)
		CW_USEDEFAULT, // позиция окна по оси у (раз дефолт в х, то писать не нужно)
		CW_USEDEFAULT, // ширина окошка (по умолчанию)
		CW_USEDEFAULT, // высота окна (раз дефолт в ширине, то писать не нужно)
		NULL, // дескриптор родительского окошка (у нас нет род. окон)
		NULL, // дескриптор меню (у нас его нет)
		hInst, // .... экземпляра приложения
		NULL); // ничего не передаём из WndProc

	if (!hWnd)
	{
		// в случае некорректного создания окна (неверные параметры и тп):
		MessageBox(NULL, "Не получилось создать окно!", "Ошибка", MB_OK);
		return NULL; // выходим из приложения
	}

	ShowWindow(hWnd, nCmdShow); //отображает окно на экране ПК. Её первый параметр – дескриптор  окошка (он возвращался  CreateWindow()). 
								//Второй параметр – стиль отображения. При первом запуске окна должен быть равен последнему параметру 
								//функции WinMain(), а в последующие разы можно вписывать свои данные
	UpdateWindow(hWnd); //отвечает за обновления окошка на экране при сворачиваниях или при динамической информации. 
						//Его параметр – всё тот же дескриптор окна.

	while (GetMessage(&msg, // указатель на структуру MSG
		NULL, // дескриптор окошка 
		NULL, // фильтры
		NULL)) // фильтры для выборки сообщений
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

LRESULT WINAPI WndProc(HWND hWnd, // дескриптор окошка
	UINT uMsg, // сообщение, посылаемое ОС
	WPARAM wParam, // параметры
	LPARAM lParam) // сообщений, для последующего обращения
{
	PAINTSTRUCT ps; //в структуре информация об окне для прорисовки
	//RECT rect; //прямоугольная область окна
	COLORREF colorText = RGB(255, 0, 0); //цвет текста										 
	HDC hdc; // Объявляем контекст устройства.
	static ListFigure* a;
	static ListFigure* b;
	static int cxClient; // Ширина окна
	static int cyClient; // Высота окна
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
		hdc = BeginPaint(hWnd, &ps); // Присоединяем контекст устройства к окну.

		/*int k = GetDeviceCaps(hdc, HORZSIZE); //Ширина, в миллиметрах, физического экрана. 
		k = GetDeviceCaps(hdc, VERTSIZE); //Ширина, в миллиметрах, физического экрана. 
		k = GetDeviceCaps(hdc, HORZRES); //Ширина, в миллиметрах, физического экрана. 
		k = GetDeviceCaps(hdc, VERTRES); //Ширина, в миллиметрах, физического экрана. 
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
		x = LOWORD(lParam); //узнаём координаты
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
		x = LOWORD(lParam); //узнаём координаты
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
		x = LOWORD(lParam); //узнаём координаты
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
		PostQuitMessage(NULL); // отправляем WinMain() сообщение WM_QUIT
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}