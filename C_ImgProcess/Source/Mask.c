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

MSK setXMask(int Ksize)
{
    MSK retMask;
    retMask.Ksize = Ksize;

    if (Ksize % 2 == 0) Ksize++;
    retMask.Ksize = Ksize;
    retMask.Mptr = MallocMSK(retMask);

    for (int y = 0; y < Ksize; y++) {
        for (int x = 0; x < Ksize; x++) {
            retMask.Mptr[y][x] = 0.0;
        }
    }
    retMask.Mptr[1][1] = -1.0;
    retMask.Mptr[1][2] = 1.0;


    return retMask;
}

MSK setYMask(int Ksize)
{
    MSK retMask;
    retMask.Ksize = Ksize;

    if (Ksize % 2 == 0) Ksize++;
    retMask.Ksize = Ksize;
    retMask.Mptr = MallocMSK(retMask);

    for (int y = 0; y < Ksize; y++) {
        for (int x = 0; x < Ksize; x++) {
            retMask.Mptr[y][x] = 0.0;
        }
    }
    retMask.Mptr[1][1] = -1.0;
    retMask.Mptr[2][1] = 1.0;


    return retMask;
}

MSK setPrewittXEMask(int Ksize)
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

MSK setPrewittYEMask(int Ksize)
{
    MSK retMask;
    retMask.Ksize = Ksize;

    if (Ksize % 2 == 0) Ksize++;
    retMask.Ksize = Ksize;
    retMask.Mptr = MallocMSK(retMask);

    for (int y = 0; y < Ksize; y++) {
        for (int x = 0; x < Ksize; x++) {
            if (y == 0) retMask.Mptr[y][x] = -1.0;
            else if (y == 2) retMask.Mptr[y][x] = 1.0;
            else retMask.Mptr[y][x] = 0.0;
        }
    }


    return retMask;
}
