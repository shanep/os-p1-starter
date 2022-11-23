# Project 1

This assignment is intended to serve as a warm up assignment. It may have been a
long time since you have written any code in C/C++, so we will get warmed up by
writing a circular doubly linked list. This will allow you get up to speed using
C and refresh your knowledge of pointers, struct's, and manual memory
management. This assignment can also be leveraged in future assignments that may
need to store a bunch of data and need a data structure that is more flexible
than a standard C array! We will write our code in C but use a C++ compiler so
we can take advantage of the gtest framework and more strict compile time checks
to help make your code more robust. You can only use C++ in the unit testing
harness everything else must be in C.

### Warmup Purpose

- Refresh you knowledge of struct's
- Refresh you knowledge pointers (function and data)
- Refresh you knowledge of memory allocation in C (malloc/free)
- Implement a simple data structure
- Make sure you have all your tools installed and they are usable

## Tools

This project requires the following tools, all of which are installed on the
cs lab machines for you to use. If you are working on a Mac you can install all
these tools using [homebrew](https://brew.sh/). If you are on windows you need
to use [WSL](https://learn.microsoft.com/en-us/windows/wsl/about). Support is
only provided for developing on the CS lab machines, if you can't get your
personal machine configured you will need to use the machines in the lab.

CMake should detect your compiler and then enable or disable features base on
what is installed. For example this project will compile with `gcc` but not
be able to take advantage of the address sanitizers that clang has.

- [cmake](https://cmake.org/)
- [clang](https://clang.llvm.org/)
- [google test](http://google.github.io/googletest/)

## Linked Lists

It is sometimes helpful to draw out what your data structure will look like in
memory before you start coding anything up. Having a visual model to reference
can aid in both development and testing. The diagram below shows a list with 3
elements and a sentinel node. You can see that the next pointer in node **n3**
points back to the sentinel node and the prev pointer of  **n1**  points back to
the sentinel node. Each node has a data pointer that will hold a reference to
the data that is being stored in the list. Using a sentinel node allows us to
write slightly simpler algorithms when manipulating the list.

![Linked list visualization]({{site.url}}{% link /assets/images/os/list-sentinel.png %})

## Thinking in C

Java is an Object Oriented (OO) programming language and uses methods while C is
a procedural language and uses functions. The purpose of both is to break large
computing tasks into smaller ones. While pre-ANSI C (known as K&R C) had very
strange function declarations, functions in ANSI C (C89 and greater) have a
similar look and feel to Java.

One of the biggest differences between functions in C and methods in Java is
Java groups your functions and data together into a class. So in java if you
want to create a new linked list and then add something to it you would create a
new list and then call the **add** method on that list:

```java
Mylist list = new Mylist();
list.add(new Object());
```

In C the code above would be written as follows:

```c
struct object *obj = create_object();
struct mylist *list = create_list();
list_add(list, obj);
```

So as you can see with the examples above any code that is written in Java using
objects can be translated to C!

## Task 1 - Build

There are two scripts in the root directory `debug.sh` and `release.sh`. One
creates a debug build with address sanitizers compiled in and one is a release
build with no debug symbols or sanitizers. A good approach in this class is to
use the `release.sh` build unless you need to do any debugging or want to run
the memory sanitizers.

Run the `release.sh` script from the terminal to get setup your project. Note
that your output will be slightly different than what is shown below because
cmake configures the build system specific to the system that it is running on.

```bash
[shanepanter@onyx os-starter]$ ./setup.sh 
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY - Success
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY - Success
-- Performing Test COMPILER_HAS_DEPRECATED_ATTR
-- Performing Test COMPILER_HAS_DEPRECATED_ATTR - Success
-- The C compiler identification is GNU 8.5.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Found Python: /usr/bin/python3.8
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE  
-- Configuring done
-- Generating done
-- Build files have been written to:
```

After you have run `release.sh` you can `cd` into the build directory and compile
the program and then run the example tests.

```bash
[shanepanter@onyx os-starter]$ cd build/
[shanepanter@onyx build]$ make
Scanning dependencies of target lab
[  7%] Building CXX object src/CMakeFiles/lab.dir/lab.cpp.o
[ 14%] Linking CXX shared library ../liblab.so
[ 14%] Built target lab
Scanning dependencies of target myprogram
[ 21%] Building CXX object src/CMakeFiles/myprogram.dir/main.cpp.o
[ 28%] Linking CXX executable ../myprogram
[ 28%] Built target myprogram
Scanning dependencies of target gtest
[ 35%] Building CXX object _deps/gtest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[ 42%] Linking CXX static library ../../../lib/libgtest.a
[ 42%] Built target gtest
Scanning dependencies of target gtest_main
[ 50%] Building CXX object _deps/gtest-build/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 57%] Linking CXX static library ../../../lib/libgtest_main.a
[ 57%] Built target gtest_main
Scanning dependencies of target test-lab
[ 64%] Building CXX object tests/CMakeFiles/test-lab.dir/test-lab.cpp.o
[ 71%] Linking CXX executable ../test-lab
[ 71%] Built target test-lab
Scanning dependencies of target gmock
[ 78%] Building CXX object _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 85%] Linking CXX static library ../../../lib/libgmock.a
[ 85%] Built target gmock
Scanning dependencies of target gmock_main
[ 92%] Building CXX object _deps/gtest-build/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library ../../../lib/libgmock_main.a
[100%] Built target gmock_main
[shanepanter@onyx build]$ make test
Running tests...
Test project /home/ShanePanter/starter-code-test/os-starter/build
    Start 1: AddTest.Positive
1/1 Test #1: AddTest.Positive .................   Passed    0.11 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.38 sec
[shanepanter@onyx build]$ ./myprogram 
Function go called by main version: 0.1

```

## Task 2 - Implement the header file

In the starter code you will fine a file named `lab.h` that is well documented.
You need to implement all the functions defined in that file in `lab.cpp`.

## Task 3 - Write Unit tests

In the tests directory is a file named `test-lab.cpp`. There are a few example
tests to get you started, you will need to complete that file to ensure that
your solution is correct.

## Task 4 - Complete Retrospective

Update the Retrospective.md in the root directory of your starter code and
complete all the TODO items.

## Acceptance Criteria

- You have installed all the dev tools and can build and test the project
- You have implemented all the functions defined in lab.h
- You have written enough tests in `test-lab.cpp` to ensure your solution is correct
- You have completed all the TODO's in the README.md
- You have verified all criteria on the [grading rubric]({% link _os/grading-rubric.md %})
