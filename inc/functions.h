/**
 * @file functions.h
 * 
 * @brief Functions header file.
 * 
 * @author Robledo, Valentín
 * @date May 2023
 * @version 1.0
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "common.h"

/**
 * @brief Reads a band from a dataset.
 * 
 * Reads a band and stores it in band_read.
 * 
 * @param dataset Dataset from which the band will be read.
 * @param band Pointer to the space where the band will be stored.
 * @param x_size Width.
 * @param y_size Height.
 * @param band_index Index of the band that will be read.
 */
void read_band(GDALDatasetH dataset, float** band_read, int x_size, int y_size, int band_index);

/**
 * @brief Filters a band.
 * 
 * Apply edge filter to a band using a kernel.
 * If macro PARALLEL_EXECUTION is defined, it will be executed in parallel mode.
 * 
 * @param band Band that will be filtered.
 * @param x_size Width.
 * @param y_size Height.
 * @param band_index Index of the band that will be filtered.
*/
float* filter_band(float* band, int x_size, int y_size, int band_index);

/**
 * @brief Writes a band in a dataset.
 * 
 * @param dataset_out Dataset where the band will be written.
 * @param band Band that will be written.
 * @param x_size Width.
 * @param y_size Height.
 * @param band_index Index of the band that will be written.
*/
void write_band(GDALDatasetH dataset_out, float* band, int x_size, int y_size, int band_index);

#endif // __FUNCTIONS_H__