#include "WordCount.h"
#include "tddFuncs.h"

int main() {
  WordCount wc;

  // Edge: Empty and invalid inputs
  ASSERT_EQUALS(0, wc.incrWordCount(""));
  ASSERT_EQUALS(0, wc.getTotalWords());

  ASSERT_EQUALS(0, wc.incrWordCount("@#$%"));

  // Edge: invalid leading/trailing punctuation
  ASSERT_EQUALS("", WordCount::makeValidWord("-start"));
  ASSERT_EQUALS("", WordCount::makeValidWord("end-"));
  ASSERT_EQUALS("", WordCount::makeValidWord("'start"));
  ASSERT_EQUALS("", WordCount::makeValidWord("end'"));

  // Edge: multiple punctuation
  ASSERT_EQUALS("goodhearted", WordCount::makeValidWord("good--hearted"));
  ASSERT_EQUALS("can'tdo", WordCount::makeValidWord("can't''do"));

  // Edge: single character word
  ASSERT_EQUALS(1, wc.incrWordCount("A"));
  ASSERT_EQUALS(1, wc.getWordCount("a"));

  // Edge: case insensitivity
  ASSERT_EQUALS(1, wc.incrWordCount("Monkey"));
  ASSERT_EQUALS(2, wc.incrWordCount("MONKEY"));  // already 1 from "Monkey"
  ASSERT_EQUALS(3, wc.incrWordCount("monkey"));
  ASSERT_EQUALS(3, wc.getWordCount("Monkey"));

  // Edge: mixed junk chars
  ASSERT_EQUALS("monkey", WordCount::makeValidWord("12%$MoNkEy!@"));

  // Edge: test different hash keys (not string-colliding)
  ASSERT_EQUALS(1, wc.incrWordCount("hello1"));
  ASSERT_EQUALS(1, wc.incrWordCount("goodbye"));
  ASSERT_EQUALS(1, wc.getWordCount("hello1"));
  ASSERT_EQUALS(1, wc.getWordCount("goodbye"));

  // Edge: very long valid word
  std::string longWord = "pneumonoultramicroscopicsilicovolcanoconiosis";
  ASSERT_EQUALS(1, wc.incrWordCount(longWord));
  ASSERT_EQUALS(1, wc.getWordCount(longWord));

  // Edge: mixed digit+letters input
  ASSERT_EQUALS("paive", WordCount::makeValidWord("pa55ive"));

  // Edge: multiple case variations
  ASSERT_EQUALS(1, wc.incrWordCount("Apple"));
  ASSERT_EQUALS(2, wc.incrWordCount("apple"));
  ASSERT_EQUALS(3, wc.incrWordCount("APPLE"));  // Add another
  ASSERT_EQUALS(4, wc.incrWordCount("aPpLe"));
  ASSERT_EQUALS(4, wc.getWordCount("APPLE"));

  // Edge: decr non-existent word
  ASSERT_EQUALS(-1, wc.decrWordCount("nonexistent"));

  // Edge: insert + delete
  ASSERT_EQUALS(1, wc.incrWordCount("MonkeyKing"));
  ASSERT_EQUALS(0, wc.decrWordCount("monkeyking"));
  ASSERT_EQUALS(0, wc.getWordCount("MONKEYKING"));

  // Edge: digit/symbol cleaning
  ASSERT_EQUALS("monkeys", WordCount::makeValidWord("12mOnkEYs-$"));

  return 0;
}