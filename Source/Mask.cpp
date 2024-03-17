#include "Mask.h"
#include "ImgProcessLib.h"

MSK setEmMask(uint8 Ksize)
{
    MSK retMask;
    retMask.Ksize = Ksize;

    //if (Ksize % 2 == 0) Ksize++;
    retMask.Ksize = Ksize;
    retMask.Mptr = MallocMSK(retMask);

    for (int y = 0; y < Ksize; y++) {
        for (int x = 0; x < Ksize; x++) {
            printf("%d %d\n", y, x);
            if (y > x) retMask.Mptr[y][x] = 1.0;
            if (y < x) retMask.Mptr[y][x] = -1.0;
            if (y == x) retMask.Mptr[y][x] = 0.0;
        }
    }
    return retMask;
}