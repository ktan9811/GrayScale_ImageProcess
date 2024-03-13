#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "ImgProcessLib.h"
#include "dataType.h"

void ImgPrint(uint8 img[][HEIGHT])
{
	HWND hwnd;
	HDC hdc;

	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL);
	char keyIn = 0;
	puts("Printing IMG....... Press 'X' to Quit !");
	while (true) {
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				int px = img[i][j];
				SetPixel(hdc, j + 50, i + 250, RGB(px, px, px));
			}
		}
		keyIn = _getch();
		if (keyIn == 'x' || keyIn =='X') break;
	}
}