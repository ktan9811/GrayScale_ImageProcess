#pragma once

#define int8 __int8
#define int16 __int16
#define int32 __int32
#define int64 __int64

#define uint8 unsigned __int8
#define uint16 unsigned __int16
#define uint32 unsigned __int32
#define uint64 unsigned __int64

typedef struct
{
	uint8** iptr;
	int HEIGHT, WIDTH;
}IMG;