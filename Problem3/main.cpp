#include <iostream>
#include <string>

#include "PalindromeFinder.h"

using namespace std;

void printUsage();

int main(int argc, const char* argv[])
{
  if (argc != 2) {
    printUsage();
    return 2;
  }

  string input = argv[1];
  cout << "Finding palindromes in \"" << input << "\"" << endl;

  PalindromeCache checkedCache;
  PalindromeCache foundPalindromes;
  bool palindromesFound = findPalindromes(input, 0, input.size() - 1, checkedCache, foundPalindromes);

  if (!palindromesFound) {
    cout << "No palindromes found!" << endl;
  } else {
    for (const auto& palindrome : foundPalindromes) {
      const auto& key = palindrome.first;
      printPalindrome(input, key.first, key.second);
    }
  }
}

void printUsage() {
  cout << "Usage: PalindromeFinder <string>" << endl;
}
