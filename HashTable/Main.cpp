#include <Windows.h>
#include <string>
#include <cmath>

HINSTANCE hInst;

//

LPCTSTR szWindowClass = "szMainWindowClass";
LPCTSTR szTitle = "Title";

HWND MainWindow;

// 

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	hInst = hInstance;

	MSG msg;

	{

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = NULL;
		wcex.lpfnWndProc = (WNDPROC)WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = LoadIcon(NULL, IDI_INFORMATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = NULL;

		RegisterClassEx(&wcex);

		MainWindow = CreateWindow(
			szWindowClass,
			szTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			500,
			500,
			NULL,
			NULL,
			hInst,
			NULL
		);

		ShowWindow(MainWindow, SW_NORMAL);
		UpdateWindow(MainWindow);


	}

	// Цикл обработки событий:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

class Vector {

public:

	double dx;
	double dy;

	Vector() {}

	Vector(const double& x, const double& y) {

		dx = x;
		dy = y;

	}

	Vector& operator=(const Vector& src) {

		this->dx = src.dx;
		this->dy = src.dy;

		return (*this);

	}

};

class Point {

private:

	double x;
	double y;

public:

	friend COLORREF PXLCOLOR(const Point&);

	friend void PrintFuckingProjection(HDC);

	friend void PrintFuckingPoint(HDC);

	friend bool isInsideFigure(Point&);
	friend int GetNumber(const Point&);
	friend void PrintLine(HDC&, Point&, Point&);
	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	friend void PrintFuckingRotation(HDC);

	friend double Length(const Point&, const Point&);

public:

	Point() {

		x = -1488;
		y = -228;

	}

	Point(const double& X, const double& Y) {

		x = X;
		y = Y;

	}

	Point(const Point& src) {

		this->x = src.x;
		this->y = src.y;

	}

	Point& operator+=(const Vector& dv) {

		this->x += dv.dx;
		this->y += dv.dy;

		return (*this);

	}

	void operator=(const Point& src) {

		this->x = src.x;
		this->y = src.y;

	}

	const Point& ProjectionToTanget60() const {

		const double tanget60 = 1.7320508075;

		double resX = (this->y + this->x / tanget60) / (tanget60 + 1 / tanget60);

		return Point(

			resX,

			resX * tanget60

		);

	}

	const Point& ProjectionToTangetN60() const {

		const double tanget60 = 1.7320508075;
		const double tangetN60 = -tanget60;

		double resX = (this->x / tanget60 - this->y) / (tanget60 + 1 / tanget60);

		return Point(

			resX,

			resX * tangetN60

		);

	}

	const Point& ProjectionToAbscissaAxis() const {

		double resX = this->x;

		return Point(resX, 0.);

	}

	double LengthFromOrgin() {

		return std::sqrt(x * x + y * y);

	}

};

COLORREF PXLCOLOR(const Point& target) {

	if (target.x * target.x + target.y * target.y > 40000)
		return RGB(255, 255, 255);

	const double tanget30 = 0.577350269;
	const double tangetN30 = 0 - tanget30;

	if (target.x >= 0 && target.y >= target.x * tanget30) {

		// 1

		return RGB(0, 0, 0);

	}
	if (target.y <= target.x * tanget30 && target.y >= target.x * tangetN30) {

		// 6

		return RGB(255, 255, 0);

	}
	if (target.x >= 0 && target.y <= target.x * tangetN30) {

		// 5

		return RGB(0, 255, 255);

	}
	if (target.x <= 0 && target.y <= target.x * tanget30) {

		// 4

		return RGB(0, 160, 0);

	}
	if (target.y >= target.x * tanget30 && target.y <= target.x * tangetN30) {

		// 3

		return RGB(255, 0, 255);

	}
	if (target.x <= 0 && target.y >= target.x * tangetN30) {

		// 1

		return RGB(255, 0, 0);

	}

}

void ClearFuckingScreen(HDC hdc) {

	RECT cr;

	GetClientRect(MainWindow, &cr);

	SelectObject(hdc, GetStockObject(WHITE_BRUSH));

	Rectangle(hdc, 0, 0, cr.right, cr.bottom);

}

void PrintFuckingPie(HDC hdc) {

	int iBuf;
	int jBuf;

	for (int i(0); i < 500; i += 3) {

		iBuf = i;

		for (int j(0); j < 500; j += 3) {

			jBuf = j;

			j += rand() % 7 - 3;

			i += rand() % 7 - 3;

			SetPixel(hdc, i, j, PXLCOLOR(Point(i - 250, j - 250)));

			i = iBuf;
			j = jBuf;

		}

	}



}

void PrintFuckingLines(HDC hdc) {

	POINT pt;

	SelectObject(hdc, GetStockObject(BLACK_BRUSH));

	MoveToEx(hdc, 107, 500, &pt);

	LineTo(hdc, 500 - 107, 0);

	MoveToEx(hdc, 107, 0, &pt);

	LineTo(hdc, 500 - 107, 500);

	MoveToEx(hdc, 0, 250, &pt);

	LineTo(hdc, 500, 250);

}

Point mouse(0, 0);
Point projection(0, 0);
Point rotation(0, 0);

void PrintFuckingPoint(HDC hdc) {

	SelectObject(hdc, GetStockObject(GRAY_BRUSH));
	SelectObject(hdc, GetStockObject(NULL_PEN));

	const int radius = 5;

	Ellipse(hdc, mouse.x - radius, mouse.y - radius, mouse.x + radius, mouse.y + radius);

}

void PrintFuckingProjection(HDC hdc) {

	Point target(mouse.x - 250, mouse.y - 250);

	const double tanget30 = 0.577350269;
	const double tangetN30 = -tanget30;

	const double tanget60 = 1.7320508075;
	const double tangetN60 = -tanget60;

	if (target.x >= 0 && target.y >= target.x * tanget30) {

		// 1

		projection.x = (target.y + target.x / tanget60) / (tanget60 + 1 / tanget60);

		projection.y = projection.x * tanget60;

	}
	if (target.y <= target.x * tanget30 && target.y >= target.x * tangetN30) {

		// 6

		projection.x = target.x;

		projection.y = 0;

	}
	if (target.x >= 0 && target.y <= target.x * tangetN30) {

		// 5

		projection.x = (target.x / tanget60 - target.y) / (tanget60 + 1 / tanget60);

		projection.y = projection.x * tangetN60;


	}
	if (target.x <= 0 && target.y <= target.x * tanget30) {

		// 4

		projection.x = (target.y + target.x / tanget60) / (tanget60 + 1 / tanget60);

		projection.y = projection.x * tanget60;

	}
	if (target.y >= target.x * tanget30 && target.y <= target.x * tangetN30) {

		// 3

		projection.x = target.x;

		projection.y = 0;

	}
	if (target.x <= 0 && target.y >= target.x * tangetN30) {

		// 2

		projection.x = (target.x / tanget60 - target.y) / (tanget60 + 1 / tanget60);

		projection.y = projection.x * tangetN60;

	}

	SelectObject(hdc, GetStockObject(GRAY_BRUSH));
	SelectObject(hdc, GetStockObject(NULL_PEN));

	const int radius = 5;

	projection.x += 250;
	projection.y += 250;

	Ellipse(hdc, projection.x - radius, projection.y - radius, projection.x + radius, projection.y + radius);

}

void PrintFuckingRotation(HDC hdc) {

	Point target(mouse.x - 250, mouse.y - 250);

	const double tanget30 = 0.577350269;
	const double tangetN30 = -tanget30;

	const double tanget60 = 1.7320508075;
	const double tangetN60 = -tanget60;

	if (target.x >= 0 && target.y >= target.x * tanget30) {

#ifdef TEST1

		return 0;

#endif

		// 1

		rotation.x = target.x * (-0.5) - target.y * (0.8660254037844386);
		rotation.y = target.y * (-0.5) + target.x * (0.8660254037844386);

	}
	else if (target.y <= target.x * tanget30 && target.y >= target.x * tangetN30) {

#ifdef TEST6
		return 0;
#endif

		// 6

		rotation.x = -target.x;
		rotation.y = -target.y;

	}
	else if (target.x >= 0 && target.y <= target.x * tangetN30) {

#ifdef TEST5

		return 0;

#endif

		// 5

		rotation.x = target.x * (-0.5) - target.y * (-0.8660254037844386);
		rotation.y = target.y * (-0.5) + target.x * (-0.8660254037844386);

	}
	else if (target.x <= 0 && target.y <= target.x * tanget30) {

#ifdef TEST4

		return 0;

#endif

		// 4

		rotation.x = target.x * 0.5 - target.y * (-0.8660254037844386);
		rotation.y = target.y * 0.5 + target.x * (-0.8660254037844386);

	}
	else if (target.y >= target.x * tanget30 && target.y <= target.x * tangetN30) {

#ifdef TEST3
		return 0;
#endif

		// 3



	}
	else if (target.x <= 0 && target.y >= target.x * tangetN30) {

#ifdef TEST2

		return 0;

#endif

		// 2

		rotation.x = target.x * 0.5 - target.y * (0.8660254037844386);
		rotation.y = target.y * 0.5 + target.x * (0.8660254037844386);

	}

	SelectObject(hdc, GetStockObject(GRAY_BRUSH));
	SelectObject(hdc, GetStockObject(NULL_PEN));

	const int radius = 5;

	rotation.x += 250;
	rotation.y += 250;

	Ellipse(hdc, rotation.x - radius, rotation.y - radius, rotation.x + radius, rotation.y + radius);

}

bool isInsideFigure(Point& target) {

	return (target.x * target.x + target.y * target.y <= 40000);

}

//#define TEST

double Length(const Point& a, const Point& b) {

	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);

}

