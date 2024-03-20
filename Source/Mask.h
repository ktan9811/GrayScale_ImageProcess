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

MSK setXMask(int Ksize);

MSK setYMask(int Ksize);

MSK setPrewittXEMask(int Ksize);

MSK setPrewittYEMask(int Ksize);