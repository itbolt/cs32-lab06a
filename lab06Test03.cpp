#include "WordCount.h"
#include "tddFuncs.h"

int main() {
  // ----- Invalid start/end punctuation tests -----
  ASSERT_EQUALS("", WordCount::makeValidWord("-start"));
  ASSERT_EQUALS("", WordCount::makeValidWord("end-"));
  ASSERT_EQUALS("", WordCount::makeValidWord("'start"));
  ASSERT_EQUALS("", WordCount::makeValidWord("end'"));
  ASSERT_EQUALS("", WordCount::makeValidWord("-can't"));
  ASSERT_EQUALS("", WordCount::makeValidWord("can't-"));
  ASSERT_EQUALS("", WordCount::makeValidWord("-mid-dle-"));
  ASSERT_EQUALS("", WordCount::makeValidWord("''"));

  // ----- Valid punctuation inside -----
  ASSERT_EQUALS("can't", WordCount::makeValidWord("Can't"));
  ASSERT_EQUALS("good-hearted", WordCount::makeValidWord("Good-hearted"));
  ASSERT_EQUALS("rock'n'roll", WordCount::makeValidWord("Rock'n'Roll"));
  ASSERT_EQUALS("x-ray", WordCount::makeValidWord("x-Ray"));

  // ----- Rejected cleaned result due to non-alpha boundaries -----
  ASSERT_EQUALS("", WordCount::makeValidWord("1234"));
  ASSERT_EQUALS("", WordCount::makeValidWord("----"));
  ASSERT_EQUALS("", WordCount::makeValidWord("''''"));

  // ----- Valid words that should clean successfully -----
  ASSERT_EQUALS("simple", WordCount::makeValidWord("Simple"));
  ASSERT_EQUALS("complexword", WordCount::makeValidWord("COMPLEXword"));
  ASSERT_EQUALS("hyphenated-word", WordCount::makeValidWord("hyphenated-word"));
  ASSERT_EQUALS("apostrophe's", WordCount::makeValidWord("Apostrophe's"));

  // ----- Words with symbols/digits to strip -----
  ASSERT_EQUALS("data", WordCount::makeValidWord("123data!@#"));
  ASSERT_EQUALS("time's", WordCount::makeValidWord("Time's!"));
  ASSERT_EQUALS("clean", WordCount::makeValidWord("...clean..."));

  return 0;
}