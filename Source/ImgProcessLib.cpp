#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "ImgProcessLib.h"
#include "dataType.h"


uint8** _2dMalloc(IMG img)
{
	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;

	img.iptr = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		img.iptr[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);
	return img.iptr;
}

void _2dFree(IMG img)
{
	uint8** imptr = img.iptr;
	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;

	if (!imptr) return;

	for (int i = 0; i < HEIGHT; i++)
		free(imptr[i]);
	free(imptr);
}


void ImgPrint(IMG img)
{
	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** ptr = img.iptr;
	HWND hwnd;
	HDC hdc;

	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL);
	char keyIn = 0;
	puts("Printing IMG....... Press 'X' to Quit !");
	while (true) {
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				int px = ptr[i][j];
				SetPixel(hdc, j + 50, i + 250, RGB(px, px, px));
			}
		}
		keyIn = _getch();
		if (keyIn == 'x' || keyIn == 'X') break;
	}
}

IMG ImgLoad(FILE* rfp)
{
	IMG RET;
	int8 route[100] = "./Source/Etc_Raw(squre)/";
	int8 fName[50];
	uint64 fsize;

	printf("Flie Name? ");
	scanf("%s", fName);
	strcat(route, fName);
	strcat(route, ".raw");

	rfp = fopen(route, "rb");
	fseek(rfp, 5L, SEEK_END);
	fsize = ftell(rfp);
	fclose(rfp);
	RET.HEIGHT = RET.WIDTH = (int)sqrt(fsize);

	RET.iptr = (uint8**)malloc(sizeof(uint8*) * RET.HEIGHT);
	for (int i = 0; i < RET.HEIGHT; i++)
		RET.iptr[i] = (uint8*)malloc(sizeof(uint8) * RET.WIDTH);

	rfp = fopen(route, "rb");
	for (int i = 0; i < RET.HEIGHT; i++)
		fread(RET.iptr[i], sizeof(uint8), RET.WIDTH, rfp);
	fclose(rfp);

	return RET;
}

void ImgSave(IMG img, FILE* wfp)
{
	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** ptr = img.iptr;

	int8 route[100] = "./Source/Etc_Raw(squre)/";
	int8 fName[50];

	printf("Flie Name? ");
	scanf("%s", fName);
	strcat(route, fName);
	strcat(route, ".raw");

	wfp = fopen(route, "wb");
	for (int i = 0; i < HEIGHT; i++)
		fwrite(ptr, sizeof(unsigned char), WIDTH, wfp);
	fclose(wfp);
	printf("Saved! \n");
	return;
}


IMG ImgCopy(IMG img) {
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = _2dMalloc(RET);
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[y][x] = imptr[y][x];
		}
	}
	return RET;
}

IMG ImgAdd(IMG img, uint8 val) {
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = _2dMalloc(RET);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (imptr[y][x] < 255 - val) {
				RET.iptr[y][x] = imptr[y][x] + val;
			}
			else imptr[y][x] = 255;
		}
	}
	return RET;
}

IMG ImgSub(IMG img, uint8 val) {
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = _2dMalloc(RET);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (imptr[y][x] < val) {
				RET.iptr[y][x] = imptr[y][x] - val;
			}
			else RET.iptr[y][x] = 0;
		}
	}
	return RET;
}

IMG ImgInv(IMG img) {
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = _2dMalloc(RET);

	RET.iptr = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		RET.iptr[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[y][x] = 255 - imptr[y][x];
		}
	}

	return RET;
}

//void ImgBin() {
//	dst = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
//	for (int i = 0; i < HEIGHT; i++)
//		dst[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);
//
//	char mode = 0;
//	uint8 point = 0;
//	puts("0. Bin by Avg, 1. Bin By Mid, 2. Bin by UserInput");
//	printf("Select Mode : ");
//	mode = getCh();
//
//	if (mode == '0')	point = RetAvg();
//	else if (mode == '1') point = RetMid();
//	else point = getUint8();
//
//	for (int y = 0; y < HEIGHT; y++) {
//		for (int x = 0; x < WIDTH; x++) {
//			if (src[y][x] < point) {
//				dst[y][x] = 0;
//			}
//			else dst[y][x] = 255;
//		}
//	}
//	printf("point : %d\n", point);
//}
//
//void ImgGamma()
//{
//	float gamma;
//	printf("Write Gamma Value : 0.2 ~ 1.8\nValue ? : ");
//	scanf("%f", &gamma);
//
//	if (gamma < 0.2 || gamma > 1.8) return;
//
//	dst = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
//	for (int i = 0; i < HEIGHT; i++)
//		dst[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);
//
//
//	for (int y = 0; y < HEIGHT; y++) {
//		for (int x = 0; x < WIDTH; x++) {
//			dst[y][x] = (uint8)(255 * pow(255 / src[y][x], gamma));
//		}
//	}
//}