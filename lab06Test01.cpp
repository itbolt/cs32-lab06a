#include "WordCount.h"
#include "tddFuncs.h"

int main() {
  WordCount wc;

  ASSERT_EQUALS(0, wc.getTotalWords());
  ASSERT_EQUALS(0, wc.getNumUniqueWords());

  ASSERT_EQUALS(1, wc.incrWordCount("Monkey"));    // monkey: 1
  ASSERT_EQUALS(2, wc.incrWordCount("monkey"));    // monkey: 2
  ASSERT_EQUALS(3, wc.incrWordCount("MONKEY"));    // monkey: 3

  ASSERT_EQUALS(3, wc.getTotalWords());            // monkey: 3
  ASSERT_EQUALS(1, wc.getNumUniqueWords());        // only monkey

  ASSERT_EQUALS(1, wc.incrWordCount("Banana"));    // banana: 1
  ASSERT_EQUALS(2, wc.getNumUniqueWords());        // monkey, banana

  ASSERT_EQUALS(2, wc.decrWordCount("monkey"));    // monkey: 2
  ASSERT_EQUALS(3, wc.getTotalWords());            // banana(1) + monkey(2)

  ASSERT_EQUALS(1, wc.decrWordCount("monkey"));    // monkey: 1
  ASSERT_EQUALS(2, wc.getTotalWords());            // banana(1) + monkey(1)

  ASSERT_EQUALS(0, wc.decrWordCount("monkey"));    // monkey removed
  ASSERT_EQUALS(0, wc.getWordCount("monkey"));     // no entry
  ASSERT_EQUALS(1, wc.getNumUniqueWords());        // only banana
  ASSERT_EQUALS(1, wc.getTotalWords());            // only banana(1)

  ASSERT_EQUALS(-1, wc.decrWordCount("monkey"));   // already gone

  ASSERT_EQUALS("can't", WordCount::makeValidWord("Can't"));             // valid apostrophe
  ASSERT_EQUALS("good-hearted", WordCount::makeValidWord("Good-hearted"));// valid hyphen
  ASSERT_EQUALS("monkeys", WordCount::makeValidWord("12mOnkEYs-$"));     // strip junk

  return 0;
}