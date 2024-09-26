//
// Created by jwang on 9/13/2024.
// THIS CODE CLASSIFIES AND SORTS HYDROCARBONS BY FORMULA
//

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
using namespace std;

struct hydroCarb{
    int numC;
    int numH;
    vector<string> names;
};

// PARAMETERS
void open_file(ifstream&);
void fill_formula(ifstream&, vector<hydroCarb>&);
void insert_info(const string&, int&, int&, vector<hydroCarb>&);
int find_formula(const vector<hydroCarb>&, int&, int&);
void display_all(const vector<hydroCarb>&);
void display_one(const hydroCarb&);
void sort_CH(vector<hydroCarb>&);

// OPENS FILE OF HYDROCARBONS, ORGANISES THEM BY FORMULA, PRINTS
int main(){
    ifstream fileCH;
    open_file(fileCH);

    vector<hydroCarb> allCH;
    fill_formula(fileCH, allCH);

    cout << "Unsorted: \n";
    display_all(allCH);
    sort_CH(allCH);
    cout << '\n';
    cout << "Sorted: \n";
    display_all(allCH);

    return 0;
}

// OPENS FILE ONLY IF NAME IS CORRECT
void open_file(ifstream& file){
    string input;
    do {
        cout << "\nInput a file name\n";
        cin >> input;
        file.open(input);
    } while (!file);
}

// OBTAINS #C AND #H FROM EACH LINE IN THE FILE
void fill_formula(ifstream& file, vector<hydroCarb>& allCH){
    char carbon, hydrogen;
    int numCarbon, numHydro;
    string getFormula;
    while (file >> getFormula >> carbon >> numCarbon >> hydrogen >> numHydro){
        insert_info(getFormula, numCarbon, numHydro, allCH);
    }
}

// DETERMINES WHETHER HYDROCARBON WITH SAME FORMULA ALREADY EXISTS
void insert_info(const string& name, int& numCarbon, int& numHydro, vector<hydroCarb>& allCH){
    int index = find_formula(allCH, numCarbon, numHydro);
    if (index < allCH.size()){
        // FORMULA EXISTS, ADD MOLECULE NAME TO ITS FORMULA VECTOR
        allCH[index].names.push_back(name);
    } else {
        // FORMULA DOESN'T EXIST YET, ADD MOLECULE TO allCH VECTOR
        hydroCarb formula;
        formula.numC = numCarbon;
        formula.numH = numHydro;
        formula.names.push_back(name);
        allCH.push_back(formula);
    }
}

// IF THE FORMULA EXISTS IN allCH, RETURN ITS INDEX, OTHERWISE RETURN allCH.size()
int find_formula(const vector<hydroCarb>& allCH, int& numCarbon, int& numHydro){
    for (size_t index = 0; index < allCH.size(); index++){
        if ((numCarbon == allCH[index].numC) && (numHydro == allCH[index].numH)) {
            return int(index);
        }
    }
    return int(allCH.size());
}

// CALLS display_one TO PRINT ALL THE MOLECULES
void display_all(const vector<hydroCarb>& allCH){
    for (const hydroCarb& someCH : allCH){
        display_one(someCH);
    }
}

// FORMATS ONE LINE OF OUTPUT BY FORMULA AND ALL MOLECULES WITH THE FORMULA
void display_one(const hydroCarb& oneCH){
    cout << 'C' << oneCH.numC << 'H' << oneCH.numH;
    for (const string& name : oneCH.names){
        cout << ' ' << name;
    }
    cout << endl;
}

// USE INSERTION SORT TO ORDER FORMULAS BY LEAST #Cs, THEN #Hs
void sort_CH(vector<hydroCarb>& allCH){
    // COMPARES ADJACENT, THE SMALLER IS PUSHED FORWARD
    for (size_t discover_i = 1; discover_i < allCH.size(); discover_i++){
        // FINDING THE PLACE FOR THE SMALLER AMONG ALREADY SORTED
        for (size_t sort_i = discover_i; sort_i > 0; sort_i--){
            if(allCH[sort_i].numC < allCH[sort_i-1].numC){
                swap(allCH[sort_i], allCH[sort_i-1]);
            } else if ((allCH[sort_i].numC == allCH[sort_i-1].numC) &&
                    (allCH[sort_i].numH < allCH[sort_i-1].numH)) {
                swap(allCH[sort_i], allCH[sort_i-1]);
            } else {
                break; // already sorted
            }
        }
    }

}

