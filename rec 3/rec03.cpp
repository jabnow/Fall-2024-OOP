/*
  rec03_start.cpp
  2024 Fall
  Joy Wang
  Bank Accounts tutorial-style
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account{
    string name;
    int number;
};


// Task 2
// Define an Account class (use a different name than in Task 1)
class Acct{
    friend ostream& operator <<(ostream& os, const Acct& someAcct);
public:
    //void setName(string& acctName){name = acctName;}
    //void setNum(int acctNumber){acc_num = acctNumber;}
    const string& getName() const {return name;}
    int getNum() const {return acc_num;}
    Acct(const string& accName, int accNumber) : name(accName) {
//        name = accName;
        acc_num = accNumber;
    }
private:
    string name;
    int acc_num;

};
ostream& operator <<(ostream& os, const Acct& someAcct){
    // os  << "Account: " << someAcct.getName() << "   Number: " << someAcct.getNum();
    os << "Account: " << someAcct.name << "   Number: " << someAcct.acc_num;
    return os;
}

// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside the Account class, i.e. it is not "nested".

class Transaction{

public:
    const string& getAction() const {return action_type;}
    int getAmount() const {return amount;}
    Transaction(const string& input_action, int money) : action_type(input_action) {
        amount = money;
    }
private:
    string action_type; // "Deposit" or "Withdrawal"
    int amount;

};
ostream& operator <<(ostream& os, const Transaction& transact){
    os  << "\t" << transact.getAction() <<  ' ' << transact.getAmount();
    return os;
}

class Acct2{

public:
    Acct2(const string& input_name, int account_num) : acc_name(input_name) {
        acc2_num = account_num;
    }
    void deposit(int money){
        Transaction entry("deposit", money);
        history.emplace_back(entry);
        balance += money;
    }
    void withdraw(int money){
        if (balance < money){
            cout << "Account# " << acc2_num << " has only " << balance <<
            ". Insufficient for withdrawal of " << money << ".\n";
        } else {
            Transaction entry("withdrawal", money);
            history.emplace_back(entry);
            balance -= money;
        }
    }
    int getacc2_num()  const {return acc2_num;}
    const string& getName() const {return acc_name;}
    const vector<Transaction>& getHistory() const {return history;}
private:
    string acc_name;
    int acc2_num;
    int balance = 0;
    vector<Transaction> history;
};
ostream& operator <<(ostream& os, const Acct2& account2){
    os << account2.getName() << ' ' << account2.getacc2_num() << ":\n";
    for (const Transaction& some_entry : account2.getHistory()){
        os << some_entry << '\n';
    }
    return os;
}

// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.
class Acct4{
public:
    class Transaction{
    public:
        const string& getAction() const {return action_type;}
        int getAmount() const {return amount;}
        Transaction(const string& input_action, int money) : action_type(input_action) {
            amount = money;
        }
    private:
        string action_type; // "Deposit" or "Withdrawal"
        int amount;

    };
    Acct4(const string& input_name, int account_num) : acc_name(input_name) {
        acc4_num = account_num;
    }
    void deposit(int money){
        Transaction entry("deposit", money);
        history.emplace_back(entry);
        balance += money;
    }
    void withdraw(int money){
        if (balance < money){
            cout << "Account# " << acc4_num << " has only " << balance <<
                 ". Insufficient for withdrawal of " << money << ".\n";
        } else {
            Transaction entry("withdrawal", money);
            history.emplace_back(entry);
            balance -= money;
        }
    }
    int getacc4_num()  const {return acc4_num;}
    const string& getName() const {return acc_name;}
    const vector<Transaction>& getHistory() const {return history;}
private:
    string acc_name;
    int acc4_num;
    int balance = 0;
    vector<Transaction> history;
};
ostream& operator <<(ostream& os, const Acct4::Transaction& transact){
    os  << "\t" << transact.getAction() <<  ' ' << transact.getAmount();
    return os;
}
ostream& operator <<(ostream& os, const Acct4& account4){
    os << account4.getName() << ' ' << account4.getacc4_num() << ":\n";
    for (const Acct4::Transaction& some_entry : account4.getHistory()){
        os << some_entry << '\n';
    }
    return os;
}

// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.
class Acct3{
    friend ostream& operator <<(ostream& os, const Acct3& account3);
    class Transaction {
        friend ostream& operator<<(ostream& os, const Transaction& transact);
    public:
        Transaction(const string& input_action, int money) : action_type(input_action) {
            amount = money;
        }
    private:
        string action_type; // "Deposit" or "Withdrawal"
        int amount;
    };
    friend ostream& operator<<(ostream& os, const Acct3::Transaction& transact);
public:
    Acct3(const string& input_name, int account_num) : acc_name(input_name) {
        acc3_num = account_num;
    }
    void deposit(int money){
        Transaction entry("deposit", money);
        history.emplace_back(entry);
        balance += money;
    }
    void withdraw(int money){
        if (balance < money){
            cout << "Account# " << acc3_num << " has only " << balance <<
                 ". Insufficient for withdrawal of " << money << ".\n";
        } else {
            Transaction entry("withdrawal", money);
            history.emplace_back(entry);
            balance -= money;
        }
    }
    int getacc3_num()  const {return acc3_num;}
    const string& getName() const {return acc_name;}
    const vector<Transaction>& getHistory() const {return history;}
private:
    string acc_name;
    int acc3_num;
    int balance = 0;
    vector<Transaction> history;
};
ostream& operator<<(ostream& os, const Acct3::Transaction& transact) {
    os << "\t" << transact.action_type << ' ' << transact.amount;
    return os;
}
ostream& operator <<(ostream& os, const Acct3& account3){
    os << account3.acc_name << ' ' << account3.acc3_num << ":\n";
    for (const Acct3::Transaction& some_entry : account3.history){
        os << some_entry << '\n';
    }
    return os;
}

int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";

    // try to open the file
    ifstream acctFile("accounts.txt");
    if (!acctFile){
        cerr << "Can't open file" << endl;
        return 1;
    }
    // read file and fill in a vector of account objects
    string acctName;
    int acctNum = 0;
    vector<Account> accounts;
    while (acctFile >> acctName >> acctNum){
        Account newAcct;
        newAcct.name = acctName;
        newAcct.number = acctNum;
        accounts.push_back(newAcct);
    }
    acctFile.close();
    // display all the objects (does it have to be aligned?)
    for (const Account& someAcct : accounts){
        cout << "Account: " << someAcct.name << "   Number: " << someAcct.number << endl;
    }

    //      1b
    cout << "\nTask1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";

    // clear the vector and reopen file
    accounts.clear();
    acctFile.open("accounts.txt");
    if (!acctFile){
        cerr << "Can't open file" << endl;
        return 1;
    }
    // same as 1a, but use curly braces for parameterized initialization
    while (acctFile >> acctName >> acctNum){
        Account newAcct{acctName, acctNum};
        accounts.push_back(newAcct);
    }
    acctFile.close();
    // same as 1a: display all the objects (does it have to be aligned?) (Do I need to clear?)
    for (const Account& someAcct : accounts){
        cout << "Account: " << someAcct.name << "   Number: " << someAcct.number << endl;
    }

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
    accounts.clear();
    // open file
    acctFile.open("accounts.txt");
    if (!acctFile){
        cerr << "Can't open file" << endl;
        return 1;
    }
    // fill in vector
    vector<Acct> accts;

    while (acctFile >> acctName >> acctNum){
        Acct some_acct(acctName,acctNum);
        accts.push_back(some_acct);
    }
    acctFile.close();
    //print out
    for (const Acct& this_acct : accts){
        cout << "Account: " << this_acct.getName() << "   Number: " << this_acct.getNum() << endl;
    }

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for (const Acct& this_acct : accts){
        cout << this_acct << endl;
    }

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
    for (const Acct& this_acct : accts){
        cout << this_acct << endl;
    }

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
    accts.clear();
    // open file
    acctFile.open("accounts.txt");
    if (!acctFile){
        cerr << "Can't open file" << endl;
        return 1;
    }
    while (acctFile >> acctName >> acctNum){
        accts.push_back(Acct(acctName, acctNum));
    }

    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
    accts.clear();
    while (acctFile >> acctName >> acctNum){
        accts.emplace_back(acctName, acctNum);
    }
    acctFile.close();
    
    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";
    ifstream transactFile;
    transactFile.open("transactions.txt");
    if (!transactFile){
        cerr << "Could not open file" << endl;
        return 1;
    }
    vector<Acct2> all_accts;
    string keyword;
    int acct_num, money;
    // read the first token, decide on action
    while (transactFile >> keyword){
        if (keyword == "Account"){
            string name;
            transactFile >> name >> acct_num;
            all_accts.emplace_back(name, acct_num);
        } else if (keyword == "Deposit"){
            transactFile >> acct_num >> money;
            for (Acct2& account : all_accts){
                if (account.getacc2_num() == acct_num){
                    account.deposit(money);
                    break;
                }
            }
        } else if (keyword == "Withdraw"){
            transactFile >> acct_num >> money;
            for (Acct2& account : all_accts){
                if (account.getacc2_num() == acct_num){
                    account.withdraw(money);
                    break;
                }
            }
        }
    }
    transactFile.close();
    for (const Acct2& account : all_accts){
        cout << account;
    }

    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
    transactFile.open("transactions.txt");
    if (!transactFile) {
        cerr << "Could not open file" << endl;
        return 1;
    }
    vector<Acct4> all_acct4;
    string command1;
    int accNum4, amount4;
    // read the first token, decide on action
    while (transactFile >> command1){
        if (command1 == "Account"){
            string acc4Name;
            transactFile >> acc4Name >> accNum4;
            all_acct4.emplace_back(acc4Name, accNum4);
        } else if (command1 == "Deposit"){
            transactFile >> accNum4 >> amount4;
            for (Acct4& account : all_acct4){
                if (account.getacc4_num() == accNum4){
                    account.deposit(amount4);
                    break;
                }
            }
        } else if (command1 == "Withdraw"){
            transactFile >> accNum4 >> amount4;
            for (Acct4& account : all_acct4){
                if (account.getacc4_num() == accNum4){
                    account.withdraw(amount4);
                    break;
                }
            }
        }
    }
    transactFile.close();
    for (const Acct4& account : all_acct4){
        cout << account;
    }
    
    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";
    transactFile.open("transactions.txt");
    if (!transactFile) {
        cerr << "Could not open file" << endl;
        return 1;
    }
    vector<Acct3> all_acct3;
    string command;
    int accountNum, amount;
    // read the first token, decide on action
    while (transactFile >> command){
        if (command == "Account"){
            string acc3Name;
            transactFile >> acc3Name >> accountNum;
            all_acct3.emplace_back(acc3Name, accountNum);
        } else if (command == "Deposit"){
            transactFile >> accountNum >> amount;
            for (Acct3& account : all_acct3){
                if (account.getacc3_num() == accountNum){
                    account.deposit(amount);
                    break;
                }
            }
        } else if (command == "Withdraw"){
            transactFile >> accountNum >> amount;
            for (Acct3& account : all_acct3){
                if (account.getacc3_num() == accountNum){
                    account.withdraw(amount);
                    break;
                }
            }
        }
    }
    transactFile.close();
    for (const Acct3& account : all_acct3){
        cout << account;
    }
    
}
