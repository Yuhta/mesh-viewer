#ifndef _SCOMPLEX_H
#define _SCOMPLEX_H

typedef struct _Simplex Simplex;
struct _Simplex
{
    union
    {
        struct { float x, y, z; };
        struct { unsigned a, b, c; };
    };
    Simplex ** face;
    Simplex ** coface;
    unsigned cofaceNum;
};

typedef struct _SComplex
{
    unsigned dim[3];
    Simplex * e[3];
} SComplex;

void printSComplex(const SComplex * c);

void clearSComplex(SComplex * c);

#endif
