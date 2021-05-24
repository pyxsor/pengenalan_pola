#include "MNIST_API.h"

int main(void) {
    uint32_t* image = NULL;

    mnistapi_initTraining();
    image = mnistapi_getRandomTrainImageByNumber(5);
    mnistapi_printImageWithOneAndZero(image);
    free(image);
    image = mnistapi_getRandomTrainImage();
    mnistapi_printImageWithOneAndZero(image);
    free(image);
    mnistapi_closeTraining();

    mnistapi_initTesting();
    image = mnistapi_getRandomTestImageByNumber(5);
    mnistapi_printImageWithOneAndZero(image);
    free(image);
    image = mnistapi_getRandomTestImage();
    mnistapi_printImageWithOneAndZero(image);
    free(image);
    mnistapi_closeTesting();

	return 0;
}
