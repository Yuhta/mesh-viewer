#ifndef _YLPFILE_H
#define _YLPFILE_H

#include "scomplex.h"

/*
 * return values:
 * 0 - successful read
 * 1 - fail to read file
 * 2 - fail to allocate memory
 */
int readylp(const char * filename, SComplex * c);

#endif
