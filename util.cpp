
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
  std::unordered_map<std::string,unsigned int>::iterator got;
  std::unordered_map<std::string,unsigned int> word_map;

  while(getline(words, data))
    {
      data = data + " .";
      istringstream iss(data);

      while(1)
        {
          string temp = "";
          iss >> temp;
          if(temp == ".") break;
          got = word_map.find(temp);
          if ( got == word_map.end() )
            word_map.insert( {temp,1} );
          else
             got->second =  got->second + 1;
        }
    }

    std::unordered_map<std::string, unsigned int>::iterator it = word_map.begin();
    while(it!=word_map.end()) {
      dict.insert(it->first, it->second);
      it++;
    }
}
