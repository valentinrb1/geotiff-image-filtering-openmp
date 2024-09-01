# Satellite Image Filtering using GeoTiff Format with GDAL and OpenMP

## Date - 2023

### Authors:
- **Robledo, Valentín**

## Abstract
In this project, a satellite image is filtered. This image is in GeoTiff format, which is an image file format that contains geographic information. To carry out this project, the GDAL library was used, which allows reading and writing image files in GeoTiff format. In addition, the OpenMP library was used, achieving parallel image processing.

## How to clone this repository?
You can clone this repository to any directory you want using the following command:

```console
git clone https://github.com/valentinrb1/geotiff-image-filtering-openmp.git
```

## How to use?
First, we move to the project folder.

```console
cd geotiff-image-filtering-openmp
```

Inside the project directory we are going to create a folder called *build*.

```console
mkdir build
```

We move to that folder.
```console
cd build
```

We run the *cmake* command inside the *build* folder.
```console
cmake ..
```

We run the *make* command, to obtain the binary files that are saved inside the *bin* directory.
```console
make
```

To run the program we move to the *imgs* directory where the image to be filtered is located and execute the following command: where the first parameter is the name of the image to be filtered and the second parameter is the name of the filtered image.

```console
../bin/filter <img_to_filter> <img_filtered>
```

Note that within the *common.h* directory there is the *PARALLEL_EXECUTION* macro that allows you to activate or deactivate the parallel execution of the program.

---
## Operation

## Sequential execution
As mentioned above, if we comment out the macro *PARALLEL_EXECUTION* inside the file *common.h* the program will be executed sequentially.

If the program is executed sequentially, the img_process() function will be called three times, once for each band. Within this function the band is read, the filter is applied and the filtered band is written to an output file.

## Parallel execution
If we uncomment the macro *PARALLEL_EXECUTION* inside the file *common.h* the program will be executed in parallel.

In this case, three threads will be created, one for each band. Each thread will call the img_process() function and within this function the band will be read, the filter will be applied and the filtered band will be written to an output file.

## Results
Two different computers were used for the tests, one with more computing power than the other.

Computer 1 specifications:
- Processor: AMD Ryzen 5 3600 4GHz 6-Core Processor.
- RAM: 16GB DDR4 3200MHz.

Computer 2 specifications:
- Processor: Intel(R) Core(TM) i5-3320M CPU @ 2.60GHz 2-Core Processor.
- RAM: 8GB DDR3

Computer 1 results:

| Sequential | Parallel |
| :---: | :---: |
| 0m4.44s | 0m2.14s |

Computer 2 results:

| Sequential | Parallel |
| :---: | :---: |
| 0m13.01s | 0m14.45s |

## Conclusions
We can see that in the case of computer 1, parallel execution is faster than sequential execution, achieving an improvement of 107%. This is mainly due to the number of cores that the processor has, in addition to the clock speed of each core.

In the case of computer 2, we can see that sequential and parallel execution are very similar, even being the parallel form slower, since the cost of parallelizing the program is too much for its technical specifications.
