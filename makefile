all: compile

compile:
	gcc main.c MNIST_API.h MNIST_API_impl.c -o main