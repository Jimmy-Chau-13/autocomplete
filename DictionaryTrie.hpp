#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <deque>
#include <ctype.h>

/**
 *  The class for a dictionary ADT, implemented as a trie
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
  bool insert(std::string word);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Destructor */
  ~DictionaryTrie();

  class TrieNode
  {
    public:

      std::vector<TrieNode*> arr;
      int freq;           /* If it is a word stores the frequency of it */
      bool exist;             /* true if it is a word, else false */
      char c;                 /* the char this node contains */
      std::string s;          /* Concatenates the current path */


	/* used to compare the frequencies of the nodes */
	class TrieNodePtrComp
	{
		public:

			bool operator()(TrieNode*& lhs, TrieNode*& rhs) const {
    		return *rhs < *lhs;
  		}
	};

    /* Stores all nodes of which this is a prefix of */
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
  TrieNode* curr;
  unsigned int index;
  std::string theWord;

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

	/* helper method to recursively insert */
  bool insertHelp(TrieNode* prevNode);

  void prefixExist(TrieNode* prevNode, char letter);

  void noPrefix(TrieNode* prevNode, char letter);

  void lastChar();

	/* helper method to recursively delete the tree */
  void deleteAll(TrieNode* n);

};

#endif // DICTIONARY_TRIE_HPP
