.globl __problem1
.type  __problem1, @function

__problem1:
    # extern int __problem1(long *a, long *b, long *c);
    # INPUT:
    #   The parameter `a` is contained in `%rdi`.
    #   The parameter `b` is contained in `%rsi`.
    #   The parameter `c` is contained in `%rdx`.
    # OUTPUT:
    #   The return value is contained in `%rax`.

    movq  (%rdi),          %rax
    movq  (%rsi),          %rdx
    leaq  (%rdx, %rdx, 2), %rcx
    imulq  %rax, %rcx
    jmp   .L2
.L3:
    leaq (%rax, %rax), %rdx
    leaq (%rdx, %rax), %rcx
    movq  %rdx, %rax
.L2:
    cmpq %rcx, %rax
    jg   .L3

    rep ret
