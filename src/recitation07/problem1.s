.globl __problem1
.type  __problem1, @function

__problem1:
    # extern int __problem1(int n);
    # INPUT:
    #   The parameter `n` is contained in `%edi`.
    # OUTPUT:
    #   The return value is contained in `%eax`.

    movl $1, %edx
    movl $0, %eax
    jmp  .L2
.L3:
    addl %edx, %eax
    addl $1,   %edx
.L2:
    cmpl %edi, %edx
    jle  .L3
    ret
