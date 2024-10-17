/*
  words.cpp
  Sec 
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Word {
    string token;
    vector<int> positions;
};

int main() {

    ifstream textStream("jabberwocky");
    if (!textStream) {
	cerr << "failed to open jabberwocky\n";
	exit(1);
    }


    vector<Word> words;

    string token;
    int where = 0;
    while (textStream >> token) {
        // Have we seen it?
        size_t index = findToken(token, words);

        // If we haven't
        if (index == words.size()) {
            Word aWord;
            aWord.token = token;
            aWord.positions.push_back(where);
            words.push_back(aWord);
        }
        // if we have
        else {
            
        }
        

        ++where;

    }

}
