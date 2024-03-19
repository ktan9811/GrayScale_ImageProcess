#include "Mask.h"
#include "ImgProcessLib.h"

MSK setEmMask(int Ksize)
{
    MSK retMask;
    retMask.Ksize = Ksize;

    if (Ksize % 2 == 0) Ksize++;
    retMask.Ksize = Ksize;
    retMask.Mptr = MallocMSK(retMask);

    for (int y = 0; y < Ksize; y++) {
        for (int x = 0; x < Ksize; x++) {
            if (y > x)
                retMask.Mptr[y][x] = -1.0;
            else if (x > y)
                retMask.Mptr[y][x] = 1.0;
            else
                retMask.Mptr[y][x] = 0.0;
        }
    }



    return retMask;
}

MSK setAvgMask(int Ksize)
{
    MSK retMask;
    retMask.Ksize = Ksize;

    if (Ksize % 2 == 0) Ksize++;
    retMask.Ksize = Ksize;
    retMask.Mptr = MallocMSK(retMask);

    for (int y = 0; y < Ksize; y++) {
        for (int x = 0; x < Ksize; x++) {
            retMask.Mptr[y][x] = 1.0 / Ksize / Ksize;
        }
    }
    return retMask;
}

MSK setXEMask(int Ksize)
{
    MSK retMask;
    retMask.Ksize = Ksize;

    if (Ksize % 2 == 0) Ksize++;
    retMask.Ksize = Ksize;
    retMask.Mptr = MallocMSK(retMask);

    for (int y = 0; y < Ksize; y++) {
        for (int x = 0; x < Ksize; x++) {
            if (x == 0) retMask.Mptr[y][x] = -1.0;
            else if (x == 2) retMask.Mptr[y][x] = 1.0;
            else retMask.Mptr[y][x] = 0.0;
        }
    }


    return retMask;
}