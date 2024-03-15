#include "Mask.h"
#include "ImgProcessLib.h"

MSK setEmMask(uint8 Ksize)
{
    MSK retMask;
    double** Mask = retMask.Mptr;
    if (Ksize % 2 == 0) Ksize++;
    retMask.Ksize = Ksize;

    Malloc2DArr(retMask.Mptr, Ksize, Ksize);
    printf("m");
    for (int y = 0; y < Ksize; y++) {
        for (int x = 0; x < Ksize; x++) {
            if (y > x) Mask[y][x] = 1.0;
            if (y < x) Mask[y][x] = -1.0;
            if (y == x) Mask[y][x] = 0.0;
        }
    }
    return retMask;
}