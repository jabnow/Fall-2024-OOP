// rec13.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// this is just to shorten the print each time
void printVec(const vector<int>& vec){
    for (int val : vec){
        cout << val << " ";
    }
    cout << endl;
}

// I templated this for part 21
template <typename T>
void printVec(const vector<T>& vec){
    for (const T& val : vec){
        cout << val << " ";
    }
    cout << endl;
}

// print out for list
void displayLst(const list<int>& lst){
    for (int val : lst){
        cout << val << " ";
    }
    cout << endl;
}

// print out for a set
void displaySet(const set<string>& set){
    for (const string& val : set){
        cout << val << " ";
    }
    cout << endl;
}

// function for task 9: iterator print out list
void printListIter(const list<int>& lst){
    for (list<int>::const_iterator iter = lst.begin(); iter != lst.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}

// function for task 10: ranged-for print out list
void printListRF(const list<int>& lst){
    for (int val : lst){
        cout << val << " ";
    }
    cout << endl;
}

// task 11: auto to print list
void printListAuto(const list<int>& lst){
    for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}

// task 12: find item in list
list<int>::const_iterator findInList(const list<int>& lst, int val){
    cout << "findInList()" << endl;
    for (list<int>::const_iterator iter = lst.begin(); iter != lst.end(); ++iter) {
        if (*iter == val) {
            return iter;    // uhm
        }
    }
    return lst.end();
}

// task 13: find item in list w/ auto
auto findInListAuto(const list<int>& lst, int val){
    cout << "findInListAuto() " << endl;
    for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
        if (*iter == val) {
            return iter;
        }
    }
    return lst.end();
}

// task 15: locate the first even number in the vector and in the list and print them out.
bool isEven(int val){
    return val % 2 == 0;
}

// task 16: functor
class Even {
public:
    bool operator()(int val){
        return val % 2 == 0;
    }
};

// task 19: make your own find algo for list of ints but template it
// This will be a function, not a function template.
list<int>::const_iterator ourFind(list<int>::const_iterator begin, list<int>::const_iterator end, int val){
    cout << "ourFind()\n";
    for (list<int>::const_iterator iter = begin; iter != end; ++iter) {
        if (*iter == val) {
            return iter;
        }
    }
    return end;
//    return find(lst.begin(), lst.end(), val);
}

// task 20: Rewrite ourFind as a function template.
template <typename T, typename K>
T ourFind(T begin, T end, K val){
    cout << "ourFind()\n";
    for (T iter = begin; iter != end; ++iter) {
        if (*iter == val) {
            return iter;
        }
    }
    return end;
}

// task 23: printMap(map)

