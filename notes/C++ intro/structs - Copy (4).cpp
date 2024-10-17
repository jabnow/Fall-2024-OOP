/*
  structs.cpp
  
  Demonstrate defining and using a struct
  24F Sec E
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Motorcycle {
    string model;
    int cc;
};

//void printBike(Motorcycle mot) {
//void printBike(Motorcycle& mot) {
void printBike(const Motorcycle& mot) {
   cout << "Model: " << mot.model << ", cc: " << mot.cc << endl;
}

int main() {
    Motorcycle myBike;

    //cout << myBike << endl;
    cout << "Model: " << myBike.model << ", cc: " << myBike.cc << endl;

    //    string s;

    myBike.model = "VStrom";
    myBike.cc = 650;
    cout << "Model: " << myBike.model << ", cc: " << myBike.cc << endl;

    Motorcycle dreamBike {"Boneville", 1000};
    cout << "Model: " << dreamBike.model << ", cc: " << dreamBike.cc << endl;

    printBike(myBike);
    printBike(dreamBike);

    Motorcycle someBike;
    someBike = dreamBike;

    ifstream bikeStream("bikes.txt");
    if (!bikeStream) {
        cout << "Failed to open bikes.txt";
        exit(1);
    }

    vector<Motorcycle> bikes;

    // string model;
    // int cc;
    // while (bikeStream >> model >> cc) {
    //     Motorcycle mot { model, cc };
    //     bikes.push_back(mot);
    // }

    Motorcycle mot;
    while (bikeStream >> mot.model >> mot.cc) {
        bikes.push_back(mot);
    }
    bikeStream.close();

    //for (int index = 0; index < bikes.size(); ++index) {
    for (size_t index = 0; index < bikes.size(); ++index) {
        printBike(bikes[index]);
    }

    //for (Motorcycle m : bikes) {
    //for (Motorcycle& m : bikes) {
    for (const Motorcycle& m : bikes) {
        printBike(m);
    }


}
