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
