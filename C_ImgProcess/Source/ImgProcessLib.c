#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include "ImgProcessLib.h"
#include "dataType.h"



uint8** MallocImg(IMG img)
{
	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;

	img.iptr = (uint8**)malloc(sizeof(uint8*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		img.iptr[i] = (uint8*)malloc(sizeof(uint8) * WIDTH);
	return img.iptr;
}

void FreeImg(IMG img)
{
	uint8** imptr = img.iptr;
	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;

	if (!imptr) return;

	for (int i = 0; i < HEIGHT; i++)
		free(imptr[i]);
	free(imptr);
}



double** MallocMSK(MSK mask)
{
	int HEIGHT = mask.Ksize;
	int WIDTH = mask.Ksize;

	mask.Mptr = (double**)malloc(sizeof(double*) * HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
		mask.Mptr[i] = (double*)malloc(sizeof(double) * WIDTH);

	return mask.Mptr;
}

void FreeMask(MSK mask)
{
	double** mptr = mask.Mptr;
	int HEIGHT = mask.Ksize;

	if (!mptr) return;

	for (int i = 0; i < HEIGHT; i++)
		free(mptr[i]);
	free(mptr);
}



void ImgPrint(IMG img)
{
	system("cls");
	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** ptr = img.iptr;
	HWND hwnd;
	HDC hdc;

	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL);

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int px = ptr[i][j];
			SetPixel(hdc, j + 50, i + 250, RGB(px, px, px));
		}
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
	RET.HEIGHT = (uint64)sqrt(fsize);
	RET.WIDTH = (uint64)sqrt(fsize);

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

	int8 route[100] = "./Source/Out(squre)/";
	int8 fName[50];

	printf("Flie Name? ");
	scanf("%s", fName);
	strcat(route, fName);
	strcat(route, ".raw");

	wfp = fopen(route, "wb");
	for (int i = 0; i < HEIGHT; i++)
		fwrite(ptr[i], sizeof(uint8), WIDTH, wfp);
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

	RET.iptr = MallocImg(RET);
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

	RET.iptr = MallocImg(RET);

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

	RET.iptr = MallocImg(RET);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (imptr[y][x] > val) {
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

	RET.iptr = MallocImg(RET);

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

IMG ImgBin(IMG img) {
	
	char mode = 0;
	uint8 point = 0;
	puts("0. Bin by Avg, 1. Bin By Mid, 2. Bin by UserInput");
	printf("Select Mode : ");
	mode = getCh();

	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = MallocImg(RET);


	if (mode == '0')	point = RetAvg(img);
	else if (mode == '1') point = RetMid(img);
	else point = getUint8();

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (imptr[y][x] < point) {
				RET.iptr[y][x] = 0;
			}
			else RET.iptr[y][x] = 255;
		}
	}
	printf("point : %d\n", point);

	return RET;
}

IMG ImgGamma(IMG img)
{
	float gamma;
	printf("Write Gamma Value : 0.2 ~ 1.8\nValue ? : ");
	scanf("%f", &gamma);

	if (gamma < 0.2 || gamma > 1.8) return img;

	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = MallocImg(RET);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[y][x] = (uint8)(255 * pow(imptr[y][x] / 255.0f, gamma));
		}
	}

	return RET;
}

IMG HistStretch(IMG img)
{
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = MallocImg(RET);

	uint8 high = 0, low = 255;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (imptr[y][x] > high) high = imptr[y][x];
			if (imptr[y][x] < low) low = imptr[y][x];
		}
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[y][x] = (uint8)(((imptr[y][x] - low) / (float)(high - low)) * 255);
		}
	}

	return RET;
}

IMG HistEqual(IMG img)
{
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = MallocImg(RET);

	
	int Hist[256] = {0, };
	int HistSum[256] = {0, };

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++)
			Hist[imptr[y][x]]++;
	}

	for (int i = 1; i < 256; i++) {
		HistSum[i] = HistSum[i - 1] + Hist[i];
	}

	double HistNorm[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		HistNorm[i] = HistSum[i] * (1.0 / (HEIGHT * WIDTH)) * 255.0;
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[y][x] = (uint8)HistNorm[imptr[y][x]];
		}
	}
	return RET;
}

IMG HistNorm(IMG img)
{
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = MallocImg(RET);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[y][x] = imptr[y][x];
		}
	}
	return RET;
}


IMG ZoomIn2(IMG img)
{
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = (int)(HEIGHT * 2);
	RET.WIDTH = (int)(WIDTH * 2);

	RET.iptr = MallocImg(RET);

	for (int y = 0; y < RET.HEIGHT; y++) {
		for (int x = 0; x < RET.WIDTH; x++) {
			RET.iptr[y][x] = imptr[y/2][x/2];
		}
	}

	return RET;
}

