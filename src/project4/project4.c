// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 32
#define DELIMITERS ", \t\n"

/**
 * Represents text as a sequence of characters.
 */
typedef char *String;

/**
 * Represents an 8-bit unsigned integer.
 */
typedef unsigned char Byte;

/**
 * Represents an entry in the translation lookaside buffer (TLB).
 */
typedef struct TlbEntry
{
    /**
     * Specifies the tag of the entry.
     */
    int tag;

    /**
     * Specifies the physical page number (PPN) of the entry.
     */
    int physicalPageNumber;
} TlbEntry;

/**
 * Represents an entry in the physical set-associative cache memory.
 */
typedef struct CacheLine
{
    /**
     * Specifies the tag of the entry.
     */
    int tag;

    /**
     * Specifies the physical bytes of cached memory.
     */
    Byte bytes[4];
} CacheLine;

/**
 * Specifies the input text buffer.
 */
char buffer[BUFFER_SIZE];

/**
 * Specifies an array representing the virtual page table.
 */
int pages[16];

/**
 * Specifies an array representing the physical cache memory.
 */
CacheLine cacheLines[16];

/**
 * Specifies a two-dimensional array representing the translation lookaside
 * buffer (TLB).
 */
TlbEntry tlbSets[4][4];

/**
 * Retrieves the next token from the buffered tokenizer, converted to an
 * integer from its hexadecimal string representation.
 *
 * @return The integral representation of the next buffered token.
 */
static int nextInt()
{
    String token = strtok(NULL, DELIMITERS);

    return strtol(token, NULL, 16);
}

/**
 * Reads and parses the next line from the buffered tokenizer.
 */
static void read()
{
    String token = strtok(buffer, DELIMITERS);

    if (!strcmp(token, "TLB"))
    {
        int index = nextInt();
        int tag = nextInt();
        int physicalPageNumber = nextInt();

        // Brief linear search to find an empty position in the TLB set

        for (int i = 0; i < 4; i++)
        {
            if (tlbSets[index][i].physicalPageNumber == 0)
            {
                tlbSets[index][i].tag = tag;
                tlbSets[index][i].physicalPageNumber = physicalPageNumber;

                break;
            }
        }
    }
    else if (!strcmp(token, "Page"))
    {
        // Index into the page table directly

        int virtualPageNumber = nextInt();
        int physicalPageNumber = nextInt();

        pages[virtualPageNumber] = physicalPageNumber;
    }
    else if (!strcmp(token, "Cache"))
    {
        // Index into the cache directory

        int index = nextInt();

        cacheLines[index].tag = nextInt();

        for (int i = 0; i < 4; i++)
        {
            cacheLines[index].bytes[i] = nextInt();
        }
    }
}

/**
 * The main entry point for the application.
 *
 * @param count the number of command-line arguments
 * @param args the command-line arguments. By convention, the first argument is
 *             the program name.
 * @return An exit code. This value is always 0.
 */
int main(int count, String args[])
{
    if (count < 1)
    {
        printf("Usage: project4 <input_path>\n");

        return 1;
    }

    String fileName = args[1];
    FILE *streamReader = fopen(fileName, "r");
    int virtualAddress = 0;

    while (fgets(buffer, BUFFER_SIZE, streamReader))
    {
        read();
    }

    fclose(streamReader);

    for (int round = 1; round <= 3; round++)
    {
        printf("Enter Virtual Address: ");

        if (!scanf("%X", &virtualAddress))
        {
            break;
        }

        int virtualPageNumber = virtualAddress >> 6;
        int tlbTag = (virtualAddress >> 8) & 0x3f;
        int tlbIndex = virtualPageNumber & 0x3;
        int cacheIndex = (virtualAddress >> 2) & 0xf;
        int cacheOffset = virtualAddress & 0x3;
        int physicalPageNumber = -1;

        // Brief linear search to find a matching tag in the TLB set

        for (int i = 0; i < 4; i++)
        {
            if (tlbSets[tlbIndex][i].tag == tlbTag)
            {
                physicalPageNumber = tlbSets[tlbIndex][i].physicalPageNumber;

                break;
            }
        }

        if (physicalPageNumber == -1)
        {
            // No matching tag discovered in the TLB
            // Index into the virtual page table instead

            physicalPageNumber = pages[virtualPageNumber];
        }

        if (cacheLines[cacheIndex].tag != physicalPageNumber)
        {
            // Incorrect tag discovered in the cache

            printf("Can not be determined\n");

            continue;
        }

        // No issues encountered

        printf("%X\n", cacheLines[cacheIndex].bytes[cacheOffset]);
    }

    return 0;
}
