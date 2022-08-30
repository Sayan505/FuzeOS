#pragma once


/*    for x86_64    */

// native length (64-bits)
typedef unsigned long long int UINTN;
typedef unsigned long long int UINT64;
typedef unsigned long long int QWORD;

typedef signed long long int   INTN;
typedef signed long long int   INT64;

typedef unsigned long int      uint64_t;    // for compat


// byte (8-bits)
typedef unsigned char BYTE;
typedef unsigned char UCHAR;
typedef unsigned char UINT8;

typedef signed   char INT8;
typedef signed   char SBYTE;        // signed byte

typedef char          CHAR;
typedef char          SCHAR;

typedef unsigned char uint8_t;      // for compat


// word (16-bits)
typedef unsigned short WORD;
typedef unsigned short UINT16;

typedef signed   short INT16;

typedef unsigned short uint16_t;    // for compat


// double-word (32-bits)
typedef unsigned int DWORD;
typedef unsigned int UINT32;

typedef signed   int INT32;

typedef unsigned int uint32_t;      // for compat


// void
typedef void VOID;

// NULL
#define NULL ('\0')

// mem addr
typedef void* PHYS_ADDR;
typedef void* VIRT_ADDR;
typedef void* ADDR;
