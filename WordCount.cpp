#include "WordCount.h"
#include <cctype>  // for std::isalpha, std::tolower
using namespace std;

// Default constructor - ensure table is empty
WordCount::WordCount() {
  for (size_t i = 0; i < CAPACITY; ++i) {
    table[i].clear();
  }
}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
  size_t accumulator = 0;
  for (size_t i = 0; i < word.size(); i++) {
    accumulator += word.at(i);
  }
  return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
  int total = 0;
  for (size_t i = 0; i < CAPACITY; i++) {
    for (const auto& p : table[i]) {
      total += p.second;
    }
  }
  return total;
}

int WordCount::getNumUniqueWords() const {
  int total = 0;
  for (size_t i = 0; i < CAPACITY; i++) {
    total += table[i].size();
  }
  return total;
}

int WordCount::getWordCount(std::string word) const {
  std::string valid = makeValidWord(word);
  if (valid.empty()) return 0;

  size_t index = hash(valid);  // valid is already lowercase
  const auto& vec = table[index];

  for (const auto& p : vec) {
    if (p.first == valid) {
      return p.second;
    }
  }
  return 0;
}

int WordCount::incrWordCount(std::string word) {
  std::string valid = makeValidWord(word);
  if (valid.empty()) return 0;

  size_t index = hash(valid);  // valid is lowercase
  auto& vec = table[index];

  for (auto& p : vec) {
    if (p.first == valid) {
      p.second += 1;
      return p.second;
    }
  }

  vec.push_back(std::make_pair(valid, 1));  // store lowercase word
  return 1;
}

int WordCount::decrWordCount(std::string word) {
  std::string valid = makeValidWord(word);
  if (valid.empty()) return -1;

  size_t index = hash(valid);  // valid is lowercase
  auto& vec = table[index];

  for (auto it = vec.begin(); it != vec.end(); ++it) {
    if (it->first == valid) {
      if (it->second > 1) {
        it->second -= 1;
        return it->second;
      } else {
        vec.erase(it);
        return 0;
      }
    }
  }
  return 0;
}


bool WordCount::isWordChar(char c) {
  return std::isalpha(c);
}

std::string WordCount::makeValidWord(std::string word) {
    std::string result;
    int len = word.length();

    for (int i = 0; i < len; ++i) {
        char c = word[i];

        if (std::isalpha(c)) {
            result += std::tolower(c);
        } else if ((c == '\'' || c == '-') &&
                   i > 0 && i < len - 1 &&
                   std::isalpha(word[i - 1]) &&
                   std::isalpha(word[i + 1])) {
            result += c;
        }
    }

    // Word must start and end with alpha character
    if (result.empty() || !std::isalpha(result.front()) || !std::isalpha(result.back())) {
        return "";
    }

    return result;
}