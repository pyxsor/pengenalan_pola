#ifndef __MINST_API_H__
#define __MINST_API_H__

//* printf(), fopen(), FILE, fclose(), putchar() *//
#include <stdio.h>
//* malloc(), free(), srand(), rand() *//
#include <stdlib.h>
//* uint32_t, uint_8_t *//
#include <stdint.h>
//* time() *//
#include <time.h>

#ifdef __linux__ 
    #define MNIST_TRAIN_IMAGES_FILE "data/train-images.idx3-ubyte"
    #define MNIST_TRAIN_LABELS_FILE "data/train-labels.idx1-ubyte"
    #define MNIST_TEST_IMAGES_FILE "data/t10k-images.idx3-ubyte"
    #define MNIST_TEST_LABELS_FILE "data/t10k-labels.idx1-ubyte"
#elif _WIN32
    #define MNIST_TRAIN_IMAGES_FILE "data\\train-images.idx3-ubyte"
    #define MNIST_TRAIN_LABELS_FILE "data\\train-labels.idx1-ubyte"
    #define MNIST_TEST_IMAGES_FILE "data\\t10k-images.idx3-ubyte"
    #define MNIST_TEST_LABELS_FILE "data\\t10k-labels.idx1-ubyte"
#else

#endif


/// Train files
//* initialization of MNIST API, allocating memory and open streaming with read files *//
void mnistapi_initTraining(void);
//* free allocated memory and close file streams *//
void mnistapi_closeTraining(void);
//* print info about file "train-images.idx3-ubyte" on console*//
uint32_t* mnistapi_getRandomTrainImage(void);
uint32_t* mnistapi_getRandomTrainImageByNumber(uint32_t number);
//* print info about file "train-labels.idx1-ubyte" on console*//
void mnistapi_printTrainImageInfo(void);

/// Test files
void mnistapi_initTesting(void);
void mnistapi_closeTesting(void);
uint32_t* mnistapi_getRandomTestImage(void);
uint32_t* mnistapi_getRandomTestImageByNumber(uint32_t number);
void mnistapi_printTestImageInfo(void);

/// Other
//* flip 4 bytes (1 with 4, 2 with 3) *//
void mnistapi_reverseUInt32_t(uint32_t*);
void mnistapi_printImage(uint32_t*);
void mnistapi_printImageWithOneAndZero(uint32_t*);


#endif // __MINST_API_H__
