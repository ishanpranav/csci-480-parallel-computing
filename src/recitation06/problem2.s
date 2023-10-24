.globl __problem2
.type  __problem2, @function

__problem2:
    # extern int __problem2(int *x, int *y);
    # INPUT:
    #   The parameter `x` is contained in `%rdi`.
    #   The parameter `y` is contained in `%rsi`.
    # OUTPUT:
    #   The return value is contained in `%eax`.

    movl    (%rsi),           %eax
    leal    (%rax, %rax, 2),  %eax
    leal -4 (%rax),           %edx
    movl     %edx,           (%rdi)
    addl    $3,               %edx
    movl     %edx,           (%rsi)
    ret
