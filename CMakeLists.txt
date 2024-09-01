cmake_minimum_required(VERSION 3.22)
project(Lab4)

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/imgs)

set(CMAKE_C_COMPILER gcc)

get_filename_component(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE) #get absolute path to project root directory
set(BIN_DIR "${PROJECT_ROOT_DIR}/bin") #set bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}) #set bin directory as output directory

set(SOURCES ./src/main.c ./src/functions.c)
set(HEADERS ./inc/main.h ./inc/functions.h ./inc/common.h)

add_executable(filter ${SOURCES} ${HEADERS})

target_compile_options(filter PRIVATE -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11 -g -fopenmp)
target_link_libraries(filter PRIVATE gdal -fopenmp)