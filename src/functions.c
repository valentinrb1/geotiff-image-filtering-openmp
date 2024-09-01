/**
 * @file functions.c
 * 
 * @brief Functions source file. Reads, filters and writes a band.
 * 
 * @author Robledo, Valentín
 * @date May 2023
 * @version 1.0
 * 
 * @copyright Copyright (c) 2023
*/

#include "../inc/functions.h"

void read_band(GDALDatasetH dataset, float** band_read, int x_size, int y_size, int band_index)
{
    CPLErr err;

    GDALRasterBandH band = GDALGetRasterBand(dataset, band_index);
    
    printf("\nThe reading of the band [%d] has started.\n", band_index);

    err = GDALRasterIO(band, GF_Read, 0, 0, x_size, y_size, *band_read, x_size, y_size, GDT_Float32, 0, 0);
    
    if(err == CE_Failure || err == CE_Fatal)
    {
        printf("Error reading band: %d\nError: %s", band_index, strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("\nThe reading of the band [%d] has finished\n", band_index);
}

float* filter_band(float* band, int x_size, int y_size, int band_index)
{
    const float kernel[9] = 
    {
        -1, -1, -1, 
        -1,  8, -1, 
        -1, -1, -1
    };

    float* filtered_band = (float*)CPLMalloc((unsigned long)y_size * (unsigned long)x_size * sizeof(float));

    printf("\nThe filtering of the band [%d] has started.\n", band_index);
    
    #ifdef PARALLEL_EXECUTION
        #pragma omp parallel for collapse(2)
        for(int i = 1; i < y_size - 1; i++)
        {
            for(int j = 1; j < x_size - 1; j++)
            {
                filtered_band[i * x_size + j] = band[(i - 1) * x_size + (j - 1)] * kernel[0] +
                                                band[(i - 1) * x_size +       j] * kernel[1] +
                                                band[(i - 1) * x_size + (j + 1)] * kernel[2] +
                                                band[ i      * x_size + (j - 1)] * kernel[3] +
                                                band[ i      * x_size +       j] * kernel[4] +
                                                band[ i      * x_size + (j + 1)] * kernel[5] +
                                                band[(i + 1) * x_size + (j - 1)] * kernel[6] +
                                                band[(i + 1) * x_size +       j] * kernel[7] +
                                                band[(i + 1) * x_size + (j + 1)] * kernel[8];
            }
        }
    #else
        for(int i = 1; i < y_size - 1; i++)
        {
            for(int j = 1; j < x_size - 1; j++)
            {
                filtered_band[i * x_size + j] = band[(i - 1) * x_size + (j - 1)] * kernel[0] +
                                                band[(i - 1) * x_size +       j] * kernel[1] +
                                                band[(i - 1) * x_size + (j + 1)] * kernel[2] +
                                                band[ i      * x_size + (j - 1)] * kernel[3] +
                                                band[ i      * x_size +       j] * kernel[4] +
                                                band[ i      * x_size + (j + 1)] * kernel[5] +
                                                band[(i + 1) * x_size + (j - 1)] * kernel[6] +
                                                band[(i + 1) * x_size +       j] * kernel[7] +
                                                band[(i + 1) * x_size + (j + 1)] * kernel[8];
            }
        }
    #endif
    
    printf("\nThe filtering of the band [%d] has finished.\n", band_index);

    return filtered_band;
}

void write_band(GDALDatasetH dataset_out, float* band, int x_size, int y_size, int band_index)
{
    CPLErr err;

    printf("\nThe writing to the band [%d] has started.\n", band_index);

    err = GDALRasterIO(GDALGetRasterBand(dataset_out, band_index), GF_Write, 0, 0, x_size, y_size, band, x_size, y_size, GDT_Float32, 0, 0);

    if(err == CE_Failure || err == CE_Fatal)
    {
        printf("Error writing band: %d\nError: %s", band_index, strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("\nThe writing to the band [%d] has finished.\n", band_index);
}