int GetNumber(const Point& target) {

	const double bigRadius = 31;
	const double& sixGonSideLength = bigRadius;

	/////////////////

	Point targetRotated = target;

	const double tanget30 = 0.577350269;
	const double tangetN30 = 0 - tanget30;

	const double sin60 = sqrt(3.) / 2.;
	const double cos60 = 0.5;

	Point projectionToBicectris;

	Vector offsetDiagonal;
	Vector offsetCurrent;
	Vector offsetPredict;

	offsetDiagonal.dx = -sixGonSideLength;
	offsetDiagonal.dy = 0;

	offsetCurrent.dx = -bigRadius * cos60;
	offsetCurrent.dy = -bigRadius * sin60;

	offsetPredict.dx = bigRadius * cos60;
	offsetPredict.dy = -bigRadius * sin60;

	double res = tan(45);

	if (target.x >= 0 && target.y >= target.x * tanget30) {

#ifdef TEST1

		return 0;

#endif

		// 1

		targetRotated.x = target.x * (-0.5) - target.y * (0.8660254037844386);
		targetRotated.y = target.y * (-0.5) + target.x * (0.8660254037844386);

	}
	else if (target.y <= target.x * tanget30 && target.y >= target.x * tangetN30) {

#ifdef TEST6
		return 0;
#endif

		// 6

		targetRotated.x = -target.x;
		targetRotated.y = -target.y;

	}
	else if (target.x >= 0 && target.y <= target.x * tangetN30) {

#ifdef TEST5

		return 0;

#endif

		// 5

		targetRotated.x = target.x * (-0.5) - target.y * (-0.8660254037844386);
		targetRotated.y = target.y * (-0.5) + target.x * (-0.8660254037844386);

	}
	else if (target.x <= 0 && target.y <= target.x * tanget30) {

#ifdef TEST4

		return 0;

#endif

		// 4

		targetRotated.x = target.x * 0.5 - target.y * (-0.8660254037844386);
		targetRotated.y = target.y * 0.5 + target.x * (-0.8660254037844386);

	}
	else if (target.y >= target.x * tanget30 && target.y <= target.x * tangetN30) {

#ifdef TEST3
		return 0;
#endif

		// 3



	}
	else if (target.x <= 0 && target.y >= target.x * tangetN30) {

#ifdef TEST2

		return 0;

#endif

		// 2

		targetRotated.x = target.x * 0.5 - target.y * (0.8660254037844386);
		targetRotated.y = target.y * 0.5 + target.x * (0.8660254037844386);

	}

	projectionToBicectris = targetRotated.ProjectionToAbscissaAxis();

	int countRadiuses = std::round(projectionToBicectris.LengthFromOrgin() / bigRadius);

	if (countRadiuses % 3 == 0) {

		countRadiuses--;

	}

	int lowLimit = countRadiuses;

	lowLimit -= (countRadiuses - 1) / 3;

	lowLimit--;

	lowLimit *= lowLimit;

	int highLimit = countRadiuses;

	highLimit -= (countRadiuses - 1) / 3;

	highLimit *= highLimit;

	int result = lowLimit + 1;

	Point resultPoint;

	resultPoint.x = countRadiuses * offsetDiagonal.dx;
	resultPoint.y = countRadiuses * offsetDiagonal.dy;

	if (Length(resultPoint, targetRotated) < sixGonSideLength / 2.)
		return result;

	if (targetRotated.y > 0.) {

		offsetCurrent.dy *= -1.;
		offsetPredict.dy *= -1.;

		result = (highLimit - lowLimit - 1) / 2 + lowLimit + 1;

		if (lowLimit % 2 == 0) {
			std::swap(offsetCurrent, offsetPredict);
		}

		while (Length(resultPoint, targetRotated) > sixGonSideLength / 2.) {

			resultPoint += offsetCurrent;
			result++;

			std::swap(offsetCurrent, offsetPredict);

		}

		return result;

	}
	else {

		if (lowLimit % 2 == 0) {
			std::swap(offsetCurrent, offsetPredict);
		}


		while (Length(resultPoint, targetRotated) > sixGonSideLength / 2.) {

			resultPoint += offsetCurrent;
			result++;

			std::swap(offsetCurrent, offsetPredict);

		}

		return result;// (highLimit - lowLimit - 1) / 2 + lowLimit + 1;

	}

}

