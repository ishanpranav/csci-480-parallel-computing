.globl __problem1
.type  __problem1, @function

__problem1:
    # extern int __problem1(long *xp, long *yp, long *zp);
    # INPUT:
    #   The parameter `xp` is contained in `%rdi`.
    #   The parameter `yp` is contained in `%rsi`.
    #   The parameter `zp` is contained in `%rdx`.
    # OUTPUT:
    #   The return value is contained in `%rax`.

    movq  (%rdi), %rax
    addq   %rax,  %rax
    movq   %rax,  %rdx
    imulq (%rsi), %rdx
    jmp   .L2
.L3:
    leaq  -4 (%rdx),          %rcx
    imulq     %rcx,           %rdx
    leaq     (%rax, %rax, 2), %rcx

    salq $3,   %rcx
    subq %rax, %rcx
    movq %rcx, %rax
.L2:
    cmpq  %rax,  %rdx
    jg    .L3
    movq  %rdx, (%rdi)
    movq  %rax, (%rsi)
    movl  $5,    %ecx
    subq  %rdx,  %rcx
    imull %ecx,  %eax
    ret
