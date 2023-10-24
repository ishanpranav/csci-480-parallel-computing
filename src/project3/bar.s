# Author: Ishan Pranav
# Copyright (c) 2023 Ishan Pranav. All rights reserved.
# Licensed under the MIT License.

.globl __bar
.type  __bar, @function

__bar:
    # extern void __bar(long a, long b);
    # INPUT:
    #   The parameter `a` is contained in `%rdi`.
    #   The parameter `b` is contained in `%rsi`.
    # OUTPUT:
    #   The return value is contained in `%rax`.

    mov %rdi, %rdx
    mov $0,   %eax
    
    lea (%rdi, %rdi, 4), %rcx
    lea (%rdi, %rcx, 2), %rcx

    mov %rsi, %rdi
    shl $4,   %rdi
    
    lea (%rcx, %rsi, 2), %rcx
    
    sub %rdi, %rcx
    add $1,   %rcx
    jmp .L2b
.L24:
    add $1,   %rdx
    add %rcx, %rax
.L2b:
    cmp %rsi, %rdx
    jle .L24
