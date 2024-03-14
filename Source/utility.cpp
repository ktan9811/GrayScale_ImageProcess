#define _CRT_SECURE_NO_WARNINGS
#include "utility.h"

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

void PrintMenu()
{
	puts("GrayScale IMG Processing\n");
	puts("0.Open, 1.Save 2.Close\n");
	puts("A.Copy, B.Bright, C.Dark, D.Inverse, E.BinByPoint, X.Quit\n");
}

int RetMid(IMG img) {
	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** ptr = img.iptr;

	uint16 modeCnt[256] = { 0, };

	int mode, mid = 0;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			modeCnt[ptr[y][x]] += 1;
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

int RetAvg(IMG img) {
	int sum = 0;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** ptr = img.iptr;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			sum += ptr[y][x];
		}
	}
	return sum / (HEIGHT * WIDTH);
}
