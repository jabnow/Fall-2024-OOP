//
// Created by jwang on 9/9/2024.
// This code decrypts the Caesar Cypher in encrypted.txt
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


//PROTOTYPES
char decryptChar(char&, const int&);
void modifyString(string&, const int&);

// OPENS & CLOSES FILE, COMPLETES DECRYPTION PROCESS
int main(){
    ifstream cypher("encrypted.txt");
    if (!cypher) {
        cerr << "failed to open encrypted.txt";
        return 1;
    }
    // find the encryption shift from the 1st file line
    string num;
    cypher >> num;
    // reverse the shift amount and print in the 1st line
    int undo_shift = stoi(num)*(-1);
    cout << undo_shift << endl;

    string line;
    vector<string> readLines;
    // reads line by line and puts in vector
    while (getline(cypher, line)){
        readLines.push_back(line);
    }
    // decrypts each line and modifies the vector
    for (size_t index = 0; index < readLines.size(); index++){
        modifyString(readLines[index],undo_shift);
    }
    // print out the decrypted vector backwards
    for (size_t reverse = readLines.size(); reverse > 0; reverse--){
        cout << readLines[reverse-1] << endl;
    }
    cypher.close();
}

// SHIFTS EACH LETTER IN PLACE, references characters from words and the shift amount.
// only uppercase characters are decrypted.
// A negative shift indicates a smaller letter, and a larger shift means a larger letter.
// additional +26 in calculations so that mod will not accept negatives.
// returns the changed character.
char decryptChar(char& character, const int& shift) {
    if (isupper(character)){
        return 'A' + (character + shift - 'A' + 26) % 26;
    }
    return character;
}

// MODIFIES EACH LINE OF WORDS, as stored in the vector.
// references each line from the file as a string.
// calls the decryptChar method to reconstruct each character of the string.
// no return value.
void modifyString(string& word, const int& shift) {
    // shift each character of word in place
    for (size_t index = 0; index < word.length(); index++){
        word[index] = decryptChar(word[index],shift);
    }
}
