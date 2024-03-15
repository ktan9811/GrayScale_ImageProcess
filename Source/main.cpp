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

FILE* rfp;
FILE* wfp;

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

		case 'a': case 'A':
			_2dFree(dstImg);
			dstImg = ImgCopy(srcImg);
			ImgPrint(dstImg);
			break;

		case 'b': case 'B':
			_2dFree(dstImg);
			dstImg = ImgAdd(srcImg, getUint8());
			ImgPrint(dstImg);
			break;

		case 'c': case 'C':
			_2dFree(dstImg);
			dstImg = ImgSub(srcImg, getUint8());
			ImgPrint(dstImg);
			break;

		case 'd': case 'D': 
			_2dFree(dstImg);
			dstImg = ImgInv(srcImg);
			ImgPrint(dstImg);
			break;

		case 'e': case 'E': 
			_2dFree(dstImg);			
			dstImg = ImgBin(srcImg);
			ImgPrint(dstImg);
			break;

		case 'f': case 'F':
			_2dFree(dstImg);
			dstImg = ImgGamma(srcImg);
			ImgPrint(dstImg);
			break;

		case 'g': case 'G':
			_2dFree(dstImg);
			dstImg = ZoomIn2(srcImg);
			ImgPrint(dstImg);
			break;

		case 'h': case 'H':
			_2dFree(dstImg);
			dstImg = ZoomOut2(srcImg);
			ImgPrint(dstImg);
			break;

		case 'i': case 'I':
			_2dFree(dstImg);
			dstImg = ReverseX(srcImg);
			ImgPrint(dstImg);
			break;

		case 'j': case 'J':
			_2dFree(dstImg);
			dstImg = RotateDegree(srcImg);
			ImgPrint(dstImg);
			break;


		case 'x': case 'X':
			_2dFree(srcImg);
			_2dFree(dstImg);
			return 0;
		}
	}

	_2dFree(srcImg);
	_2dFree(dstImg);
	return 0;
}