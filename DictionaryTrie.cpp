/*
 * This program creates a multiway trie and inserts nodes that contain a vector
 * of the alphabet. It returns true or false if a word exists return true
 * or false.It can take in a prefix and find the most frequent words that
 * can be created from that prefix
 */

#include "util.hpp"
#include "DictionaryTrie.hpp"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
  root = new TrieNode();
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word)
{
  theWord = word;
  index = 0;
  insertHelp(root);
  return false;
}

/* Helper method to insert a word recursively
 */
bool DictionaryTrie::insertHelp(TrieNode* prevNode)
{

  char letter = theWord.at(index);	  // holds the next char in word
  // case when prefix does exist
  if(prevNode->arr[letter - 97] != 0)
      prefixExist(prevNode, letter);

  // case when prefix does not exist
  else
  {
    noPrefix(prevNode, letter);
    TrieNode* current = prevNode->arr[letter-97];
    current->allWords.push(end);
  }
  
  return true;
}

void DictionaryTrie::prefixExist(TrieNode* prevNode, char letter)
{
  // case when prefix does exist
    curr = prevNode->arr[letter- 97];

    // if it is the last char in word then set freq and boolean
    // as well as push itself into its own priority queue
    if(index == theWord.length() - 1)
      lastChar();
    else {
      index++;
      insertHelp(curr);
    }
}

void DictionaryTrie::noPrefix(TrieNode* prevNode, char letter)
{
  curr = new TrieNode();
  curr->freq = 0;
  prevNode->arr[letter - 97] = curr;
  curr->c = letter;

  // update the string of the node
  curr->s += prevNode->s + letter;
  if(index == theWord.length() - 1)
     lastChar();
  else {
    index++;
    insertHelp(curr);
  }
}

void DictionaryTrie::lastChar()
{
    curr->freq = curr->freq++;
    curr->exist = true;
    end = curr;

}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  if(root == 0)
    return false;

  TrieNode* pos = root;

  for(unsigned int i = 0; i < word.length(); i++)
  {
    char letter = word.at(i);
    if(letter == ' ')
      letter = 26+97;

    if(pos->arr[letter - 97] == 0)
      return false;
    else
      pos = pos->arr[letter - 97];
  }

  if(pos->exist)
    return true;

  return false;
}

std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;

  // check if num_completions is valid
  if(num_completions == 0)
    return words;

  // checks if prefix is valid else go to the node at the end of the prefix
  TrieNode* pos = root;
  for(unsigned int i = 0; i < prefix.length(); i++)
  {
     char letter = prefix.at(i);
     if(letter == ' ')
       letter = 26+97;
     if(pos->arr[letter-97] == 0)
       return words;
     else
       pos = pos->arr[letter - 97];
  }

  // insert into vector
  while(!pos->allWords.empty() && num_completions != 0)
  {
    words.push_back(pos->allWords.top()->s);
    pos->allWords.pop();
    num_completions--;
  }

    return words;
}

/* helper method to deconstruct the tree */
void DictionaryTrie::deleteAll(TrieNode* n)
{
  for(int i = 0; i < 27; i++)
  {
    if(n->arr[i] != 0)
      deleteAll(n->arr[i]);
  }
  delete n;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
  deleteAll(root);
}
