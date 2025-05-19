// WordCount.cpp

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {}

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
  if (valid == "") return 0;
  size_t index = hash(valid);
  for (const auto& p : table[index]) {
    if (p.first == valid) {
      return p.second;
    }
  }
  return 0;
}
	
int WordCount::incrWordCount(std::string word) {
  std::string valid = makeValidWord(word);
  if (valid == "") return 0;
  size_t index = hash(valid);
  for (auto& p : table[index]) {
    if (p.first == valid) {
      p.second += 1;
      return p.second;
    }
  }
  table[index].push_back(std::make_pair(valid, 1));
  return 1;
}

int WordCount::decrWordCount(std::string word) {
  std::string valid = makeValidWord(word);
  if (valid == "") return -1;
  size_t index = hash(valid);
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
  return -1;
}

bool WordCount::isWordChar(char c) {
	return std::isalpha(c);
}

std::string WordCount::makeValidWord(std::string word) {
  std::string result;
  int len = word.length();

  for (int i = 0; i < len; i++) {
    if (std::isalpha(word[i])) {
      result += std::tolower(word[i]);
    } else if ((word[i] == '\'' || word[i] == '-') && i > 0 && i < len - 1 && std::isalpha(word[i - 1]) && std::isalpha(word[i + 1])) {
      result += word[i];
    }
  }

	if (result.length() == 0) return "";
	char first = word.front();
	char last = word.back();

	if (!std::isalpha(result.front()) || !std::isalpha(result.back())) return "";

	if (first == '-' || first == '\'' || last == '-' || last == '\'') return "";
	return result;
}
