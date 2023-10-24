# Project 3
## Makefile

The `Makefile` provided with this project compiles and builds all of the required programs.

To compile and build all of the programs run:

    make all

To compile and build individual problems run:

    make problem1
    make problem2

To run simple tests  on each program you can execute

    make run_problem1
    make run_problem2

To remove all previously compiled and built files, run

    make clean

(It is a good idea to run `make clean` before you commit and push the files to the remote repository so that you are
  not copying binaries from one platform to the other.)

## Programming requirements

- The programs should be leak-free: any memory that is allocated should be freed before the program terminates.
- The programs have to be documented! Any file that you edit should have preamble
 including your name as the author, description of the purpose of the program and
 inline comments in the functions that you implement. All functions except for `main()` should
 have descriptions of function parameters, returned value and a summary of what the function does.
- The code has to build correctly using the provided `Makefile`.
- The code has to follow C programming conventions.
- The code has to be formatted properly.  


## Problem 1


You are given two object files `problem1.o` and `foo_given.o` as well as an executable binary
file called `problem1_given`. The first one
contains the `main` function, the second contains a function called `foo` and the third
one is the program build from the two object files. Your task is to write C code for
the function `foo` in `foo_given.o`. Your code may not end up being identical to
the one in the given file, but it should be equivalent (i.e., given the same
inputs, it should produce the same output).

In order to build the object file, run:

```
make foo.o
```

In order to build and run the program:

```
make problem1
make run_problem1
```

__Deliverables:__
Implementation of the function `foo` in file `foo.c`.





## Problem 2

You are given two object files `problem2.o` and `bar_given.o` as well as an executable binary
file called `problem2_given`. The first one
contains the `main` function, the second contains a function called `bar` and the third
one is the program build from the two object files. Your task is to write C code for
the function `bar` in `bar_given.o`. Your code may not end up being identical to
the one in the given file, but it should be equivalent (i.e., given the same
inputs, it should produce the same output).

In order to build the object file, run:

```
make bar.o
```

In order to build and run the program:

```
make problem2
make run_problem2
```

The output from the program will give you an idea if your function `bar` performs
the task equivalent to the given version.

__Deliverables:__
Implementation of the function `bar` in file `bar.c`.
