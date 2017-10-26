#ifndef UTIL_HPP
#define UTIL_HPP


#include "DictionaryTrie.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <iostream>


using std::istringstream;
using std::string;
using std::vector;

using std::istream;

/*
 * This class if for loading a text file
 */
class Util{
public:

    /*
     * Load the words in the file into the dictionary
     */
    void static load_dict(DictionaryTrie& dict, istream& words);

};


#endif //UTIL_HPP
