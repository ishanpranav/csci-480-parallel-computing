# Project 1
## Makefile

The `Makefile` provided with this project compiles and builds all of the required programs.
To compile and build all of the programs run:

    make all

To compile and build individual problems run:

    make problem1
    make problem2
    ...

To run simple tests on each program you can execute

    ./problem1 < test1.txt
    ./problem2 < test2.txt
    ...
(You should test your code much more extensively than these simple test cases provided with the assignment do.)

To remove all previously compiled and built files, run

    make clean

## Programming requirements

- The programs should be leak-free: any memory that is allocated should be freed before the program terminates. (Although in this project, there should not be a need to allocate any memory. )
- The programs have to be documented! Any file that you edit should have preamble including your name as the author, description of the purpose of the program and inline comments in the functions that you implement. All functions except for `main()` should have descriptions of function parameters, returned value and a summary of what the function does.__
- The code has to build correctly using the provided `Makefile`.
- The code has to follow C programming conventions.
- The code has to be formatted properly.  

## Problem 1

The program in  `problem1.c` is a date compression program. Your task is to implement
the `main` function as well as any other functions you may wish to use to accomplish
the task outlined below.

Your program should be able to convert date/time specification from multi-integer
human readable format to a single integers (this way we can use one 8-byte integer
instead of five 8-byte integers). Given a date/time in the following format

```
MM/DD hh:mm:ss
```

The program uses different bits in a 32-bit sequence to represent each digit above.
The number of bits for each digit is determined by the number of possible values
that digit can take in a valid date/time specification:
- bits 0-3 used to represent the ones digit in seconds s**s** (valid values are 0-9)
- bits 4-6 used to represent the tens digit in seconds **s**s (valid values are 0-5)
- bits 7-10 used to represent the ones digit in minutes m**m** (valid values are 0-9)
- bits 11-13 used to represent the tens digit in minutes **m**m (valid values are 0-5)
- bits 14-17 used to represent the ones digit in hour h**h** (valid values are 0-9)
- bits 18-19 used to represent the tens digit in hour **h**h (valid values are 0-2)
- bits 20-23 used to represent the ones digit in day D**D** (valid values are 0-9)
- bits 24-25 used to represent the tens digit in day **D**D (valid values are 0-3)
- bits 26-29 used to represent the ones digit in month M**M** (valid values are 0-9)
- bit 30 used to represent the tens digit in month **M**M (valid values are 0-1)
- bit 31 is not used and should always be zero

Keep in mind that the bit numbering in an integer is from right to left (the right
bit is the least significant one, the left bit is the most significant one).

__Input__

The input for your program will be specified as follows:
- the first line will contain a non-negative integer N indicating how many dates will
follow
- the next N lines will contain the dates in the format specified as above (note,
  format is ALWAYS going to be as above, but the values may not be always correct).

__Output__

The program should print N lines to the standard output. For each valid date/time
the program should print its corresponding integer. For each invalid
date/time the program should print INVALID.

__Example__

Input:
```
4
11/25 12:53:32
11/25 12:53:02
07/01 03:12:00
13/25 12:53:02
```
Output:
```
1179953586
1179953538
470862080
INVALID
```

__Deliverables__

Implementation of the program in `problem1.c` file.

## Problem 2

RGB color models uses three color channels: red, green and blue to represent
a large number of colors that can be obtained from combining the three.  

In many applications the three separate values are combined and represented
as a single hexadecimal number.
The objective of your program is to read the three values representing the three
separate colors and produce a single hexadecimal value.

Each color is represented by a value in a range of [0,255]. Each of those numbers
is represented by exactly two hexadecimal symbols: RRGGBB.

__Input__

The input for your program will be specified as follows:
- the first line will contain a non-negative integer N indicating how many colors will
follow
- the next N lines will contain the colors specified as three comma-separated integers (note,
  format of each line is always going to be correct, but the values may not be always valid).

__Output__

The program should print N lines to the standard output. For each valid color
the program should print its corresponding hexadecimal value proceeded by a # symbol.
For each invalid color the program should print INVALID.

__Example__

Input:
```
5
255, 0, 0
100, 150, 200
0, 200, 0
300, 0, -1
130, 0, 155
```
Output:
```
#ff0000
#6496c8
#00c800
INVALID
#82009b
```

__Deliverables__
Implementation of the program in `problem2.c` file.

## Problem 3

We define the operation of splitting a binary number `n` into two numbers
`an`, `bn` as follows. Let `0 ≤ i1 < i2 < ... < ik` be the indices of the bits (with
the least significant bit having index 0) in `n` that are 1. Then the indices of the bits
of `an` that are 1 are `i1` , `i3` , `i5` , ... and the indices of the bits of `bn`
that are 1 are `i2` , `i4` , `i6` ,  ...

For example, if `n` is `110110101` in binary then, again in binary, we have `a =
010010001` and `b = 100100100`.

__Input__

The program has to read multiple values of `n` and, for each, produce two values
`an` and `bn` as described above.

Each test case consists of a single integer
`n` between 1 and 2^(31) - 1 (i.e. any positive integer within the range of the int type)
written in standard decimal (base 10) format on a single line.
Input is terminated by a line containing ‘0’ which should not be processed.

__Output__

The output for each test case consists of a single line, containing the integers
`an` and `bn` separated by a single space. Both `an` and `bn` should be written in decimal format
(base 10).

__Example__

Input:
```
6
7
13
0
```
Output:
```
2 4
5 2
9 4
```

__Restrictions__

Your program is not allowed to use ANY of the functions defined in the `math.h` header file.
Specifically, it is not allowed to use the `pow()` functions to compute values of powers of 2.
