.globl __problem3Part1
.globl __problem3Part2
.type  __problem3Part1, @function
.type  __problem3Part2, @function

__problem3Part1:
    # extern int __problem3Part1(int n);
    # INPUT:
    #   The parameter `n` is contained in `%edi`.
    # OUTPUT:
    #   The return value is contained in `%eax`.

    movl $0, %eax
    movl $0, %edx
    jmp  .L2
.L3:
    addl %edx, %eax
    addl $2,   %edx
.L2:
    cmpl %edi, %edx
    jle  .L3
    ret

__problem3Part2:
    # extern int __problem3Part2(int n);
    # INPUT:
    #   The parameter `n` is contained in `%edi`.
    # OUTPUT:
    #   The return value is contained in `%eax`.

    movl $0, %eax
    movl $1, %edx
    jmp  .L5
.L6:
    addl %edx, %eax
    addl $2,   %edx
.L5:
    cmpl %edi, %edx
    jle  .L6
    ret
