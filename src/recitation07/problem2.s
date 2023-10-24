.globl __problem2
.type  __problem2, @function

__problem2:
    # extern long __problem2(int n);
    # INPUT:
    #   The parameter `n` is contained in `%edi`.
    # OUTPUT:
    #   The return value is contained in `%eax`.

    cmpl $1, %edi
    jbe  .L5
    movl $1, %edx
    movl $1, %eax
    jmp  .L3
.L4:
    movslq %edx, %rcx
    imulq  %rcx, %rax
    addl   $1,   %edx
.L3:
    cmpl %edi, %edx
    jle  .L4
    ret
.L5:
    movl $1, %eax
    ret
