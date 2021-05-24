#ifndef __MNIST_API_IMPL_C__
#define __MNIST_API_IMPL_C__

#include "MNIST_API.h"

//* MNIST images size (28*28) *//
#define IMAGE_SIZE 784

//* info about file "train-images.idx3-ubyte" *//
typedef struct {
    uint32_t magicNumber;
	uint32_t nrOfImages;
    uint32_t nrOfRows;
	uint32_t nrOfColumns;
} MNIST_TRAIN_HEAD;

//* info about file "train-labels.idx1-ubyte" *//
typedef struct {
    uint32_t magicNumber;
    uint32_t numberOfItems;
} MNIST_TRAIN_LABEL;

static MNIST_TRAIN_HEAD * restrict train_head = NULL;
static MNIST_TRAIN_LABEL * restrict train_label = NULL;

static MNIST_TRAIN_HEAD * restrict test_head = NULL;
static MNIST_TRAIN_LABEL * restrict test_label = NULL;


static uint8_t * restrict trainPixels = NULL;
static uint8_t * restrict trainLabels = NULL;

static uint8_t * restrict testPixels = NULL;
static uint8_t * restrict testLabels = NULL;

void mnistapi_initTesting() {
    FILE * imageFile = fopen(MNIST_TEST_IMAGES_FILE, "rb");
    FILE * labelsFile = fopen(MNIST_TEST_LABELS_FILE, "rb");

	if( ( !imageFile ) || ( !labelsFile ) ) {
		printf("No such file or files\nTesting MNIST API can't load.\n");
		if (imageFile) fclose(imageFile);
		if (labelsFile) fclose(labelsFile);
		return;
	}

	srand(time(NULL));

	test_head = (MNIST_TRAIN_HEAD*)malloc(sizeof(MNIST_TRAIN_HEAD));
	test_label = (MNIST_TRAIN_LABEL*)malloc(sizeof(MNIST_TRAIN_LABEL));

    fread(test_head, sizeof(uint32_t), 4, imageFile);
    mnistapi_reverseUInt32_t(&test_head->magicNumber);
    mnistapi_reverseUInt32_t(&test_head->nrOfColumns);
    mnistapi_reverseUInt32_t(&test_head->nrOfImages);
    mnistapi_reverseUInt32_t(&test_head->nrOfRows);

    fread(test_label, sizeof(uint32_t), 2, labelsFile);
    mnistapi_reverseUInt32_t(&test_label->magicNumber);
    mnistapi_reverseUInt32_t(&test_label->numberOfItems);

    testPixels = (uint8_t*)malloc(sizeof(uint8_t) * (IMAGE_SIZE * test_head->nrOfImages));
    fread(testPixels, sizeof(uint8_t), IMAGE_SIZE * test_head->nrOfImages, imageFile);
    testLabels = (uint8_t*)malloc(sizeof(uint8_t) * test_label->numberOfItems);
    fread(testLabels, sizeof(uint8_t), test_label->numberOfItems, labelsFile);

	fclose(imageFile);
    fclose(labelsFile);
}

void mnistapi_closeTesting() {
    free(testPixels);
    free(testLabels);
    free(test_head);
    free(test_label);
}

void mnistapi_initTraining() {
    FILE * imageFile = fopen(MNIST_TRAIN_IMAGES_FILE, "rb");
    FILE * labelsFile = fopen(MNIST_TRAIN_LABELS_FILE, "rb");

	if( ( !imageFile ) || ( !labelsFile ) ) {
		printf("No such file or files\nTraining MNIST API can't load.\n");
		if (imageFile) fclose(imageFile);
		if (labelsFile) fclose(labelsFile);
		return;
	}

	srand(time(NULL));

	train_head = (MNIST_TRAIN_HEAD*)malloc(sizeof(MNIST_TRAIN_HEAD));
	train_label = (MNIST_TRAIN_LABEL*)malloc(sizeof(MNIST_TRAIN_LABEL));

    fread(train_head, sizeof(uint32_t), 4, imageFile);
    mnistapi_reverseUInt32_t(&train_head->magicNumber);
    mnistapi_reverseUInt32_t(&train_head->nrOfColumns);
    mnistapi_reverseUInt32_t(&train_head->nrOfImages);
    mnistapi_reverseUInt32_t(&train_head->nrOfRows);

    fread(train_label, sizeof(uint32_t), 2, labelsFile);
    mnistapi_reverseUInt32_t(&train_label->magicNumber);
    mnistapi_reverseUInt32_t(&train_label->numberOfItems);

    trainPixels = (uint8_t*)malloc(sizeof(uint8_t) * (IMAGE_SIZE * train_head->nrOfImages));
    fread(trainPixels, sizeof(uint8_t), IMAGE_SIZE * train_head->nrOfImages, imageFile);
    trainLabels = (uint8_t*)malloc(sizeof(uint8_t) * train_label->numberOfItems);
    fread(trainLabels, sizeof(uint8_t), train_label->numberOfItems, labelsFile);

	fclose(imageFile);
    fclose(labelsFile);
}

