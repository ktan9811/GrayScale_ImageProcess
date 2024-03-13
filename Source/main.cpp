#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include "dataType.h"
#include "ImgProcessLib.h"

#define HEIGHT 512
#define WIDTH 512

// 변수

int line = 0;
uint8 src[HEIGHT][WIDTH];
uint8 dst[HEIGHT][WIDTH];
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
			ImgPrint(dst);
			break;

		case '1':
			ImgSave();
			break;

		case 'a':
		case 'A':
			printf("Copy Src to Dst\n");
			ImgCopy();
			ImgPrint(dst);
			break;

		case 'b':
		case 'B': 
			printf("Img Bright\n");
			ImgAdd(getUint8());
			ImgPrint(dst);
			break;

		case 'c':
		case 'C':
			printf("Img Dark\n");
			ImgSub(getUint8());
			ImgPrint(dst);
			break;

		case 'd':
		case 'D': 
			printf("Img Inverse\n");
			ImgInv();
			ImgPrint(dst);
			break;

		case 'e':
		case 'E': 
			printf("Img Binary\n");
			ImgBin();
			ImgPrint(dst);
			break;

		case 'x':
		case 'X':
			return 0;
		default:
			break;
		}
	}
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
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			dst[y][x] = src[y][x];
		}
	}
}

void ImgAdd(uint8 val) {
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
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			dst[y][x] = 255 - src[y][x];
		}
	}
}

void ImgBin() {
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

void ImgLoad()
{
	int8 route[100] = "./Source/Pet_RAW(squre)/Pet_RAW(512x512)/";
	int8 fName[50];
	printf("Flie Name? ");
	scanf("%s", fName);
	strcat(route, fName);
	strcat(route, "_512.raw");

	rfp = fopen(route, "rt");
	fread(src, 1, HEIGHT * WIDTH, rfp);
	fclose(rfp);
	ImgCopy();
}

void ImgSave()
{
	int8 route[100] = "./Source/Pet_RAW(squre)/Pet_RAW(512x512)/";
	int8 fName[50];
	
	printf("Flie Name? ");
	scanf("%s", fName);
	strcat(route, fName);
	strcat(route, "_512.raw");

	wfp = fopen(route, "wb");
	for (int i = 0; i < HEIGHT; i++)
		fwrite(dst[i], sizeof(unsigned char), WIDTH, wfp);
	fclose(wfp);
	printf("Saved! \n");
	return;
}
