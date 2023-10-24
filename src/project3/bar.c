// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

#include "bar.h"

long bar(long a, long b)
{
    long rdx = a;           // mov %rdi, %rdx
    long result = 0;        // mov $0,   %eax
    long rcx = 11 * a;      // lea (%rdi, %rdi, 4), %rcx 
                            // lea (%rdi, %rcx, 2), %rcx

    a = b * 16;             // mov %rsi, %rdi
                            // shl $4,   %rdi
    rcx += (b * 2) - a + 1; // lea (%rcx, %rsi, 2), %rcx
                            // sub %rdi, %rcx
                            // add $1,   %rcx

    while (rdx <= b)        // cmp %rsi, %rdx
    {
        rdx++;              // add $1,   %rdx
        result += rcx;      // add %rcx, %rax
    }

    return result;          // repz ret
}
