CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -g

TARGETS = lab06Test01 lab06Test02 lab06Test03 lab06Test04
OBJS_COMMON = WordCount.o tddFuncs.o

all: $(TARGETS)

lab06Test01: lab06Test01.o $(OBJS_COMMON)
	$(CXX) $(CXXFLAGS) -o lab06Test01 lab06Test01.o $(OBJS_COMMON)

lab06Test02: lab06Test02.o $(OBJS_COMMON)
	$(CXX) $(CXXFLAGS) -o lab06Test02 lab06Test02.o $(OBJS_COMMON)

lab06Test01.o: lab06Test01.cpp WordCount.h tddFuncs.h
	$(CXX) $(CXXFLAGS) -c lab06Test01.cpp

lab06Test02.o: lab06Test02.cpp WordCount.h tddFuncs.h
	$(CXX) $(CXXFLAGS) -c lab06Test02.cpp

lab06Test03: lab06Test03.o WordCount.o tddFuncs.o
	$(CXX) $(CXXFLAGS) -o lab06Test03 lab06Test03.o WordCount.o tddFuncs.o

lab06Test03.o: lab06Test03.cpp WordCount.h tddFuncs.h
	$(CXX) $(CXXFLAGS) -c lab06Test03.cpp

lab06Test04: lab06Test04.o WordCount.o tddFuncs.o
	$(CXX) $(CXXFLAGS) -o lab06Test04 lab06Test04.o WordCount.o tddFuncs.o

lab06Test04.o: lab06Test04.cpp WordCount.h tddFuncs.h
	$(CXX) $(CXXFLAGS) -c lab06Test04.cpp

WordCount.o: WordCount.cpp WordCount.h
	$(CXX) $(CXXFLAGS) -c WordCount.cpp

tddFuncs.o: tddFuncs.cpp tddFuncs.h
	$(CXX) $(CXXFLAGS) -c tddFuncs.cpp

clean:
	rm -f *.o $(TARGETS)