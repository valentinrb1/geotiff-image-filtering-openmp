Laboratorio IV Sistemas Operativos 2 
### Ingeniería en Computación - FCEFyN - UNC
# Shared Memory

## Introduction
Electronic integration levels have allowed the generation of multiprocessor, multicore, hybrid and now many integrated core (MIC) processors. This advance makes it necessary for programmers to have a deep knowledge of the hardware on which their programs are executed, and that these programs can no longer be single-process (paradigm shift).

Among the most widely used techniques and standards for shared memory and distributed memory systems are OpenMP and MPI respectively.

## Objective
The objective of this practical work is for the student to be able to design a solution that uses the distributed memory paradigm, using OpenMP, in C language, that manages to maximize performance and reduce execution time, according to the hardware available to do so.

## Development

A [file](https://drive.google.com/file/d/1uQYAZNlU2lIeRw2yqQuFdvkyCIhliZhy/view?usp=share_link) is delivered in _GeoTif_ format of an image from the *Sentinel 2* satellite over the center of the Province of Córdoba. Within this file, there are the 3 RGB channels together with a lot of metadata about georeferencing and about the capture. The channels are presented in monochrome matrices, one per channel, which together form the RGB composite image shown.

There are numerous image processing algorithms based on image convolutions with a kernel. You are asked to implement an algorithm that applies an edge filter ([edge filter](https://en.wikipedia.org/wiki/Kernel_(image_processing))), as detailed below.

The filtered image is obtained from the convolution

$$ g(x, y) = \omega * f(x, y) = \sum_{dx=-a}^a \sum_{dy=-b}^b \omega(dx, dy)f(x-dx, y-dy) $$

Where $g(x, y)$ is the filtered image, $f(x, y)$ is the original image and $\omega$ is the kernel with boundaries $−a <= dx <= a$ and $−b <= dy <= b$.

### Restrictions
- A program in C language is implemented that has as input the 3 matrices R, G and B.

- That the output has a filtered image by input channel.

- The images must be treated as matrices in _M x N_, monochrome (a single matrix per channel) and you can use the library [gdal](https://gdal.org/) to open the GeoTiff, you can also convert them into a friendly format for the task (eg, [PGM](https://netpbm.sourceforge.net/doc/pgm.html)), or any other of your liking.

- The design must contemplate all situations not described in this document and a correct error handling must be done.

- The design must be dynamic, and must adapt to different images of different sizes.

### Correction Criteria
- The code must be compiled with the following compilation flags:
-Wall -Pedantic -Werror -Wextra -Wconversion -std=gnu11
- Correct memory management.
- Divide the code into modules judiciously.
- Code style.
- Error handling
- The code must not contain errors or warnings.
- The code must not contain cppcheck errors.

## Delivery
As a methodology to solve this problem, it is requested that, first, a design be made that is a solution to the problem without exploiting parallelism (procedural), perform metrics. Then, from this, perform a new implementation that performs the process through the use of the OpenMP library, exploiting the parallelism of the problem. To do this, it is required to recognize what type of parallelism the problem in question exhibits and then, design the solution to it by determining which data/operations can be parallelized. The level of parallelism achieved will be taken into account.

The submission is made through the GitHub repository and the completion of the same must be demonstrated through correct use. The repository must provide the source files and any other files associated with the compilation, “Makefile” project files and the correctly documented code. It must not contain any files associated with IDE projects and it must be assumed that the project can be compiled and run by a `tty` in a Linux distribution with the typical development tools. A report must also be submitted (which can be in MD in the repo) explaining step by step the development, including graphics of the proposed solution design, justifying at all times what was implemented.
It must also be investigated what free profiling utilities exist and what each one provides (a chapter of the report), choosing one to perform the execution time measurements of the designed application.

The report (markdown) must contain graphics and comparison analysis between procedural and distributed execution, showing the scalability and speedup of the same (one, two, four processes, etc.). The report must also contain the solution design and the comparison of profilers.

## Links
- [Introduction to parallel programming](https://hpc.llnl.gov/documentation/tutorials/introduction-parallel-computing-tutorial)
- [OpenMP Tutorial](https://hpc-tutorials.llnl.gov/openmp/)
