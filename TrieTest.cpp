#include "DictionaryTrie.hpp"
#include "util.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

/*
 * First argument is a text file to store in the dictionary
 */
int main(int argc, char *argv[]) {


    if(argc < 2){
        std::cout << "Incorrect number of arguments." << std::endl;
        std::cout << "\t First argument: name of dictionary file." << std::endl;
        std::cout << std::endl;
        exit(-1);
    }

    std::string dict_filename = argv[1];
    std::ifstream in;
    in.open(dict_filename.c_str(), std::ios::binary);

    DictionaryTrie* dictionary_trie = new DictionaryTrie();
    Util::load_dict(*dictionary_trie, in);
    std::string prefix;
    std::cout << "Enter prefix: ";
    while(std::getline(std::cin, prefix)){


        std::cout << "\n\tUser Test: prefix= \"" << prefix ;
        std::vector<std::string> results = dictionary_trie->predictCompletions(prefix,1000);
        std::cout << "\tUser Test: results found: " <<  results.size() << "\n\n";
        for(std::vector<std::string>::iterator it = results.begin(); it != results.end(); ++it) {
          std::cout << *it << '\n';
        }
        std::cout << "Enter prefix: ";

    }
}
