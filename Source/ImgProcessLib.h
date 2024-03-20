#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "dataType.h"
#include "utility.h"
#include "Mask.h"

// Memory Allocation
uint8** MallocImg(IMG img);
void FreeImg(IMG img);

double** MallocMSK(MSK mask);
void FreeMask(MSK mask);

// IMG FILE IO
void ImgPrint(IMG img);
IMG ImgLoad(FILE* rfp);
void ImgSave(IMG img, FILE* wfp);


// ȭ�� �� ó�� (Point Processing)
IMG ImgCopy(IMG img);
IMG ImgAdd(IMG img, uint8 Val); 
IMG ImgSub(IMG img, uint8 Val);

IMG ImgInv(IMG img); 
IMG ImgBin(IMG img); 
IMG ImgGamma(IMG img);

IMG HistStretch(IMG img);
IMG HistEqual(IMG img);
IMG HistNorm(IMG img);

// ������ ó�� (Geometric Processing)
IMG ZoomIn2(IMG img);
IMG ZoomOut2(IMG img);

IMG ReverseX(IMG img);
IMG ReverseY(IMG img);
//IMG MoveXY(IMG img);

IMG RotateDegree(IMG img);


//  ȭ�� ���� ó�� (Area Processing) Convolution / filter
IMG Embossing(IMG img);
IMG AvgBlur(IMG img);
IMG XEdge(IMG img);
IMG YEdge(IMG img);
IMG PrewittXEdge(IMG img);
IMG PrewittYEdge(IMG img);
IMG Gaussian(IMG img);


// ������ ó�� (Frame Processing)