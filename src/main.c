/**
 * @file main.c
 * 
 * @brief Main source file. Sets the process and call the reading, filtering and writing functions.
 * 
 * @author Robledo, Valentín
 * @date May 2023
 * @version 1.0
 * 
 * @copyright Copyright (c) 2023
 */

#include "../inc/main.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Invalid arguments.\n");
        exit(EXIT_FAILURE);
    }
    
    GDALAllRegister();

    GDALDatasetH dataset_in = GDALOpen(realpath(argv[1], NULL), GA_ReadOnly);
    
    if(dataset_in == NULL)
    {
        printf("Error opening the image.\n%s\n", strerror(errno));
        
        exit(EXIT_FAILURE);
    }

    int x_size = GDALGetRasterXSize(dataset_in);
    int y_size = GDALGetRasterYSize(dataset_in);
    
    GDALDatasetH dataset_out = GDALCreate(GDALGetDriverByName("GTiff"), argv[2], x_size, y_size, 3, GDT_Byte, NULL);
    
    if(dataset_out == NULL)
    {
        printf("Error creating the image.\n%s\n", strerror(errno));

        exit(EXIT_FAILURE);
    }
    
    #ifdef PARALLEL_EXECUTION
        printf("\033[0;34mExecuting in parallel mode.\n\033[0m");

        set_process(dataset_in, dataset_out, x_size, y_size);
    #else
        printf("\033[0;34mExecuting in serial mode.\n\033[0m");

        set_process(dataset_in, dataset_out, x_size, y_size);
    #endif

    GDALClose(dataset_in);
    GDALClose(dataset_out);

    return EXIT_SUCCESS;
}

#ifdef PARALLEL_EXECUTION
    void set_process(GDALDatasetH dataset_in, GDALDatasetH dataset_out, int x_size, int y_size)
    {   
        double start_time, end_time, elapsed_time;

        start_time = omp_get_wtime();

        omp_lock_t read_mutex;
        omp_lock_t write_mutex;

        omp_init_lock(&read_mutex);
        omp_init_lock(&write_mutex);

        #pragma omp parallel num_threads(3)
        {
            #pragma omp single
            {
                #pragma omp task
                {
                    img_process(dataset_in, dataset_out, &read_mutex, &write_mutex, x_size, y_size, 1);
                }
                #pragma omp task
                {
                    img_process(dataset_in, dataset_out, &read_mutex, &write_mutex, x_size, y_size, 2);
                }
                #pragma omp task
                {
                    img_process(dataset_in, dataset_out, &read_mutex, &write_mutex, x_size, y_size, 3);
                }
            }
        }

        omp_destroy_lock(&read_mutex);
        omp_destroy_lock(&write_mutex);

        end_time = omp_get_wtime();

        elapsed_time = end_time - start_time;

        printf("\n\033[0;32mProgram complete. Runtime:\033[0;32m %.2f[s]\n", elapsed_time);
    }
#else
    void set_process(GDALDatasetH dataset_in, GDALDatasetH dataset_out, int x_size, int y_size)
    {
        clock_t start_time, end_time;
        double elapsed_time;

        start_time = clock();

        img_process(dataset_in, dataset_out, x_size, y_size, 1);
        img_process(dataset_in, dataset_out, x_size, y_size, 2);
        img_process(dataset_in, dataset_out, x_size, y_size, 3);

        end_time = clock();

        elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("\n\033[0;32mProgram complete. Runtime:\033[0;32m %.2f[s]\n", elapsed_time);
    }
#endif

#ifdef PARALLEL_EXECUTION
    void img_process(GDALDatasetH dataset_in, GDALDatasetH dataset_out, omp_lock_t* read_mutex, omp_lock_t* write_mutex, int x_size, int y_size, int band_index)
    {
        float* band = (float*)CPLMalloc((unsigned long)y_size * (unsigned long)x_size * sizeof(float));

        omp_set_lock(read_mutex);

        read_band(dataset_in, &band, x_size, y_size, band_index);

        omp_unset_lock(read_mutex);

        float* filtered_band = filter_band(band, x_size, y_size, band_index);

        omp_set_lock(write_mutex);

        write_band(dataset_out, filtered_band, x_size, y_size, band_index);

        omp_unset_lock(write_mutex);

        CPLFree(band);
        CPLFree(filtered_band);
    }
#else
    void img_process(GDALDatasetH dataset_in, GDALDatasetH dataset_out, int x_size, int y_size, int band_index)
    {
        float* band = (float*)CPLMalloc((unsigned long)y_size * (unsigned long)x_size * sizeof(float));

        read_band(dataset_in, &band, x_size, y_size, band_index);

        float* filtered_band = filter_band(band, x_size, y_size, band_index);

        write_band(dataset_out, filtered_band, x_size, y_size, band_index);

        CPLFree(band);
        CPLFree(filtered_band);
    }
#endif