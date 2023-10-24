.globl __problem2
.type  __problem2, @function

__problem2:
    # extern int __problem2(long *xp, long *yp, long *zp);
    # INPUT:
    #   The parameter `xp` is contained in `%rdi`.
    #   The parameter `yp` is contained in `%rsi`.
    #   The parameter `zp` is contained in `%rdx`.
    # OUTPUT:
    #   The return value is contained in `%rax`.

    movq    (%rdi),          %rax
    addq     %rax,           %rax
    movq     %rax,           %rdx
    imulq   (%rsi),          %rdx
    leaq  3 (%rdx),          %rcx
    cmpq     %rax,           %rcx
    jl      .L2
    leaq    (%rdx, %rdx, 4), %rcx
    cmpq    $6, %rcx
    jle     .L4
    movl    $4,              %edx
    jmp     .L3
.L2:
    leaq -4 (%rax),          %rdx
    leaq    (%rdx, %rdx, 2), %rcx
    leaq    (%rdx, %rcx, 4), %rdx
    jmp     .L3
.L4:
    movl $9, %eax
.L3:
    movq  %rdx, (%rdi)
    movq  %rax, (%rsi)
    movl  $5,    %ecx
    subq  %rdx,  %rcx
    imull %ecx,  %eax
    ret
