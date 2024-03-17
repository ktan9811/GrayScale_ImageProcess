#pragma once
#include <iostream>
#include "dataType.h"

struct MSK
{
	double** Mptr = nullptr;
	uint8 Ksize = 3;
};

MSK setEmMask(uint8 Ksize);