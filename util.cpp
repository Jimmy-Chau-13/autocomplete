
#include "DictionaryTrie.hpp"
//#include "DictionaryHashtable.hpp"
//#include "DictionaryBST.hpp"
#include "util.hpp"



/*
 * Loads the text file by grabbing each word and inserting it
 * into the dictionary.
 * Case Sensitive
 * no puncuation functionality added yet
 */
void Util::load_dict(DictionaryTrie& dict, istream& words)
{

  // Stores extracted words from istream
  string data = "";

  while(getline(words, data))
    {
      data = data + " .";
      istringstream iss(data);

      while(1)
        {
          string temp = "";
          iss >> temp;
          std::cout << temp << std::endl;
          if(temp == ".") break;
          dict.insert(temp);
        }

      //word_string.clear();
      //if(words.eof()) break;
    }
}
