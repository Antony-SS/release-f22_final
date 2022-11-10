/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;


    /* Your code goes here! */
    //*
    ifstream newFile(word_list_fname);
    string w;

    if(newFile.is_open()){

        while(getline(newFile, w)){  

            if(w.size() > 2){
                string string1= w.front() + w.substr(2);

                string string2 = w.substr(1);

                if(d.homophones(w, string1) && d.homophones(w, string2)){

                    ret.push_back(tuple<string, string, string>(w, string1, string2));
                    
                }
            }
        }
    }

    return ret;
}
