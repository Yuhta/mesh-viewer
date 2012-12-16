#include "viewer.h"
#include "ylpfile.h"
#include "scomplex.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    SComplex c;

    if (argc != 2)
    {
        fprintf(stderr, "Command format:\n %s input-file-name\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (readylp(argv[1], &c) == 1)
    {
        fprintf(stderr, "Cannot open file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    view(&argc, argv, &c);
    clearSComplex(&c);

    return EXIT_SUCCESS;
}
