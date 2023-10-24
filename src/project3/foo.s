# Author: Ishan Pranav
# Copyright (c) 2023 Ishan Pranav. All rights reserved.
# Licensed under the MIT License.

.globl __foo
.type  __foo, @function

__foo:
    # extern void __foo(long a, long b);
    # INPUT:
    #   The parameter `a` is contained in `%rdi`.
    #   The parameter `b` is contained in `%rsi`.
    # OUTPUT:
    #   The return value is contained in `%rax`.

    lea (%rdi, %rdi, 2), %rax
    lea (%rdi, %rax, 4), %rax

    shl $2, %rax

    lea (%rsi, %rsi, 2), %rcx

    mov %rcx, %rdx
    shl $5,   %rdx
    sub %rcx, %rdx
    add %rdx, %rax
    sub %rdi, %rsi

    lea (%rsi, %rsi, 2), %rdx
    
    shl $5,   %rdx
    sub %rsi, %rdx
    add %rdx, %rax
    retq
