#include <stdio.h>

/**
 * Computes the floor of the integer binary logarithm of the given number.
 * 
 * @param n the number
 * @return The base-2 logarithm, rounded down to the nearest integer.
 */
static int floorLog2(unsigned int n)
{
    return 31 - __builtin_clz(n);
}

/**
 * The main entry point for the application.
 *
 * @return An exit code.
 */
int main()
{
    int cacheSize;
    int addressLength;
    int blockSize;
    int associativity;

    printf("Cache size\t(kB):\t");
    scanf("%d", &cacheSize);
    printf("Address length\t(bits):\t");
    scanf("%d", &addressLength);
    printf("Block size\t(B):\t");
    scanf("%d", &blockSize);
    printf("Associativity\t(-way):\t");
    scanf("%d", &associativity);

    int index = floorLog2((cacheSize * 1024 / blockSize) / associativity);
    int offset = floorLog2(blockSize);
    int tag = addressLength - (offset + index);

    printf("\nTag:\t%d\tbits\nIndex:\t%d\tbits\nOffset:\t%d\tbits\n", tag, index, offset);

    return 0;
}
