.globl __problem1
.type  __problem1, @function

__problem1:
    # extern int __problem1(int *x, int *y);
    # INPUT:
    #   The parameter `x` is contained in `%rdi`.
    #   The parameter `y` is contained in `%rsi`.
    # OUTPUT:
    #   The return value is contained in `%eax`.

    movl    (%rdi),  %edx
    leal  2 (%rdx),  %eax
    imull    %eax,   %edx
    movl     %edx,  (%rsi)
    ret
