/**
 * @file common.h
 * 
 * @brief Common header file.
 * 
 * @author Robledo, Valentín
 * @date May 2023
 * @version 1.0
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <gdal/gdal.h>
#include <gdal/cpl_conv.h>

/* Defininig this macro will execute the program in parallel mode. 
   Otherwise, it will be executed in serial mode.*/
#define PARALLEL_EXECUTION

#ifdef PARALLEL_EXECUTION
    #include <omp.h>
#else
    #include <time.h>
#endif

#endif // __COMMON_H__