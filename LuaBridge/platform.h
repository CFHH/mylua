#ifndef _ULUA_PLATFORM_H_
#define _ULUA_PLATFORM_H_


#ifdef _WINDOWS
	typedef signed char sint8;
	typedef unsigned char uint8;
	typedef signed short sint16;
	typedef unsigned short uint16;
	typedef __int32 sint32;
	typedef unsigned __int32 uint32;
	typedef __int64 sint64;
	typedef unsigned __int64 uint64;
#else
	typedef signed char sint8;
	typedef unsigned char uint8;
	typedef signed short sint16;
	typedef unsigned short uint16;
	typedef int sint32;
    typedef unsigned int uint32;
	typedef long long sint64;
	typedef unsigned long long uint64;
#endif

typedef sint8  int8;
typedef sint16 int16;
typedef sint32 int32;
typedef sint64 int64;
typedef int sint;
typedef unsigned int uint;

typedef float float32;
typedef double float64;


#endif

