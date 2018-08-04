#ifndef __PALINDROMEFINDER_H__
#define __PALINDROMEFINDER_H__

#include <string>
#include <map>
#include <utility>

class PalindromeKeyComparator;

using PalindromeCacheKey = std::pair<size_t, size_t>;
using PalindromeCache = std::map<PalindromeCacheKey, bool, PalindromeKeyComparator>;

class PalindromeKeyComparator {
public:
  bool operator()(const PalindromeCacheKey& left, const PalindromeCacheKey& right);
};

bool findPalindromes(const std::string& input, size_t start, size_t end,
                     PalindromeCache& checkedCache, PalindromeCache& foundPalindromes);

bool isPalindrome(const std::string& input, size_t start, size_t end);

void printPalindrome(const std::string& palindrome, size_t start, size_t end);

#endif /* __PALINDROMEFINDER_H__ */
