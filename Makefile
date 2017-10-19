CXX = g++
CXXFLAGS = -Wall -g

TrieTest: TrieTest.o util.o DictionaryTrie.o
		$(CXX) $(CXXFLAGS) -o TrieTest TrieTest.o util.o DictionaryTrie.o

TrieTest.o: TrieTest.cpp DictionaryTrie.hpp util.hpp
		$(CXX) $(CXXFLAGS) -c TrieTest.cpp

DictionaryTrie.o: DictionaryTrie.hpp util.hpp

util.o: DictionaryTrie.hpp util.hpp
