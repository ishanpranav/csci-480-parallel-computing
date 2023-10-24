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
    movq     %rax,           %rcx
    imulq   (%rsi),          %rcx
    leaq  3 (%rcx),          %rdx
    cmpq     %rax,           %rdx
    jg      .L5
    leaq    (%rcx, %rcx, 2), %rdx

    cmpq $6, %rdx
    jg   .L6
    movl $3, %eax
    jmp  .L3
.L5:
    leaq -12 (%rax, %rax, 2), %rcx
.L3:
    movq  %rcx, (%rdi)
    movq  %rax, (%rsi)
    movl  $5,    %edx
    subq  %rcx,  %rdx
    imull %edx,  %eax
    ret
.L6:
    movl $2, %ecx
    jmp  .L3
