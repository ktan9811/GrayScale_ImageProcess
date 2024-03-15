#pragma once
#include <iostream>
#include "dataType.h"

struct MSK
{
	double** Mptr;
	int Ksize;
};

MSK setEmMask(uint8 Ksize);