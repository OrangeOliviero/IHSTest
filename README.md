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
   - Sub-palindromes of palindromes aren't reported (e.g. ABBA will not report BB as well).
     - This is because the example output did not include these, and they are somewhat redundant
       as trimming the outer characters of a palindrome equally necessarily results in another
       palindrome (excepting when only one character remains).
   - Palindrome output is sorted in the following manner:
     - Larger palindromes are reported first
     - Palindromes of the same size are reported in order of where they occur in the string
       (left to right).
     - Efficiency was obtained at the expense of memory - a cache of processed portions is
       retained so that the same substring isn't re-processed repeatedly.

General notes:
 - The problem examples have all been incorporated into tests. Additional tests were added.
 - Both Problem2 and Problem3's binaries will print their expected usage if mis-usage is detected.
 - Problem2 uses the 'stoi' utility for parsing input values, which succeeds so long as the first
    portion of the string can be interpreted as an integer (e.g. 6.5, 6.s, 6 all get interpreted as 6).
   This is an artifact of how the example is implemented, not a limitation of the library function.
 - The build system puts generated object/dependency files in the same directory as the source, and
    the output in a sub-directory of the source. This is generally non-ideal for a larger-scale
    project, but acceptable for small-scale ones such as these.
 - The test system leaves test output in the same directory as the tests if they fail. This is both
    good and bad - it allows for easier debugging/comparisons, but also pollutes the directory
    structure if they aren't cleaned up. A more robust test system would do a better job of both.