IMG ZoomOut2(IMG img)
{
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = (int)(HEIGHT / 2);
	RET.WIDTH = (int)(WIDTH / 2);

	RET.iptr = MallocImg(RET);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[(int)(y / 2)][(int)(x / 2)] = imptr[y][x];
		}
	}
	return RET;
}

IMG ReverseX(IMG img)
{
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = MallocImg(RET);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[y][x] = imptr[y][x];
		}
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH / 2; x++) {
			RET.iptr[y][x] ^= RET.iptr[y][WIDTH - x - 1];
			RET.iptr[y][WIDTH - x - 1] ^= RET.iptr[y][x];
			RET.iptr[y][x] ^= RET.iptr[y][WIDTH - x - 1];
		}
	}
	return RET;
}

IMG ReverseY(IMG img)
{
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = MallocImg(RET);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[y][x] = imptr[y][x];
		}
	}

	for (int y = 0; y < HEIGHT / 2; y++) {
		for (int x = 0; x < WIDTH; x++) {
			RET.iptr[y][x] ^= RET.iptr[HEIGHT - y - 1][x];
			RET.iptr[HEIGHT - y - 1][x] ^= RET.iptr[y][x];
			RET.iptr[y][x] ^= RET.iptr[HEIGHT - y - 1][x];
		}
	}
	return RET;
}

IMG RotateDegree(IMG img)
{
	IMG RET;

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;

	RET.iptr = MallocImg(RET);
	
	uint8 degree = getUint8();
	double radian = -degree * 3.141592 / 180.0;

	int cx = HEIGHT / 2;
	int cy = WIDTH / 2;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int xd = y;
			int yd = x;

			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < RET.HEIGHT) && (0 <= ys && ys < RET.WIDTH))
				RET.iptr[xd][yd] = imptr[xs][ys];
		}
	}
	return RET;
}

IMG Embossing(IMG img)
{
	IMG RET;
	
	// 마스크 생성
	MSK Mask, INTEMP, OUTTEMP;
	int ksize;
	printf("Write K Size\n");
	ksize = getKSize();
	Mask = setEmMask(ksize);

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;
	RET.iptr = MallocImg(RET);

	INTEMP.Ksize = HEIGHT + ksize - 1;
	INTEMP.Mptr = MallocMSK(INTEMP);

	OUTTEMP.Ksize = HEIGHT;
	OUTTEMP.Mptr = MallocMSK(OUTTEMP);

	//TEMP 초기화
	double val = 127;
	for (int y = 0; y < INTEMP.Ksize; y++) {
		for (int x = 0; x < INTEMP.Ksize; x++) {
			INTEMP.Mptr[y][x] = val;
		}
	}

	for (int y = (int)(ksize / 2); y < HEIGHT + (int)(ksize / 2); y++) {
		for (int x = (int)(ksize / 2); x < WIDTH + (int)(ksize / 2); x++) {
			INTEMP.Mptr[y][x] = imptr[y - (int)(ksize / 2)][x - (int)(ksize / 2)];
		}
	}

	// 회선 연산
	double S;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			S = 0.0;
			for (int i = 0; i < Mask.Ksize; i++) {
				for (int j = 0; j < Mask.Ksize; j++) {
					S += Mask.Mptr[i][j] * INTEMP.Mptr[y + i][x + j];
				}
			}
			OUTTEMP.Mptr[y][x] = S;
		}
	}

	// 출력값 보정
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			OUTTEMP.Mptr[y][x] += 127.0;
		}
	}

	// 출력 이미지 생성
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (OUTTEMP.Mptr[y][x] < 0.0) RET.iptr[y][x] = 255;
			else if (OUTTEMP.Mptr[y][x] > 255.0) RET.iptr[y][x] = 255;
			else RET.iptr[y][x] = (uint8)OUTTEMP.Mptr[y][x];
		}
	}

	//마스크와 임시 그림 Free
	FreeMask(Mask);
	FreeMask(INTEMP);
	FreeMask(OUTTEMP);
	return RET;
}

