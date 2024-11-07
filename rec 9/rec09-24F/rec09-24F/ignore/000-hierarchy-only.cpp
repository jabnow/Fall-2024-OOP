#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
        PrintedMaterial(unsigned numPages) : numOfPages(numPages) {}
        // task 13
        virtual void displayNumPages() const = 0; //{cout << numOfPages;}
private:
    unsigned numOfPages;
};

//defined outside of class, task 13
void PrintedMaterial::displayNumPages() const {
    cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages) : PrintedMaterial(numPages){}
    // task 14
    void displayNumPages() const {
        cout << "override virtual method in mag class\n";
        PrintedMaterial::displayNumPages();
        cout << endl;
    }
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages) : PrintedMaterial(numPages){}
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndexPages) :
    Book(numPages), numIndexPages(numIndexPages){}
    void displayNumPages() const {
        cout << "Pages: ";
        PrintedMaterial::displayNumPages();
        cout << "Index pages: " << numIndexPages << endl;}
private:
    unsigned numIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages) :
    Book(numPages){}
    void displayNumPages() const {
        cout << "override virtual method in novel class\n";
        PrintedMaterial::displayNumPages();
        cout << endl;
    }
private:
};

// standalone function, task 12
void displayNumberOfPages(const PrintedMaterial& any) {
    any.displayNumPages();
}

// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    cout << "display text" << endl;
    text.displayNumPages();
    cout << endl;
    cout << "display novel" <<endl;
    novel.displayNumPages();
    cout << endl;
    cout << "display magazine" << endl;
    mag.displayNumPages();
    cout << endl;
    cout << "===========\n";

    // task 14, clean build
//    cout << "\nA PrintedMaterial material object!\n";
//    PrintedMaterial pm(2345);
//    cout << "display PrintedMaterial" << endl;
//    pm.displayNumPages();
//    cout << endl;

//    pm = text; // like putting a Textbook into a PrintedMaterial
//    pm.displayNumPages();
//    cout << endl;

    cout << "\nUsing PrintedMaterial* to \"store\" a TextBook object\n";
    cout << "Now with the virtual mechanism involved\n";
    // should work now that the virtual mechanism is being invoked
    PrintedMaterial* pmPtr;
    pmPtr = &text;
    pmPtr->displayNumPages();

    // print some stuff by calling a generic function
    cout << "\nUse a generic functino for printing\n";
    cout << "mag pages" << endl;
    displayNumberOfPages(mag);
    cout << endl;
    cout << "novel pages" << endl;
    displayNumberOfPages(novel);
    cout << endl;
    cout << "textbook pages" << endl;
    displayNumberOfPages(text);

    cout << "\n=====TASK 15======\n";
    vector<PrintedMaterial*> storage;
    storage.push_back(&text);
    storage.push_back(&novel);
    storage.push_back(&mag);
    //loop through the vector asking each to display
    for (const PrintedMaterial* pmPtr : storage){
        pmPtr->displayNumPages();
        cout << endl;
    }

}
