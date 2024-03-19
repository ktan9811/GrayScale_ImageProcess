#pragma once
#include <stdio.h>
#include "dataType.h"

typedef struct
{
	double** Mptr;
	int Ksize;
}MSK;

MSK setEmMask(int Ksize);

MSK setAvgMask(int Ksize);

MSK setXEMask(int Ksize);