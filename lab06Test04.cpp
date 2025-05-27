#include "WordCount.h"
#include "tddFuncs.h"

int main() {
  WordCount wc1, wc2, wc3;

  // --- makeValidWord tests (testWordCount00.cpp) ---
  ASSERT_EQUALS("foo", WordCount::makeValidWord(".foo"));
  ASSERT_EQUALS("bar", WordCount::makeValidWord("bar?"));
  ASSERT_EQUALS("fum", WordCount::makeValidWord("...fum***"));
  ASSERT_EQUALS("quote", WordCount::makeValidWord("\"quote\""));
  ASSERT_EQUALS("isn't", WordCount::makeValidWord("isn't"));
  ASSERT_EQUALS("mother-in-law", WordCount::makeValidWord("mother-in-law"));
  ASSERT_EQUALS("art", WordCount::makeValidWord("'aRT-*"));
  ASSERT_EQUALS("s", WordCount::makeValidWord("$-s'-#"));
  ASSERT_EQUALS("", WordCount::makeValidWord("$$*-'-!"));
  ASSERT_EQUALS("", WordCount::makeValidWord(""));

  // --- isWordChar tests (testWordCount01.cpp) ---
  ASSERT_TRUE(WordCount::isWordChar('f'));
  ASSERT_TRUE(WordCount::isWordChar('T'));
  ASSERT_TRUE(!WordCount::isWordChar(0));
  ASSERT_TRUE(!WordCount::isWordChar('^'));
  ASSERT_TRUE(!WordCount::isWordChar(' '));

  // --- incrWordCount basic tests (testWordCount02.cpp) ---
  ASSERT_EQUALS(0, wc1.getTotalWords());
  ASSERT_EQUALS(0, wc1.getNumUniqueWords());
  ASSERT_EQUALS(1, wc1.incrWordCount("foo"));
  ASSERT_EQUALS(2, wc1.incrWordCount("foo"));
  ASSERT_EQUALS(3, wc1.incrWordCount("foo"));
  ASSERT_EQUALS(1, wc1.incrWordCount("bar"));
  ASSERT_EQUALS(2, wc1.incrWordCount("bar"));
  ASSERT_EQUALS(1, wc1.incrWordCount("foobar"));
  ASSERT_EQUALS(6, wc1.getTotalWords());
  ASSERT_EQUALS(3, wc1.getNumUniqueWords());

  // --- hashing/collisions and normalization (testWordCount03.cpp) ---
  ASSERT_EQUALS(1, wc2.incrWordCount("foO"));       // foo
  ASSERT_EQUALS(2, wc2.incrWordCount("foo"));       // foo
  ASSERT_EQUALS(1, wc2.incrWordCount("bAr"));       // bar
  ASSERT_EQUALS(2, wc2.incrWordCount("BaR"));       // bar
  ASSERT_EQUALS(1, wc2.incrWordCount("foo#bar"));   // foobar
  ASSERT_EQUALS(2, wc2.incrWordCount("foo_bar-"));  // foobar
  ASSERT_EQUALS(3, wc2.incrWordCount("'foo-bar-")); // foobar
  ASSERT_EQUALS(0, wc2.incrWordCount("--$$--"));    // cleaned to ""
  ASSERT_EQUALS(7, wc2.getTotalWords());
  ASSERT_EQUALS(3, wc2.getNumUniqueWords());

  // --- chaining test (testWordCount04.cpp) ---
  ASSERT_EQUALS(1, wc3.incrWordCount("foo"));
  ASSERT_EQUALS(1, wc3.incrWordCount("oof"));
  ASSERT_EQUALS(1, wc3.incrWordCount("ofo"));
  ASSERT_EQUALS(3, wc3.getTotalWords());
  ASSERT_EQUALS(3, wc3.getNumUniqueWords());

  ASSERT_EQUALS(1, wc3.incrWordCount("isn't"));
  ASSERT_EQUALS(2, wc3.incrWordCount("$#'isn't--")); // cleaned = "isn't"
  ASSERT_EQUALS(1, wc3.incrWordCount("n'ist"));
  ASSERT_EQUALS(6, wc3.getTotalWords());
  ASSERT_EQUALS(4, wc3.getNumUniqueWords());
  ASSERT_EQUALS(2, wc3.getWordCount("isn't"));
  ASSERT_EQUALS(1, wc3.getWordCount("n'ist"));
  ASSERT_EQUALS(1, wc3.getWordCount("ofo"));

  // --- decrWordCount test (testWordCount05.cpp) ---
  ASSERT_EQUALS(0, wc3.decrWordCount("apple")); // not found
  wc3.incrWordCount("apple");
  ASSERT_EQUALS(1, wc3.getTotalWords());
  ASSERT_EQUALS(1, wc3.getNumUniqueWords());
  ASSERT_EQUALS(1, wc3.getWordCount("apple"));
  ASSERT_EQUALS(2, wc3.incrWordCount("foo"));
  ASSERT_EQUALS(3, wc3.getTotalWords());
  ASSERT_EQUALS(2, wc3.getNumUniqueWords());
  ASSERT_EQUALS(2, wc3.getWordCount("foo"));
  ASSERT_EQUALS(1, wc3.decrWordCount("foo"));
  ASSERT_EQUALS(2, wc3.getTotalWords());
  ASSERT_EQUALS(2, wc3.getNumUniqueWords());
  ASSERT_EQUALS(1, wc3.getWordCount("foo"));
  ASSERT_EQUALS(0, wc3.decrWordCount("foo")); // removed
  ASSERT_EQUALS(1, wc3.incrWordCount("oof"));
  ASSERT_EQUALS(1, wc3.incrWordCount("ofo"));
  ASSERT_EQUALS(2, wc3.incrWordCount("OFO"));  // "ofo"
  ASSERT_EQUALS(3, wc3.incrWordCount("^Ofo2")); // cleaned = "ofo"
  ASSERT_EQUALS(3, wc3.getWordCount("Ofo"));
  ASSERT_EQUALS(2, wc3.decrWordCount("1ofO-")); // cleaned = "ofo"
  ASSERT_EQUALS(4, wc3.getTotalWords());
  ASSERT_EQUALS(3, wc3.getNumUniqueWords());

  return 0;
}