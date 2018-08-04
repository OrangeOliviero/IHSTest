#include "PalindromeFinder.h"

#include <iostream>

using namespace std;

static void addFoundPalindrome(size_t start, size_t end, PalindromeCache& foundPalindromes);

bool findPalindromes(const string& input, size_t start, size_t end,
                     PalindromeCache& checkedCache, PalindromeCache& foundPalindromes)
{
  if (end <= start) return false;

  // Check to see if we've already checked this palindrome
  PalindromeCacheKey key(start, end);
  if (checkedCache[key]) return false;
  checkedCache[key] = true;

  if (isPalindrome(input, start, end)) {
    addFoundPalindrome(start, end, foundPalindromes);
    return true;
  }

  bool rv = findPalindromes(input, start + 1, end, checkedCache, foundPalindromes);
  rv = findPalindromes(input, start, end - 1, checkedCache, foundPalindromes) || rv;

  return rv;
}

bool isPalindrome(const string& input, size_t start, size_t end)
{
  // Single characters are not palindromes
  if (start >= end) return false;

  while (start < end) {
    if (input[start] != input[end]) return false;
    ++start;
    --end;
  }
  return true;
}

void printPalindrome(const string& palindrome, size_t start, size_t end)
{
  size_t len = end - start + 1;
  cout << palindrome.substr(start, len) << "," << start << "," << len << endl;
}

void addFoundPalindrome(size_t start, size_t end, PalindromeCache& foundPalindromes)
{
  // Remove any previously found palindromes that are sub-palindromes of this one
  PalindromeCacheKey keyToAdd(start, end);
  foundPalindromes[keyToAdd] = true;

  while (start < end) {
    ++start;
    --end;
    PalindromeCacheKey key(start, end);
    foundPalindromes.erase(key);
  }
}

bool PalindromeKeyComparator::operator()(const PalindromeCacheKey& left,
                                         const PalindromeCacheKey& right)
{
  // Technically the length is these + 1, but since we're only comparing the two,
  //  it cancels out anyways
  size_t leftLen = left.second - left.first;
  size_t rightLen = right.second - right.first;
  if (leftLen > rightLen) return true;
  if (rightLen > leftLen) return false;

  // Lengths are equal, order by position
  if (left.first < right.first) return true;
  return false;
}
