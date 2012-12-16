#include "scomplex.h"
#include <stdlib.h>
#include <stdio.h>

void clearSComplex(SComplex * c)
{
    unsigned i, j;

    for (i = 0; i < 3; ++i)
        if (c->e[i] != NULL)
        {
            for (j = 0; j < c->dim[i]; ++j)
            {
                if (c->e[i][j].face != NULL)
                {
                    free(c->e[i][j].face);
                    c->e[i][j].face = NULL;
                }
                if (c->e[i][j].coface != NULL)
                {
                    free(c->e[i][j].coface);
                    c->e[i][j].coface = NULL;
                    c->e[i][j].cofaceNum = 0;
                }
            }
            free(c->e[i]);
            c->e[i] = NULL;
        }
}

void printSComplex(const SComplex * c)
{
    unsigned i;

    if (c->e[0] != NULL)
    {
        printf("%u\n", c->dim[0]);
        for (i = 0; i < c->dim[0]; ++i)
            printf("%f %f %f\n", c->e[0][i].x, c->e[0][i].y, c->e[0][i].z);
    }

    if (c->e[1] != NULL)
    {
        printf("%u\n", c->dim[1]);
        for (i = 0; i < c->dim[1]; ++i)
            printf("%u %u\n", c->e[1][i].face[0] - c->e[0],
                              c->e[1][i].face[1] - c->e[0]);
    }

    if (c->e[2] != NULL)
    {
        printf("%u\n", c->dim[2]);
        for (i = 0; i < c->dim[2]; ++i)
            printf("%u %u %u %u %u %u\n", c->e[2][i].a,
                                          c->e[2][i].b,
                                          c->e[2][i].c,
                                          c->e[2][i].face[0] - c->e[1],
                                          c->e[2][i].face[1] - c->e[1],
                                          c->e[2][i].face[2] - c->e[1]);
    }
}