IMG AvgBlur(IMG img)
{
	IMG RET;

	// 마스크 생성
	MSK Mask, INTEMP;
	
	// 커널입력
	int ksize;
	printf("Write K Size\n");
	ksize = getKSize();
	Mask = setAvgMask(ksize);

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;
	RET.iptr = MallocImg(RET);

	INTEMP.Ksize = HEIGHT + ksize - 1;
	INTEMP.Mptr = MallocMSK(INTEMP);

	// TEMP 초기화
	double val = 127;
	for (int y = 0; y < INTEMP.Ksize; y++) {
		for (int x = 0; x < INTEMP.Ksize; x++) {
			INTEMP.Mptr[y][x] = val;
		}
	}

	for (int y = (int)(ksize / 2); y < HEIGHT + (int)(ksize / 2); y++) {
		for (int x = (int)(ksize / 2); x < WIDTH + (int)(ksize / 2); x++) {
			INTEMP.Mptr[y][x] = imptr[y - (int)(ksize / 2)][x - (int)(ksize / 2)];
		}
	}

	double S;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			S = 0.0;
			for (int i = 0; i < Mask.Ksize; i++) {
				for (int j = 0; j < Mask.Ksize; j++) {
					S += Mask.Mptr[i][j] * INTEMP.Mptr[y + i][x + j];
				}
			}
			RET.iptr[y][x] = S;
		}
	}


	// 마스크와 임시 그림 Free
	FreeMask(Mask);
	FreeMask(INTEMP);
	return RET;
}

IMG XEdge(IMG img)
{
	IMG RET;

	// 마스크 생성
	MSK Mask, INTEMP, OUTTEMP;
	int ksize = 3;
	Mask = setXMask(ksize);

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;
	RET.iptr = MallocImg(RET);

	INTEMP.Ksize = HEIGHT + ksize - 1;
	INTEMP.Mptr = MallocMSK(INTEMP);

	OUTTEMP.Ksize = HEIGHT;
	OUTTEMP.Mptr = MallocMSK(OUTTEMP);

	//TEMP 초기화
	double val = 127;
	for (int y = 0; y < INTEMP.Ksize; y++) {
		for (int x = 0; x < INTEMP.Ksize; x++) {
			INTEMP.Mptr[y][x] = val;
		}
	}

	for (int y = (int)(ksize / 2); y < HEIGHT + (int)(ksize / 2); y++) {
		for (int x = (int)(ksize / 2); x < WIDTH + (int)(ksize / 2); x++) {
			INTEMP.Mptr[y][x] = imptr[y - (int)(ksize / 2)][x - (int)(ksize / 2)];
		}
	}

	// 회선 연산
	double S;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			S = 0.0;
			for (int i = 0; i < Mask.Ksize; i++) {
				for (int j = 0; j < Mask.Ksize; j++) {
					S += Mask.Mptr[i][j] * INTEMP.Mptr[y + i][x + j];
				}
			}
			OUTTEMP.Mptr[y][x] = S;
		}
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (OUTTEMP.Mptr[y][x] < 0.0) RET.iptr[y][x] = 0;
			else if (OUTTEMP.Mptr[y][x] > 255.0) RET.iptr[y][x] = 255;
			else RET.iptr[y][x] = (uint8)OUTTEMP.Mptr[y][x];
		}
	}

	//마스크와 임시 그림 Free
	FreeMask(Mask);
	FreeMask(INTEMP);
	FreeMask(OUTTEMP);
	return RET;
}

IMG YEdge(IMG img)
{
	IMG RET;

	// 마스크 생성
	MSK Mask, INTEMP, OUTTEMP;
	int ksize = 3;
	Mask = setYMask(ksize);

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;
	RET.iptr = MallocImg(RET);

	INTEMP.Ksize = HEIGHT + ksize - 1;
	INTEMP.Mptr = MallocMSK(INTEMP);

	OUTTEMP.Ksize = HEIGHT;
	OUTTEMP.Mptr = MallocMSK(OUTTEMP);

	//TEMP 초기화
	double val = 127;
	for (int y = 0; y < INTEMP.Ksize; y++) {
		for (int x = 0; x < INTEMP.Ksize; x++) {
			INTEMP.Mptr[y][x] = val;
		}
	}

	for (int y = (int)(ksize / 2); y < HEIGHT + (int)(ksize / 2); y++) {
		for (int x = (int)(ksize / 2); x < WIDTH + (int)(ksize / 2); x++) {
			INTEMP.Mptr[y][x] = imptr[y - (int)(ksize / 2)][x - (int)(ksize / 2)];
		}
	}

	// 회선 연산
	double S;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			S = 0.0;
			for (int i = 0; i < Mask.Ksize; i++) {
				for (int j = 0; j < Mask.Ksize; j++) {
					S += Mask.Mptr[i][j] * INTEMP.Mptr[y + i][x + j];
				}
			}
			OUTTEMP.Mptr[y][x] = S;
		}
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (OUTTEMP.Mptr[y][x] < 0.0) RET.iptr[y][x] = 0;
			else if (OUTTEMP.Mptr[y][x] > 255.0) RET.iptr[y][x] = 255;
			else RET.iptr[y][x] = (uint8)OUTTEMP.Mptr[y][x];
		}
	}

	//마스크와 임시 그림 Free
	FreeMask(Mask);
	FreeMask(INTEMP);
	FreeMask(OUTTEMP);
	return RET;
}


