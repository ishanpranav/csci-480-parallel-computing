// Author: Mark Ebersole � NVIDIA Corporation
// Source: https://developer.nvidia.com/cuda-education
// Modified and adapted by Ishan Pranav

#include <stdio.h>

using namespace std;

__device__ const char *MESSAGE = "HELLO WORLD!";

const char MESSAGE_LENGTH = 12;

__global__ void hello()
{
    printf("%c\n", MESSAGE[threadIdx.x % MESSAGE_LENGTH]);
}

int main()
{
    int threads = MESSAGE_LENGTH;
    int blocks = 1;

    hello<<<blocks, threads>>>();
    cudaDeviceSynchronize();

    return 0;
}