void PrintLine(HDC& hdc, Point& p1, Point& p2) {

	POINT ps;

	MoveToEx(hdc, p1.x + 250, p1.y + 250, &ps);

	LineTo(hdc, p2.x + 250, p2.y + 250);

	std::string str1 = std::to_string(GetNumber(p1));
	std::string str2 = std::to_string(GetNumber(p2));

	TextOut(hdc, p1.x + 250, p1.y + 250, str1.c_str(), str1.size());
	TextOut(hdc, p2.x + 250, p2.y + 250, str2.c_str(), str2.size());

}

void PrintFuckingShield(HDC hdc) {

	static HFONT hFont = CreateFont(12, 8, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));

	static HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	SelectObject(hdc, pen);

	SelectObject(hdc, hFont);

	static HPEN GREEN_PEN = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	static HPEN RED_PEN = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	static HPEN BLUE_PEN = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	const double R = 31;

	Point a0(0. - R / 2. + R, R * sqrt(3.) / 2.);
	Point ap1 = a0;
	Point am1 = a0;

	const double Sin60 = sqrt(3.) / 2.;

	Vector nextLine(0, 2. * R * Sin60);
	Vector prevLine(0, -2. * R * Sin60);

	am1 += prevLine;

	Vector nextTriangle(2. * R - R / 2., R * Sin60);
	Vector prevTriangle(-2. * R + R / 2., 0. - R * Sin60);

	Vector t1(0. - R, 0);
	Vector t2(R / 2., R * Sin60);
	Vector t3(R / 2., 0. - R * Sin60);

	Point a;

	Point at;

	bool isEvenOne = true;

	bool doContinue = true;

	bool doContinue1 = true;
	bool doContinue2 = true;
	bool doContinue3 = true;

	while (isEvenOne) {

		isEvenOne = false;

		a = ap1;

		doContinue = true;

		while (doContinue) {

			doContinue = isInsideFigure(a);

			at = a;

			at += t1;

			if (doContinue1 = isInsideFigure(at)) {

				PrintLine(hdc, a, at);

			}

			at = a;

			at += t2;

			if (doContinue2 = isInsideFigure(at)) {

				PrintLine(hdc, a, at);

			}

			at = a;

			at += t3;

			if (doContinue3 = isInsideFigure(at)) {

				PrintLine(hdc, a, at);

			}

			a += nextTriangle;

			doContinue = doContinue || doContinue1 || doContinue2 || doContinue3;

			isEvenOne = isEvenOne || doContinue;

		}

		a = ap1;

		a += prevTriangle;

		doContinue = true;

		while (doContinue) {

			doContinue = false;

			if (isInsideFigure(a)) {

				doContinue = true;

				at = a;

				at += t1;

				if (isInsideFigure(at)) {

					PrintLine(hdc, a, at);

				}

				at = a;

				at += t2;

				if (isInsideFigure(at)) {

					PrintLine(hdc, a, at);

				}

				at = a;

				at += t3;

				if (isInsideFigure(at)) {

					PrintLine(hdc, a, at);

				}
			}

			a += prevTriangle;

			doContinue = doContinue || doContinue1 || doContinue2 || doContinue3;

			isEvenOne = isEvenOne || doContinue;

		}

		a = am1;

		doContinue = true;

		while (doContinue) {

			doContinue = isInsideFigure(a);

			at = a;

			at += t1;

			if (doContinue1 = isInsideFigure(at)) {

				PrintLine(hdc, a, at);

			}

			at = a;

			at += t2;

			if (doContinue2 = isInsideFigure(at)) {

				PrintLine(hdc, a, at);

			}

			at = a;

			at += t3;

			if (doContinue3 = isInsideFigure(at)) {

				PrintLine(hdc, a, at);

			}

			a += nextTriangle;

			doContinue = doContinue || doContinue1 || doContinue2 || doContinue3;

			isEvenOne = isEvenOne || doContinue;

		}

		a = am1;

		a += prevTriangle;

		doContinue = true;

		while (doContinue) {

			doContinue = false;

			if (isInsideFigure(a)) {

				doContinue = true;

				at = a;

				at += t1;

				if (isInsideFigure(at)) {

					PrintLine(hdc, a, at);

				}

				at = a;

				at += t2;

				if (isInsideFigure(at)) {

					PrintLine(hdc, a, at);

				}

				at = a;

				at += t3;

				if (isInsideFigure(at)) {

					PrintLine(hdc, a, at);

				}
			}

			a += prevTriangle;

			doContinue = doContinue || doContinue1 || doContinue2 || doContinue3;

			isEvenOne = isEvenOne || doContinue;

		}

		ap1 += nextLine;

		am1 += prevLine;

	}

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	RECT cr;

	HDC MainDC;

	HBITMAP bitmap;

	HDC hdc;

	switch (message)
	{
	case WM_PAINT:

		MainDC = BeginPaint(hWnd, &ps);

		hdc = CreateCompatibleDC(MainDC);

		bitmap = CreateCompatibleBitmap(MainDC, 1000, 1000);

		SelectObject(hdc, bitmap);

		ClearFuckingScreen(hdc);

		PrintFuckingPie(hdc);

		PrintFuckingLines(hdc);

		PrintFuckingPoint(hdc);

		PrintFuckingProjection(hdc);

		PrintFuckingRotation(hdc);

		PrintFuckingShield(hdc);

		BitBlt(MainDC, 0, 0, 1000, 1000, hdc, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);

		DeleteDC(hdc);

		DeleteObject(bitmap);

		break;

	case WM_LBUTTONDOWN:

		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);

		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

		break;

	case WM_DESTROY:

		PostQuitMessage(0);

		break;

	case WM_CREATE:

		break;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