auto printMap(const map<string, vector<int>>& map){
    for (const auto& x : map){
        cout << x.first << " ";
        printVec(x.second);
    }
    cout << endl;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vec({1, 4, 5, 7, 8, 2});
    for (int val: vec) {
        cout << val << " ";
    }
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> lst(vec.begin(), vec.end());
    for (int val: lst) {
        cout << val << " ";
    }
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vec.begin(), vec.end());
    cout << "vector: ";
    printVec(vec);
    cout << "list: ";
    displayLst(lst);
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < vec.size(); i += 2) {
        cout << vec[i] << " ";
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//    for (size_t i=0; i<lst.size(); i+=2){
//        cout << lst[i] << " ";
//    }
    cout << "there is no op[] provided for list";
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    // if the vec.length() wasn't even, then it would go out of bounds to undef territory
    cout << "Task 6:\n";
    // Task: Write a loop to print every other element of the vector
    cout << "using iterators\n";
    for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter += 2) {
        cout << *iter << " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator iter = lst.begin(); iter != lst.end(); ++iter) {
        cout << *iter << " ";
        ++iter;
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    displayLst(lst);
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    // First try using list::iterator as before and observe that you get a compilation error.
    // Try again using list::const_iterator. It works! But what a pain!
    printListIter(lst);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListRF(lst);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alternate
    // items in the list
    cout << "Task 11:\n";
    printListAuto(lst);
    cout << "=======\n";

    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << *findInList(lst, 4);     // test with value in lst
    cout << endl;
    cout << "testing value not in list:\n";
    cout << *findInList(lst, 23);    // test with value not in lst
    cout << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << *findInListAuto(lst, 4);
    cout << endl;
    cout << "testing value not in list:\n";
    cout << *findInListAuto(lst, 23);
    cout << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << *find(lst.begin(), lst.end(), 4);
    cout << endl;
    cout << "testing value not in list:\n";
    cout << *find(lst.begin(), lst.end(), 23);
    cout << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    cout << "first even in the list found: ";
    cout << *find_if(lst.begin(), lst.end(), isEven);   // isEven returns a bool
    cout << endl;
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    cout << "first even in the list found (functor): ";
    cout << *find_if(lst.begin(), lst.end(), Even());   // isEven returns a bool
    cout << endl;
    cout << "=======\n";

    // 17. Lambda
    cout << "Task 17:\n";
    // example lambda
//    [] { cout << "Hello Lambda!"; }();
    //    [] (int a, int b) { cout << a + b << endl; } (4, 5);
    // example lambda sum
    // int result = [] (int a, int b) { return a + b; } (4, 5);
    //    cout << "the result is: " << result << endl;
    // now specifying the return type (optional)
    // int result2 = [] (int a, int b) -> int { return a + b; } (4, 5);
    //    cout << "the result is: " << result2 << endl;
    cout << *find_if(
            lst.begin(), lst.end(), [](int val) { return (val & 2) == 0; }
    );
    cout << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int *dyna = new int[6];
    copy(lst.begin(), lst.end(), dyna);
    for (size_t i = 0; i < 6; ++i) {
        cout << dyna[i] << " ";
    }
    // Don't forget to free the space from the heap!!!
    delete[] dyna;
    cout << endl;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << *ourFind(lst.begin(), lst.end(), 4);
    cout << endl;
    cout << "testing value not in list:\n";
    cout << *ourFind(lst.begin(), lst.end(), 23);
    cout << endl;
    cout << "=======\n";

    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << *ourFind(lst.begin(), lst.end(), 4);
    cout << endl;
    cout << "testing value not in list:\n";
    cout << *ourFind(lst.begin(), lst.end(), 23);
    cout << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    // vector of strings for each word
    vector<string> read;
    // open file
    ifstream ifs("pooh-nopunc.txt");
    if (!ifs) {
        cout << "failed to open\n";
        exit(1);
    }
        string word;
        while (ifs >> word) {
            if (find(read.begin(), read.end(), word) == read.end()) {
                read.push_back(word);
            }
    }   // close file
    ifs.close();
    // display size and content
    cout << "size\n";
    cout << read.size() << endl;
    cout << "content\n";
    printVec(read);
    cout << endl;
    // add distinct tokens to another vector
    // print out 1 line only with the number of distinct tokens: 2,278
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    // do previous but with a set
    set<string> words;
    ifs.open("pooh-nopunc.txt");
    if (!ifs) {
        cout << "failed to open\n";
        exit(1);
    }
    while (ifs >> word){
//        find(words.begin(), words.end(), word);
        words.insert(word);
    }
    ifs.close();
    cout << words.size() << endl;
    displaySet(words);
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    int pos = 0;
    // use auto for the ranged for, (key, value)
    // For each item in the map, first print out the word and then print out all of the positions.
    // It would look best to do this all on one line for each word.
    ifs.open("pooh-nopunc.txt");
    if (!ifs) {
        cout << "failed to open\n";
        exit(1);
    }
    // insert
    while (ifs >> word){
        ++pos;
        wordMap[word].push_back(pos);
    }
    // now print out everything
    printMap(wordMap);
    cout << "=======\n";
    }