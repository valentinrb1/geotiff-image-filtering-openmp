/**
 * @file main.h
 * 
 * @brief Main header file.
 * 
 * @author Robledo, Valentín
 * @date May 2023
 * @version 1.0
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef __MAIN_H__
#define __MAIN_H__

#include "functions.h"

/**
 * @brief Sets the process.
 * 
 * If macro PARALLEL_EXECUTION is defined, it will be executed in parallel mode, creating a thread for each band.
 * Otherwise, it will be executed in serial mode.
 * 
 * @param dataset_in Dataset from which the bands will be read.
 * @param dataset_out Dataset where the bands will be written.
 * @param x_size Width.
 * @param y_size Height.
*/
void set_process(GDALDatasetH dataset_in, GDALDatasetH dataset_out, int x_size, int y_size);

#ifdef PARALLEL_EXECUTION
    /**
     * @brief Processes a band.
     * 
     * Reads a band, filters it and writes it.
     * 
     * @param dataset_in Dataset from which the band will be read.
     * @param dataset_out Dataset where the band will be written.
     * @param read_mutex Mutex for reading.
     * @param write_mutex Mutex for writing.
     * @param x_size Width.
     * @param y_size Height.
     * @param band_index Index of the band that will be processed.
    */
    void img_process(GDALDatasetH dataset_in, GDALDatasetH dataset_out, omp_lock_t* read_mutex, omp_lock_t* write_mutex, int x_size, int y_size, int band_index);
#else
    /**
     * @brief Processes a band.
     * 
     * Reads a band, filters it and writes it.
     * 
     * @param dataset_in Dataset from which the band will be read.
     * @param dataset_out Dataset where the band will be written.
     * @param x_size Width.
     * @param y_size Height.
     * @param band_index Index of the band that will be processed.
    */
    void img_process(GDALDatasetH dataset_in, GDALDatasetH dataset_out, int x_size, int y_size, int band_index);
#endif

#endif // __MAIN_H__