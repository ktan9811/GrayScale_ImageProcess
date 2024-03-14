#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "dataType.h"
#include "utility.h"

// Memory Allocation
uint8** _2dMalloc(IMG img);
void _2dFree(IMG img);

// IMG FILE IO
void ImgPrint(IMG img);
IMG ImgLoad(FILE* rfp);
void ImgSave(IMG img, FILE* wfp);


// 拳家 痢 贸府 (Point Processing)
IMG ImgCopy(IMG img);
IMG ImgAdd(IMG img, uint8 Val); 
IMG ImgSub(IMG img, uint8 Val);

IMG ImgInv(IMG img); 
IMG ImgBin(IMG img); 
IMG ImgGamma(IMG img);

// 扁窍切 贸府 (Geometric Processing)
IMG ZoomIn2(IMG img);
IMG ZoomOut2(IMG img);

IMG ReverseX(IMG img);
//IMG ReverseY(IMG img);

//IMG MoveXY(IMG img);
IMG RotateDegree(IMG img);

// 康开 贸府 (Area Processing)


// 橇饭烙 贸府 (Frame Processing)