void mnistapi_closeTraining() {
    free(trainPixels);
    free(trainLabels);
    free(train_head);
    free(train_label);
}

void mnistapi_printImage(uint32_t* matrix) {
    for(uint32_t j = 0; j < IMAGE_SIZE; j++) {
        printf("%u ", matrix[j]);
        if(((j+1) % 28) == 0) putchar('\n');
    }
    putchar('\n');
}
void mnistapi_printImageWithOneAndZero(uint32_t* matrix) {
    for(uint32_t j = 0; j < IMAGE_SIZE; j++) {
        if( matrix[j] > 0 ) {
            printf("1 ");
        } else {
            printf("0 ");
        }
        if(((j+1) % 28) == 0) putchar('\n');
    }
    putchar('\n');
}

uint32_t* mnistapi_getRandomTrainImage(void) {
    uint32_t randNumber = rand() % train_label->numberOfItems;
    uint32_t* image = (uint32_t*)malloc(sizeof(uint32_t) * IMAGE_SIZE);
    register uint32_t j = 0;
    for(uint32_t i = randNumber * IMAGE_SIZE; i < (randNumber * IMAGE_SIZE) + IMAGE_SIZE; i++) {
        image[j] = trainPixels[i];
        j++;
    }
    return image;
}

uint32_t* mnistapi_getRandomTestImage(void) {
    uint32_t randNumber = rand() % test_label->numberOfItems;
    uint32_t* image = (uint32_t*)malloc(sizeof(uint32_t) * IMAGE_SIZE);
    register uint32_t j = 0;
    for(uint32_t i = randNumber * IMAGE_SIZE; i < (randNumber * IMAGE_SIZE) + IMAGE_SIZE; i++) {
        image[j] = testPixels[i];
        j++;
    }
    return image;
}


uint32_t* mnistapi_getRandomTrainImageByNumber(uint32_t number) {
    if (number > 9) return NULL;
    uint32_t randNumber = 0;
    uint32_t* image = (uint32_t*)malloc(sizeof(uint32_t) * IMAGE_SIZE);
    register uint32_t j = 0;

    do {
        randNumber = rand() % train_label->numberOfItems;
    } while(trainLabels[randNumber] != number);

    for(uint32_t i = randNumber * IMAGE_SIZE; i < (randNumber * IMAGE_SIZE) + IMAGE_SIZE; i++) {
        image[j] = trainPixels[i];
        j++;
    }
    return image;
}

uint32_t* mnistapi_getRandomTestImageByNumber(uint32_t number) {
    if (number > 9) return NULL;
    uint32_t randNumber = 0;
    uint32_t* image = (uint32_t*)malloc(sizeof(uint32_t) * IMAGE_SIZE);
    register uint32_t j = 0;

    do {
        randNumber = rand() % test_label->numberOfItems;
    } while(testLabels[randNumber] != number);

    for(uint32_t i = randNumber * IMAGE_SIZE; i < (randNumber * IMAGE_SIZE) + IMAGE_SIZE; i++) {
        image[j] = testPixels[i];
        j++;
    }
    return image;
}

void mnistapi_reverseUInt32_t(uint32_t * a) {
    register unsigned char byte = 0;
    register unsigned char *offset = NULL;
    offset = (unsigned char *) a;
    byte = *(offset);
    *(offset) = *(offset + 3);
    *(offset + 3) = byte;
    byte = *(offset + 1);
    *(offset + 1) = *(offset + 2);
    *(offset + 2) = byte;
}

void mnistapi_printTestImageInfo() {
	printf(
        "MNIST test head:\n"
        "Magic number = %u \n"
        "Nr of images = %u \n"
        "Nr of rows = %u \n"
		"Nr of columns = %u \n\n"
		"MNIST test label:\n"
        "Magic number = %d\n"
        "Nr of items = %d\n\n",
		test_head->magicNumber,
		test_head->nrOfImages,
		test_head->nrOfRows,
		test_head->nrOfColumns,
        test_label->magicNumber,
        test_label->numberOfItems);
}

void mnistapi_printTrainImageInfo() {
	printf(
        "MNIST train head:\n"
        "Magic number = %u \n"
        "Nr of images = %u \n"
        "Nr of rows = %u \n"
		"Nr of columns = %u \n\n"
		"MNIST train label:\n"
        "Magic number = %d\n"
        "Nr of items = %d\n\n",
		train_head->magicNumber,
		train_head->nrOfImages,
		train_head->nrOfRows,
		train_head->nrOfColumns,
        train_label->magicNumber,
        train_label->numberOfItems);
}

#endif // __MNIST_API_IMPL_C__
