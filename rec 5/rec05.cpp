/*
  rec05-start.cpp
  Created by Joy Wang on 10/4/2024
  Recitation: lab workers management system
  Remember that the file you are to submit should be named rec05.cpp.
  And YOUR NAME should appear up here in the comment.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Section{
    class TimeSlot{
        friend ostream& operator<<(ostream& os, const TimeSlot& time);
    public:
        // constructor
        TimeSlot(const string& weekday, int start) :
        day(weekday), hour(start){}
    private:
        string day;
        int hour;
    };
    class StudentRecord{
        friend ostream& operator<<(ostream& os, const StudentRecord& record);
    public:
        // constructor
        StudentRecord(const string& name, int grade) :
                student_name(name), grades(14,-1){}
        const string& getStudentName() const {return student_name;}
        void setGrade(int grade, int lab){grades[lab-1] = grade;}
        int getGrades(){
            for (int grade : grades){
                cout << grade << " ";
            }
            return -1;
        }
    private:
        string student_name;
        vector<int> grades;
    };
public:
    // constructor
    Section(const string& id, const string& weekday, int start) :
    section(id), slot(weekday, start) {}
    // destructor
    ~Section(){
        cout << "Section" << section << " is being deleted\n";
        for (const StudentRecord* record : spreadsheet){
            cout << "Deleting " << record->getStudentName() << endl;
            delete record;
        }
    }
    // copy constructor
    Section(Section& another): section(another.section), slot(another.slot){
        for (size_t i = 0; i < another.spreadsheet.size(); i++){
            spreadsheet.push_back(new StudentRecord(*another.spreadsheet[i]));
        }
    }
    // friends
    friend ostream& operator<<(ostream& os, const Section::TimeSlot& time);
    friend ostream& operator<<(ostream&os,const Section::StudentRecord&record);
    friend ostream& operator<<(ostream& os, const Section& lab);
    // methods
    int getGrades(){
        for (StudentRecord* file : spreadsheet){
            file->getGrades();
        }
    }
    void addStudent(const string& some_name){
        spreadsheet.push_back(new StudentRecord(some_name, -1));
    }
    void setGrade(const string& name, int grade, int lab){
        for (StudentRecord* file : spreadsheet){
            if (file->getStudentName() == name){
                file->setGrade(grade, lab);
            }
        }
    }
private:
    string section;
    TimeSlot slot;
    vector<StudentRecord*> spreadsheet;
};

class LabWorker{
    friend ostream& operator<<(ostream& os, const LabWorker& some_ta);
public:
    // constructor
    LabWorker(const string& name) : ta_name(name), section(nullptr){}
    // methods
    void addGrade(const string& student, int grade, int week){
        section->setGrade(student, grade, week);
    }
    void addSection(Section& lab){ section = &lab;}
private:
    string ta_name;
    Section* section;
};


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main()
{

    cout << "Test 1: Defining a section\n";
     Section secA2("A2", "Tuesday", 16);
     cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
     secA2.addStudent("John");
     secA2.addStudent("George");
     secA2.addStudent("Paul");
     secA2.addStudent("Ringo");
     cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
     LabWorker moe( "Moe" );
     cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
     moe.addSection( secA2 );
     cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);
     moe.addGrade("Paul", 19, 1);
     moe.addGrade("George", 16, 1);
     moe.addGrade("Ringo", 7, 1);
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);
     moe.addGrade("Paul", 20, 3);
     moe.addGrade("Ringo", 0, 3);
     moe.addGrade("George", 16, 3);
     cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
     doNothing(secA2);
     cout << "Back from doNothing\n\n" << secA2 << endl;

} // main

// overloaded operator for LabWorker
ostream& operator<<(ostream& os, const LabWorker& some_ta){
    if (!some_ta.section){
        // the section can exist before the labworker
        os << some_ta.ta_name << " does not have a section";
    } else {
        os << some_ta.ta_name << " has Section: " << *some_ta.section; // what the, I initialized though
    }
    return os;
}

// overloaded operator for StudentRecord
ostream& operator<<(ostream& os, const Section::StudentRecord& record){
    for (int file : record.grades){
        os << " " << file;
    }
    return os;
}

// overloaded operator for Section
ostream& operator<<(ostream& os, const Section& lab){
    os << "Section: " << lab.section << lab.slot << "Students: ";
    // get all the students and their grades
    if (lab.spreadsheet.size()==0){ // this won't print
        os << "None" << endl;
    }
    for (Section::StudentRecord* record : lab.spreadsheet){
        os << "\nName: " << record->getStudentName() << " Grades: " <<
           record->getGrades();
    }
    os << endl;
    return os;
}

// overloaded operator for TimeSlot
ostream& operator<<(ostream& os, const Section::TimeSlot& time){
    os << ", Time slot: [Day: " << time.day << " Start time: ";
    // convert time to 12 hrs schedule
    if (time.hour > 12){
        os<< time.hour-12 << "pm], ";
    } else {
        os << time.hour << "am], ";
    }
    return os;
}