/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <deque>

//using namespace std;


/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

  // Add your own data members and methods here
  class TrieNode
  {
    public:

      std::vector<TrieNode*> arr;
      int freq;
      bool exist;
      char c;
      std::string s;

	/* used to compare the frequencies of the nodes */
	class TrieNodePtrComp
	{
		public:

			bool operator()(TrieNode*& lhs, TrieNode*& rhs) const {
    		return *rhs < *lhs;
  		}
	};

  	std::priority_queue<TrieNode*, std::vector<TrieNode*>, TrieNodePtrComp> allWords;

    TrieNode()
     {
       arr = std::vector<TrieNode*>(27, (TrieNode*)0);
       freq = 0;
       exist = false;
       c = 0;
     };

		bool operator<( TrieNode const & other) {
	 		return freq > other.freq;
	}

    private:
  };

  TrieNode* root;
  TrieNode* end;

	/* helper method to recursively insert */
  bool insertHelp(std::string word, unsigned int freq, unsigned int index, TrieNode* prevNode);

	/* helper method to recursively delete the tree */
  void deleteAll(TrieNode* n);

};

#endif // DICTIONARY_TRIE_HPP
