/*
  rec10.cpp
  created by Joy Wang on 11/8/2024
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Instrument{
    // instrument output operator?
    friend ostream& operator<<(ostream& os, const Instrument& instrument){
        instrument.display(os);
        return os;
    }
public:
    virtual void makeSound() = 0;
    virtual void display(ostream& os) const = 0;
    virtual void play() = 0;
};

void Instrument::makeSound() {
    cout << "To make a sound... ";
}

class Brass : public Instrument {
public:
    Brass(int mouthpiece) : mouthpiece(mouthpiece) {}
    unsigned getSize() const {return mouthpiece;}
    void makeSound() override {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpiece << endl;
    }
private:
    unsigned mouthpiece;
};

class Trumpet : public Brass{
public:
    using Brass::Brass;
//    Trumpet() : Brass() {}
    void play()  {
        cout << "Toot";
    }
    void display(ostream& os) const override {
        os << "\tTrumpet: " << getSize();
    }
private:
};

class Trombone : public Brass{
//    Trombone() : Brass() {}
public:
    using Brass::Brass;
    void play()  {
        cout << "Blat";
    }
    void display(ostream& os) const override {
        os << "\tTrombone: " << getSize();
    }
private:
};

class String : public Instrument {
public:
    String(int pitch) : pitch(pitch){}
    unsigned getPitch() const {return pitch;}
    void makeSound() override {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
private:
    unsigned pitch;
    // assume that there's only 1 string?
};

class Violin : public String {
public:
    using String::String;
    void play() override {
        cout << "Screech";
    }
    void display(ostream& os) const override {
        os << "\tViolin: " << getPitch();
    }
private:
};

class Cello : public String {
public:
    using String::String;
    void play() {
        cout << "Squawk";
    }
    void display(ostream& os) const override {
        os << "\tCello: " << getPitch();
    }
private:
};

class Percussion : public Instrument {
public:
    using Instrument::Instrument;
    void makeSound() override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
private:
};

class Drum : public Percussion {
public:
    using Percussion::Percussion;
    void play() override {
        cout << "Boom";
    }
    void display(ostream& os) const override {
        os << "\tDrum ";
    }
private:
};

class Cymbal : public Percussion {
public:
    using Percussion::Percussion;
    void play() {
        cout << "Crash";
    }
    void display(ostream& os) const override {
        os << "\tCymbal ";
    }
private:
};

class MILL {
    friend ostream& operator<<(ostream& os, const MILL& mill){
        os << "The MILL has the following instruments: ";
        if (mill.inventory.size() == 0){
            os << "None" << endl;
            return os;
        }
        size_t count = 0;
        for (const Instrument* instr : mill.inventory){
            if (instr){
                os << "\n" << *instr;
            } else {
                count += 1;
            }
        }
        if (count == mill.inventory.size()){    // all taken
            cout << "None" << endl;
        }
        return os;
    }
public:
//    MILL() : inventory(1, nullptr){}
    void dailyTestPlay() const {
        for (Instrument* instr : inventory){
            if (instr){
                instr->makeSound();
            }
        }
    }
    void receiveInstr(Instrument& instrument){
        instrument.makeSound();
        // find the first null value
        for (Instrument*& instr : inventory){
            if (!instr){    // null
                instr = &instrument;
                return;
            }
        }
        // otherwise add new space
        inventory.push_back(&instrument);
    }
    Instrument* loanOut(){
        for (size_t i=0; i<inventory.size(); i++){
            if (inventory[i]){  // not null
                Instrument* current = inventory[i];
                inventory[i] = nullptr;
                return current;
            }
        }
        return nullptr;     // all null
    }

private:
    vector<Instrument*> inventory;
};

// 
// Musician class as provided to the students. Requires an Instrument class.
// 

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class Orch {
public:
    void addPlayer(Musician& person){
        orchestra.push_back(&person);
    }
    void play() const {
        for (Musician* player : orchestra){
            player->play();
        }
        cout << endl;
    }
private:
    vector <Musician*> orchestra;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12) ;
     Violin violin(567) ;
  
    cout << "Define the MILL -----------------------------------------------\n";
     MILL mill;
     cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
     mill.receiveInstr(trpt);
     mill.receiveInstr(violin);
     mill.receiveInstr(tbone);
     mill.receiveInstr(drum);
     mill.receiveInstr(cello);
     mill.receiveInstr(cymbal);
     cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";
  
    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;
  
    cout << "Define some Musicians------------------------------------------\n";
     Musician harpo("Harpo");
     Musician groucho("Groucho");
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
     groucho.testPlay();	 // Groucho doesn't have an instrument yet.

     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
     groucho.testPlay();
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();
     harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
     mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
     cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
        mill.dailyTestPlay();
  
    cout << "\nThe MILL at the end of Part One:\n";
     cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;

}

