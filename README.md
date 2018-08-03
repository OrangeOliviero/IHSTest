This project was created using:
 - GNU Make 4.2.1
 - Cygwin gcc 7.3.0
 - Cygwin64 2.10.0 (sorry)
 - Windows 10
All attempts have been made to ensure portability across platforms where GCC and Make are available,
 however this has only been tested on the above named machine.

Each of the three problems are contained within a directory named with the problem number (e.g. Problem1)
If relevant, a Makefile will exist with at least the following targets:
 - all (default)
   - Builds the project. Does not run tests.
 - test
   - Runs the tests. May build the project if it's out of date.
 - clean
   - Cleans the build
In addition, a top-level Makefile with the same targets exists and will recursively make each Problem
 with the given target.

Problem-specific notes:
 - Problem 1:
   - The code being "reviewed" has been copied into a file named Critique.cpp
   - Critiques are made in the form of comments, prefixed with C[X], where X is a positive integer (e.g. C1)
 - Problem 2:
   - Since this is a utility "library", an example user is also produced and used in tests.
     This example user uses a vector of integer types for the array, but the library is not
      limited to integer types.
   - The solution uses templates to provide a generic implementation that will work for any
      array or containers that implement iterators in the standard way.
   - Operations are easily added, however they must take the following form:
     - Only the current value is to be modified by the operation
     - The operation can only use the current value, previous value, and previous result.
 - Problem 3:
