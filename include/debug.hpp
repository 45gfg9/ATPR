#ifndef __ATPR_DEBUG_HPP__
#define __ATPR_DEBUG_HPP__

#ifdef ATPR_DBGEN

#include <stdio.h>

#pragma message "Debug is enabled"

// use .init section?
void debugInit();

#define ATPRDBG(...) fprintf(stderr, __VA_ARGS__)

#else

#define debugInit()
#define ATPRDBG(...)

#endif

#endif
