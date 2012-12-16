#include "ylpfile.h"
#include <stdio.h>
#include <stdlib.h>

int readylp(const char * filename, SComplex * c)
{
    FILE * file;
    unsigned i, aa, bb, cc, a, b, d;
    Simplex ** temp;

    file = fopen(filename, "r");
    if (file == NULL) return 1;

    /* read vertices */
    fscanf(file, "%u", c->dim);
    c->e[0] = calloc(c->dim[0], sizeof(Simplex));
    if (c->e[0] == NULL) return 2;
    for (i = 0; i < c->dim[0]; ++i)
    {
        fscanf(file, "%f %f %f",
               &(c->e[0][i].x), &(c->e[0][i].y), &(c->e[0][i].z));
        c->e[0][i].face = NULL, c->e[0][i].cofaceNum = 0;
    }

    /* read edges */
    fscanf(file, "%u", c->dim+1);
    c->e[1] = calloc(c->dim[1], sizeof(Simplex));
    if (c->e[1] == NULL) return 2;
    for (i = 0; i < c->dim[1]; ++i)
    {
        c->e[1][i].face = calloc(2, sizeof(Simplex *));
        if (c->e[1][i].face == NULL) return 2;

        fscanf(file, "%u %u", &a, &b);
        c->e[1][i].face[0] = c->e[0]+a, c->e[1][i].face[1] = c->e[0]+b;
        c->e[1][i].cofaceNum = 0;

        temp = realloc(c->e[0][a].coface,
                       sizeof(Simplex *)*(++(c->e[0][a].cofaceNum)));
        if (temp == NULL) return 2;
        c->e[0][a].coface = temp;
        c->e[0][a].coface[c->e[0][a].cofaceNum - 1] = c->e[1] + i;

        temp = realloc(c->e[0][b].coface,
                       sizeof(Simplex *)*(++(c->e[0][b].cofaceNum)));
        if (temp == NULL) return 2;
        c->e[0][b].coface = temp;
        c->e[0][b].coface[c->e[0][b].cofaceNum - 1] = c->e[1] + i;
    }

    /* read triangles */
    fscanf(file, "%u", c->dim+2);
    c->e[2] = calloc(c->dim[2], sizeof(Simplex));
    if (c->e[2] == NULL) return 2;
    for (i = 0; i < c->dim[2]; ++i)
    {
        c->e[2][i].face = calloc(3, sizeof(Simplex *));
        if (c->e[2][i].face == NULL) return 2;

        fscanf(file, "%u %u %u %u %u %u", &aa, &bb, &cc, &a, &b, &d);
        c->e[2][i].a = aa;
        c->e[2][i].b = bb;
        c->e[2][i].c = cc;
        c->e[2][i].face[0] = c->e[1] + a;
        c->e[2][i].face[1] = c->e[1] + b;
        c->e[2][i].face[2] = c->e[1] + d;
        c->e[2][i].cofaceNum = 0, c->e[2][i].coface = NULL;

        temp = realloc(c->e[1][a].coface,
                       sizeof(Simplex *)*(++(c->e[1][a].cofaceNum)));
        if (temp == NULL) return 2;
        c->e[1][a].coface = temp;
        c->e[1][a].coface[c->e[1][a].cofaceNum - 1] = c->e[2] + i;

        temp = realloc(c->e[1][b].coface,
                       sizeof(Simplex *)*(++(c->e[1][b].cofaceNum)));
        if (temp == NULL) return 2;
        c->e[1][b].coface = temp;
        c->e[1][b].coface[c->e[1][b].cofaceNum - 1] = c->e[2] + i;

        temp = realloc(c->e[1][d].coface,
                       sizeof(Simplex *)*(++(c->e[1][d].cofaceNum)));
        if (temp == NULL) return 2;
        c->e[1][d].coface = temp;
        c->e[1][d].coface[c->e[1][d].cofaceNum - 1] = c->e[2] + i;
    }

    fclose(file);
    return 0;
}