IMG PrewittXEdge(IMG img)
{
	IMG RET;

	// 마스크 생성
	MSK Mask, INTEMP, OUTTEMP;
	int ksize = 3;
	Mask = setPrewittXEMask(ksize);

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;
	RET.iptr = MallocImg(RET);

	INTEMP.Ksize = HEIGHT + ksize - 1;
	INTEMP.Mptr = MallocMSK(INTEMP);

	OUTTEMP.Ksize = HEIGHT;
	OUTTEMP.Mptr = MallocMSK(OUTTEMP);

	//TEMP 초기화
	double val = 127;
	for (int y = 0; y < INTEMP.Ksize; y++) {
		for (int x = 0; x < INTEMP.Ksize; x++) {
			INTEMP.Mptr[y][x] = val;
		}
	}

	for (int y = (int)(ksize / 2); y < HEIGHT + (int)(ksize / 2); y++) {
		for (int x = (int)(ksize / 2); x < WIDTH + (int)(ksize / 2); x++) {
			INTEMP.Mptr[y][x] = imptr[y - (int)(ksize / 2)][x - (int)(ksize / 2)];
		}
	}

	// 회선 연산
	double S;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			S = 0.0;
			for (int i = 0; i < Mask.Ksize; i++) {
				for (int j = 0; j < Mask.Ksize; j++) {
					S += Mask.Mptr[i][j] * INTEMP.Mptr[y + i][x + j];
				}
			}
			OUTTEMP.Mptr[y][x] = S;
		}
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (OUTTEMP.Mptr[y][x] < 0.0) RET.iptr[y][x] = 0;
			else if (OUTTEMP.Mptr[y][x] > 255.0) RET.iptr[y][x] = 255;
			else RET.iptr[y][x] = (uint8)OUTTEMP.Mptr[y][x];
		}
	}

	//마스크와 임시 그림 Free
	FreeMask(Mask);
	FreeMask(INTEMP);
	FreeMask(OUTTEMP);
	return RET;
}

IMG PrewittYEdge(IMG img)
{
	IMG RET;

	// 마스크 생성
	MSK Mask, INTEMP, OUTTEMP;
	int ksize = 3;
	Mask = setPrewittYEMask(ksize);

	int HEIGHT = img.HEIGHT;
	int WIDTH = img.WIDTH;
	uint8** imptr = img.iptr;

	RET.HEIGHT = HEIGHT;
	RET.WIDTH = WIDTH;
	RET.iptr = MallocImg(RET);

	INTEMP.Ksize = HEIGHT + ksize - 1;
	INTEMP.Mptr = MallocMSK(INTEMP);

	OUTTEMP.Ksize = HEIGHT;
	OUTTEMP.Mptr = MallocMSK(OUTTEMP);

	//TEMP 초기화
	double val = 127;
	for (int y = 0; y < INTEMP.Ksize; y++) {
		for (int x = 0; x < INTEMP.Ksize; x++) {
			INTEMP.Mptr[y][x] = val;
		}
	}

	for (int y = (int)(ksize / 2); y < HEIGHT + (int)(ksize / 2); y++) {
		for (int x = (int)(ksize / 2); x < WIDTH + (int)(ksize / 2); x++) {
			INTEMP.Mptr[y][x] = imptr[y - (int)(ksize / 2)][x - (int)(ksize / 2)];
		}
	}

	// 회선 연산
	double S;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			S = 0.0;
			for (int i = 0; i < Mask.Ksize; i++) {
				for (int j = 0; j < Mask.Ksize; j++) {
					S += Mask.Mptr[i][j] * INTEMP.Mptr[y + i][x + j];
				}
			}
			OUTTEMP.Mptr[y][x] = S;
		}
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (OUTTEMP.Mptr[y][x] < 0.0) RET.iptr[y][x] = 0;
			else if (OUTTEMP.Mptr[y][x] > 255.0) RET.iptr[y][x] = 255;
			else RET.iptr[y][x] = (uint8)OUTTEMP.Mptr[y][x];
		}
	}

	//마스크와 임시 그림 Free
	FreeMask(Mask);
	FreeMask(INTEMP);
	FreeMask(OUTTEMP);
	return RET;
}
