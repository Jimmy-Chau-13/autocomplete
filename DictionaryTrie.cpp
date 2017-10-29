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

/* Insert a word into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not invalid (empty string)
 */
bool DictionaryTrie::insert(std::string word, unsigned int theFrequency)
{
  theWord = word;
  if(theWord.empty()) return false;
  the_freq = theFrequency;
  std::cout << "INSERTING: " << theWord  << std::endl;
  index = 0;
  return insertHelp(root);

}

/* Helper method to insert a word recursively
 */
bool DictionaryTrie::insertHelp(TrieNode* prevNode)
{

  char letter = tolower( theWord.at(index) );
  //std::cout << "LETTER IS : " << letter  << std::endl;
  // Check if valid ascii value
  int letterValue;
  if(letter == 39)
    letterValue = 26;
  else if(letter == 45)
    letterValue = 27;
  else if (letter >= 97 && letter <= 122)
    letterValue = letter - 97;
  else {
    std::cout << "Failed to insert " << theWord  << std::endl;
    return false;
  }

  // case when prefix does exist
  if(prevNode->arr[letterValue] != 0)
      prefixExist(prevNode, letterValue);

  // case when prefix does not exist
  else
    noPrefix(prevNode, letterValue);

  TrieNode* current = prevNode->arr[letterValue];
  current->allWords.push(end);

  return true;
}

void DictionaryTrie::prefixExist(TrieNode* prevNode, int letter)
{

    curr = prevNode->arr[letter];
    if(index == theWord.length() - 1)
       lastChar();
    else {
      index++;
      insertHelp(curr);
    }
}

void DictionaryTrie::noPrefix(TrieNode* prevNode, int letter)
{
  curr = new TrieNode();
  //curr->freq = 0;
  prevNode->arr[letter] = curr;
  curr->c = theWord.at(index);

  // update the string of the node
  curr->s += prevNode->s + theWord.at(index);
  if(index == theWord.length() - 1)
     lastChar();

  else {
    index++;
    insertHelp(curr);
  }
}

/* Update the node of the last letter in the word
 */
void DictionaryTrie::lastChar()
{
    curr->freq = the_freq;
    curr->exist = true;
    //std::cout << "FREQUENCY: " << curr->freq  << std::endl;
    end = curr;

}

/* Return true if word is in the dictionary and increase its freq by 1
 * false otherwise
 */
bool DictionaryTrie::find(std::string word) const
{
  if(root == 0)
    return false;

  TrieNode* pos = root;

  for(unsigned int i = 0; i < word.length(); i++)
  {
    char letter = word.at(i);
    // Check if valid ascii value
    if (letter-97 < 0 || letter-97 > 26)
      return false;

    if(pos->arr[letter - 97] == 0)
      return false;
    else
      pos = pos->arr[letter - 97];
  }

  if(pos->exist) {
    pos->freq = pos->freq + 1;
    //std::cout << "FREQUENCY: " << pos->freq  << std::endl;
    return true;
  }
  else
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
    int letterValue;
    if(letter == 39)
     letterValue = 26;
    else if(letter == 45)
     letterValue = 27;
    else if (letter >= 97 && letter <= 122)
     letterValue = letter - 97;
    else {
      return words;
    }

    if(pos->arr[letterValue] == 0)
      return words;
    else
     pos = pos->arr[letterValue];
  }

  // Grab all the results
  int amount [num_completions];
  int i = 0;
  while(!pos->allWords.empty() && num_completions != 0)
  {
    TrieNode* res = pos->allWords.top();
    words.push_back(res->s);
    pos->copy.push(res);

    amount[i] = res->freq;
    //std::cout << "ARRAY: " << amount[i] << std::endl;
    i = i + 1;

    pos->allWords.pop();
    num_completions--;
  }

  // Push results back into allWords
  while(!pos->copy.empty()) {
    pos->allWords.push( pos->copy.top()    );
    pos->copy.pop();
  }

    wordFreqs = amount;
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
