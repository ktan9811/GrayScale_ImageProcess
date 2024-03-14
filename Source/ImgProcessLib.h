#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "dataType.h"
#include "utility.h"

struct IMG
{
	uint8** iptr = nullptr;
	int HEIGHT = 0, WIDTH = 0;
};

// Mem
uint8** _2dMalloc(IMG img);
void _2dFree(IMG img);

//FILE
void ImgPrint(IMG img);
IMG ImgLoad(FILE* rfp);
void ImgSave(IMG img, FILE* wfp);


IMG ImgCopy(IMG img);
IMG ImgAdd(IMG img, uint8 Val); 
IMG ImgSub(IMG img, uint8 Val); 
IMG ImgInv(IMG img); 
void ImgBin(); 
void ImgGamma();