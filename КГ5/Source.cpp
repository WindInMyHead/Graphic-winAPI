#include"Prism.h"
#include"Pyramid.h"

Pyramid pyramid;
Prism prism;

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int mCmdShow) {//точка входа
	MSG msg{}; //сообщения
	HWND hwnd{}; //дескриптор
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(COLOR_INACTIVECAPTION));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
		RECT Rect;
		HDC hdc, hCmpDC;
		PAINTSTRUCT ps;
		HBITMAP hBmp;
		switch (uMsg) {
		case WM_PAINT:
		{//буфер кадра
			GetClientRect(hWnd, &Rect);
			hdc = BeginPaint(hWnd, &ps);
			hCmpDC = CreateCompatibleDC(hdc);//для двойной буферизации
			hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left, Rect.bottom - Rect.top);
			SelectObject(hCmpDC, hBmp);
			LOGBRUSH br;//закраска фона
			br.lbStyle = BS_SOLID;
			br.lbColor = 0x24100;
			HBRUSH brush;
			brush = CreateBrushIndirect(&br);
			FillRect(hCmpDC, &Rect, brush);
			SelectObject(hdc, brush);
			pyramid.Draw(hCmpDC);
			prism.Draw(hCmpDC);
			DeleteObject(brush);
			SetStretchBltMode(hdc, COLORONCOLOR);
			BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, hCmpDC, 0, 0, SRCCOPY);
			DeleteDC(hCmpDC);
			DeleteObject(hBmp);
			hCmpDC = NULL;
			EndPaint(hWnd, &ps);
		}
		return 0;

		case WM_KEYDOWN:
		{
			switch (wParam) {
			case VK_RIGHT:
			{
				if (GetAsyncKeyState(VK_CONTROL)) {
					prism.moveRight(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
				else {
					pyramid.moveRight(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			return 0;
			
			case VK_LEFT:
			{
				if (GetAsyncKeyState(VK_CONTROL)) {
					prism.moveLeft(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
				else {
					pyramid.moveLeft(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			return 0;

			case VK_UP:
			{
				if (GetAsyncKeyState(VK_CONTROL)) {
					prism.moveUp(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
				else {
					pyramid.moveUp(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			return 0;

			case VK_DOWN:
			{
				if (GetAsyncKeyState(VK_CONTROL)) {
					prism.moveDown(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
				else {
					pyramid.moveDown(10);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			return 0;

			case int('X'):
			{{
					if (GetAsyncKeyState(VK_CONTROL)) {
						prism.turnX(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						pyramid.turnX(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;

			case int('Y'):
			{ {
					if (GetAsyncKeyState(VK_CONTROL)) {
						prism.turnY(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						pyramid.turnY(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;

			case int('Z'):
			{ {
					if (GetAsyncKeyState(VK_CONTROL)) {
						prism.turnZ(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						pyramid.turnZ(10);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;

			case int('W'):
			{ {
					if (GetAsyncKeyState(VK_CONTROL)) {
						prism.scale(1.15, 1.15, 1.15);;
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						pyramid.scale(1.15, 1.15, 1.15);;
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;

			case int('S'):
			{ {
					if (GetAsyncKeyState(VK_CONTROL)) {
						prism.scale(0.85, 0.85, 0.85);
						InvalidateRect(hWnd, NULL, FALSE);
					}
					else {
						pyramid.scale(0.85, 0.85, 0.85);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}}
			return 0;
			}}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = L"MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	//if'ы на обработку сообщений
	{if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	if (hwnd = CreateWindow(wc.lpszClassName, L"Компьютерная графика КР", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr), hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE; }
	ShowWindow(hwnd, mCmdShow);
	UpdateWindow(hwnd);
	//цикл обработки сообщений
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//возврат точки входа
	return static_cast<int>(msg.wParam);
}