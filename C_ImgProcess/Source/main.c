#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
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
	srcImg.iptr = NULL;
	dstImg.iptr = NULL;

	char inKey = 0;

	while (inKey != '9') {
		PrintMenu();
		inKey = getCh();
		switch (inKey)
		{
		case '0':
			FreeImg(srcImg);
			srcImg = ImgLoad(rfp);
			ImgPrint(srcImg);
			break;

		case '1':
			ImgSave(dstImg, wfp);
			break;

		case '2':
			FreeImg(srcImg);
			srcImg = ImgCopy(dstImg);
			break;

		case 'a': case 'A':
			ImgPrint(srcImg);
			break;

		case 'b': case 'B':
			FreeImg(dstImg);
			dstImg = ImgAdd(srcImg, getUint8());
			ImgPrint(dstImg);
			break;

		case 'c': case 'C':
			FreeImg(dstImg);
			dstImg = ImgSub(srcImg, getUint8());
			ImgPrint(dstImg);
			break;

		case 'd': case 'D': 
			FreeImg(dstImg);
			dstImg = ImgInv(srcImg);
			ImgPrint(dstImg);
			break;

		case 'e': case 'E': 
			FreeImg(dstImg);			
			dstImg = ImgBin(srcImg);
			ImgPrint(dstImg);
			break;

		case 'f': case 'F':
			FreeImg(dstImg);
			dstImg = ImgGamma(srcImg);
			ImgPrint(dstImg);
			break;

		case 'g': case 'G':
			FreeImg(dstImg);
			dstImg = ZoomIn2(srcImg);
			ImgPrint(dstImg);
			break;

		case 'h': case 'H':
			FreeImg(dstImg);
			dstImg = ZoomOut2(srcImg);
			ImgPrint(dstImg);
			break;

		case 'i': case 'I':
			FreeImg(dstImg);
			dstImg = ReverseX(srcImg);
			ImgPrint(dstImg);
			break;

		case 'p': case 'P':
			FreeImg(dstImg);
			dstImg = ReverseY(srcImg);
			ImgPrint(dstImg);
			break;

		case 'j': case 'J':
			FreeImg(dstImg);
			dstImg = RotateDegree(srcImg);
			ImgPrint(dstImg);
			break;

		case 'k': case 'K':
			FreeImg(dstImg);
			dstImg = HistStretch(srcImg);
			ImgPrint(dstImg);
			break;

		case 'l': case 'L':
			FreeImg(dstImg);
			dstImg = HistEqual(srcImg);
			ImgPrint(dstImg);
			break;

		case 'm': case 'M':
			FreeImg(dstImg);
			dstImg = Embossing(srcImg);
			ImgPrint(dstImg);
			break;

		case 'n': case 'N':
			FreeImg(dstImg);
			dstImg = AvgBlur(srcImg);
			ImgPrint(dstImg);
			break;

		case 'o': case 'O':
			FreeImg(dstImg);
			dstImg = XEdge(srcImg);
			ImgPrint(dstImg);
			break;

		case 'Q': case 'q':
			FreeImg(dstImg);
			dstImg = YEdge(srcImg);
			ImgPrint(dstImg);
			break;

		case 'r': case 'R':
			FreeImg(dstImg);
			dstImg = PrewittXEdge(srcImg);
			ImgPrint(dstImg);
			break;

		case 's': case 'S':
			FreeImg(dstImg);
			dstImg = PrewittYEdge(srcImg);
			ImgPrint(dstImg);
			break;


		case 'x': case 'X':
			FreeImg(srcImg);
			FreeImg(dstImg);
			return 0;
		}
	}

	FreeImg(srcImg);
	FreeImg(dstImg);
	return 0;
}