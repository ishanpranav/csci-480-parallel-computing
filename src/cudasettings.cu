#include <stdlib.h>
#include <stdio.h>

int main()
{
    cudaError_t error;
    cudaDeviceProp device;
    int deviceCount = 0;

    error = cudaGetDeviceCount(&deviceCount);

    if (error != cudaSuccess)
    {
        printf("Error: %s\n", cudaGetErrorString(error));
        
        return -1;
    }

    printf("Number of devices: %d\n", deviceCount);

    for (int i = 0; i < deviceCount; i++)
    {
        error = cudaGetDeviceProperties(&device, i);

        if (error != cudaSuccess)
        {
            printf("Error: %s\n", cudaGetErrorString(error));
            
            return -1;
        }
        
        printf("\nDevice %d:\n", i);
        printf("name: %s\n", device.name);
        printf("Compute capability %d.%d\n", device.major, device.minor);
        printf("total global memory(KB): %ld\n", device.totalGlobalMem / 1024);
        printf("shared mem per block: %d\n", device.sharedMemPerBlock);
        printf("regs per block: %d\n", device.regsPerBlock);
        printf("warp size: %d\n", device.warpSize);
        printf("max threads per block: %d\n", device.maxThreadsPerBlock);
        printf("max thread dim x:%d y:%d z:%d\n", device.maxThreadsDim[0], device.maxThreadsDim[1], device.maxThreadsDim[2]);
        printf("max grid size x:%d y:%d z:%d\n", device.maxGridSize[0], device.maxGridSize[1], device.maxGridSize[2]);
        printf("clock rate(KHz): %d\n", device.clockRate);
        printf("total constant memory (bytes): %ld\n", device.totalConstMem);
        printf("multiprocessor count %d\n", device.multiProcessorCount);
        printf("integrated: %d\n", device.integrated);
        printf("async engine count: %d\n", device.asyncEngineCount);
        printf("memory bus width: %d\n", device.memoryBusWidth);
        printf("memory clock rate (KHz): %d\n", device.memoryClockRate);
        printf("L2 cache size (bytes): %d\n", device.l2CacheSize);
        printf("max threads per SM: %d\n", device.maxThreadsPerMultiProcessor);
    }

    return 1;
}
