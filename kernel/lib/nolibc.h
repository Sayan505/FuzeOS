#pragma once


#include <lib/stdtypes.h>


// ref: https://github.com/torvalds/linux/blob/master/tools/include/nolibc/nolibc.h AND glibc source

// memory
__attribute__((unused))
static int memcmp(const VOID *s1, const VOID *s2, UINT64 n_bytes) {
    UINT64 ofs = 0;
	CHAR   c1 = 0;

	while (ofs < n_bytes && !(c1 = ((CHAR *)s1)[ofs] - ((CHAR *)s2)[ofs])) {
		ofs++;
	}
	return c1;
}

__attribute__((unused))
static void* memcpy(void* dest, const void* src, UINT64 n_bytes) {
    char *pszDest = (char *)dest;
    const char *pszSource = (const char *)src;
    
    if((pszDest !=  NULL) && (pszSource != NULL)) {
        while(n_bytes) {
            *(pszDest++) = *(pszSource++);

            --n_bytes;
        }
    }
    return dest;
}

__attribute__((unused))
static void* memset(VOID *dest, BYTE data_8, UINT64 n_bytes) {
	BYTE *p = (BYTE *)dest;

	while (n_bytes--)
		*(p++) = data_8;

	return dest;
}

__attribute__((unused))
static void* zero_memory(VOID *dest, UINT64 n_bytes) {
	BYTE *p = (BYTE *)dest;

	while (n_bytes--)
        *(p++) = NULL;

	return dest;
}


// strings
__attribute__((unused))
static CHAR* strcpy(CHAR *dest, const CHAR *src) {
	CHAR *ret = dest;

    while ((*dest++ = *src++));
	return ret;
}

__attribute__((unused))
static VOID strncpy(CHAR* dest, const CHAR* src, UINT64 n_bytes) {
    UINT64 i = 0;

    while(i++ != n_bytes && (*dest++ = *src++));
}

__attribute__((unused))
static INT32 strcmp(const CHAR *str1, const CHAR *str2) {
    const UCHAR *s1 = (const UCHAR *)str1;
    const UCHAR *s2 = (const UCHAR *)str2;
    UCHAR c1, c2;

    do {
        c1 = (UCHAR)*s1++;
        c2 = (UCHAR)*s2++;

        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);

    return c1 - c2;
}

__attribute__((unused))
INT32 strncmp(const CHAR *s1, const CHAR *s2, UINT64 n_bytes) {
    UCHAR c1 = '\0';
    UCHAR c2 = '\0';

    if (n_bytes >= 4) {
        UINT64 n4 = n_bytes >> 2;
        do {
            c1 = (UCHAR)*s1++;
            c2 = (UCHAR)*s2++;
            if (c1 == '\0' || c1 != c2)
                return c1 - c2;

            c1 = (UCHAR)*s1++;
            c2 = (UCHAR)*s2++;
            if (c1 == '\0' || c1 != c2)
                return c1 - c2;

            c1 = (UCHAR)*s1++;
            c2 = (UCHAR)*s2++;
            if (c1 == '\0' || c1 != c2)
                return c1 - c2;

            c1 = (UCHAR)*s1++;
            c2 = (UCHAR)*s2++;
            if (c1 == '\0' || c1 != c2)
                return c1 - c2;
        } while (--n4 > 0);

        n_bytes &= 3;
    }

    while (n_bytes > 0) {
        c1 = (UCHAR)*s1++;
        c2 = (UCHAR)*s2++;

        if (c1 == '\0' || c1 != c2)
            return c1 - c2;
        n_bytes--;
    }

    return c1 - c2;
}
