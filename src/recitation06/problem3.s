.globl __problem3
.type  __problem3, @function

__problem3:
    # extern int __problem3(int *x, int *y);
    # INPUT:
    #   The parameter `x` is contained in `%rdi`.
    #   The parameter `y` is contained in `%rsi`.
    # OUTPUT:
    #   The return value is contained in `%eax`.

    movl (%rsi),           %eax
    sall $4,               %eax
    movl (%rdi),           %edx
    leal (%rdx, %rdx, 4),  %edx
    movl  %edx,           (%rdi)
    addl $3,               %edx
    movl  %edx,           (%rsi)
    ret
