#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include "dataType.h"
#include "ImgProcessLib.h"
#include "utility.h"


// 변수

int line = 0;

FILE* rfp;
FILE* wfp;
uint16 modeCnt[256] = { 0, };

// 전방선언
//void ImgCopy(); void ImgAdd(uint8 Val); void ImgSub(uint8 Val); void ImgInv(); void ImgBin(); void ImgGamma();




int main()
{
	IMG srcImg;
	IMG dstImg;

	char inKey = 0;

	while (inKey != '9') {
		PrintMenu();
		inKey = getCh();
		switch (inKey)
		{
		case '0':
			srcImg = ImgLoad(rfp);
			ImgPrint(srcImg);
			break;

		case '1':
			ImgSave(dstImg, wfp);
			break;

		case 'a':
		case 'A':
			_2dFree(dstImg);
			printf("Copy Src to Dst\n");
			dstImg = ImgCopy(srcImg);
			//printf("%d %d", dstImg.HEIGHT, dstImg.WIDTH);
			ImgPrint(dstImg);
			break;

		case 'b':
		case 'B':
			_2dFree(dstImg);
			printf("Img Bright\n");
			dstImg = ImgAdd(srcImg, getUint8());
			ImgPrint(dstImg);
			break;

		case 'c':
		case 'C':
			_2dFree(dstImg);
			printf("Img Dark\n");
			dstImg = ImgSub(srcImg, getUint8());
			ImgPrint(dstImg);
			break;

		case 'd':
		case 'D': 
			_2dFree(dstImg);
			printf("Img Inverse\n");
			dstImg = ImgInv(srcImg);
			ImgPrint(dstImg);
			break;

		//case 'e':
		//case 'E': 
		//	printf("Img Binary\n");
		//	ImgBin();
		//	ImgPrint();
		//	break;

		//case 'f':
		//case 'F':
		//	printf("Img Gamma\n");
		//	ImgGamma();
		//	ImgPrint();
		//	break;

		case 'x':
		case 'X':
			return 0;
		default:
			break;
		}
	}

	_2dFree(srcImg);
	_2dFree(dstImg);
	return 0;
}

// 함수 선언부

//int RetMid() {
//	int mode, mid = 0;
//	for (int y = 0; y < HEIGHT; y++) {
//		for (int x = 0; x < WIDTH; x++) {
//			modeCnt[src[y][x]] += 1;
//		}
//	}
//	int tempVal = 0;
//
//	for (int i = 0; i < 256; i++) {
//		if (tempVal < modeCnt[i]) {
//			tempVal = modeCnt[i];
//			mode = i;
//		}
//	}
//
//	int tempCnt = 0;
//	for (int i = 0; i < 256; i++) {
//		tempCnt += modeCnt[i];
//		if (tempCnt >= (int)(WIDTH * HEIGHT / 2)) {
//			mid = i;
//			break;
//		}
//	}
//	return mid;
//}
//
//int RetAvg() {
//	int sum = 0;
//	for (int y = 0; y < HEIGHT; y++) {
//		for (int x = 0; x < WIDTH; x++) {
//			sum += src[y][x];
//		}
//	}
//	return sum / (HEIGHT * WIDTH);
//}
