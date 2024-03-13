#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include "dataType.h"
//#include "ImgProcessLib.h"


// 변수

int line = 0;

int HEIGHT, WIDTH;

uint8** src, **dst;
FILE* rfp;
FILE* wfp;
uint16 modeCnt[256] = { 0, };


// 전방선언
int RetMid();
int RetAvg();
uint8 getUint8();
char getCh();
void ImgCopy();
void ImgAdd(uint8 Val);
void ImgSub(uint8 Val);
void ImgInv();
void ImgBin();
void PrintMenu();
void ImgPrint();
void ImgLoad();
void ImgSave();

int main()
{
	char inKey = 0;

	while (inKey != '9') {
		PrintMenu();
		inKey = getCh();
		switch (inKey)
		{
		case '0':
			ImgLoad();
			ImgPrint();
			break;

		case '1':
			ImgSave();
			break;

		case 'a':
		case 'A':
			printf("Copy Src to Dst\n");
			ImgCopy();
			ImgPrint();
			break;

		case 'b':
		case 'B': 
			printf("Img Bright\n");
			ImgAdd(getUint8());
			ImgPrint();
			break;

		case 'c':
		case 'C':
			printf("Img Dark\n");
			ImgSub(getUint8());
			ImgPrint();
			break;

		case 'd':
		case 'D': 
			printf("Img Inverse\n");
			ImgInv();
			ImgPrint();
			break;

		case 'e':
		case 'E': 
			printf("Img Binary\n");
			ImgBin();
			ImgPrint();
			break;

		case 'x':
		case 'X':
			return 0;
		default:
			break;
		}
	}

	for (int i = 0; i < HEIGHT; i++) {
		free(src[i]);
		free(dst[i]);
	}
	free(src);
	free(dst);
	return 0;
}

// 함수 선언부

int RetMid() {
	int mode, mid = 0;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			modeCnt[src[y][x]] += 1;
		}
	}
	int tempVal = 0;

	for (int i = 0; i < 256; i++) {
		if (tempVal < modeCnt[i]) {
			tempVal = modeCnt[i];
			mode = i;
		}
	}

	int tempCnt = 0;
	for (int i = 0; i < 256; i++) {
		tempCnt += modeCnt[i];
		if (tempCnt >= (int)(WIDTH * HEIGHT / 2)) {
			mid = i;
			break;
		}
	}
	return mid;
}

int RetAvg() {
	int sum = 0;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			sum += src[y][x];
		}
	}
	return sum / (HEIGHT * WIDTH);
}

uint8 getUint8()
{
	uint8 inKey;
	printf("Value ? : ");
	scanf("%hhu", &inKey);
	return inKey;
}

char getCh()
{
	char inKey = _getch();
	system("cls");
	return inKey;
}

void ImgCopy() {
	dst = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		dst[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			dst[y][x] = src[y][x];
		}
	}
}

void ImgAdd(uint8 val) {
	dst = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		dst[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (src[y][x] < 255 - val) {
				dst[y][x] = src[y][x] + val;
			}
			else dst[y][x] = 255;
		}
	}
}

void ImgSub(uint8 val) {
	dst = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		dst[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (src[y][x] < val) {
				dst[y][x] = src[y][x] - val;
			}
			else dst[y][x] = 0;
		}
	}
}

void ImgInv() {
	dst = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		dst[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			dst[y][x] = 255 - src[y][x];
		}
	}
}

void ImgBin() {
	dst = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		dst[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);

	char mode = 0;
	uint8 point = 0;
	puts("0. Bin by Avg, 1. Bin By Mid, 2. Bin by UserInput");
	printf("Select Mode : ");
	mode = getCh();

	if (mode == '0')	point = RetAvg();
	else if (mode == '1') point = RetMid();
	else point = getUint8();

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (src[y][x] < point) {
				dst[y][x] = 0;
			}
			else dst[y][x] = 255;
		}
	}
	printf("point : %d\n", point);
}

void PrintMenu()
{
	puts("GrayScale IMG Processing\n");
	puts("0.Open, 1.Save 2.Close\n");
	puts("A.Copy, B.Bright, C.Dark, D.Inverse, E.BinByPoint, X.Quit\n");
}

void ImgPrint()
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
				int px = dst[i][j];
				SetPixel(hdc, j + 50, i + 250, RGB(px, px, px));
			}
		}
		keyIn = _getch();
		if (keyIn == 'x' || keyIn == 'X') break;
	}

}

void ImgLoad()
{
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
	HEIGHT = WIDTH = (int)sqrt(fsize);

	src = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		src[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);

	rfp = fopen(route, "rb");
	for (int i = 0; i < HEIGHT; i++)
		fread(src[i], sizeof(uint8), WIDTH, rfp);
	fclose(rfp);

	ImgCopy();
}

void ImgSave()
{
	int8 route[100] = "./Source/Etc_Raw(squre)/";
	int8 fName[50];
	
	printf("Flie Name? ");
	scanf("%s", fName);
	strcat(route, fName);
	strcat(route, ".raw");

	wfp = fopen(route, "wb");
	for (int i = 0; i < HEIGHT; i++)
		fwrite(dst[i], sizeof(unsigned char), WIDTH, wfp);
	fclose(wfp);
	printf("Saved! \n");
	return;
}
