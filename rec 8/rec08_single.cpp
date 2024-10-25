/*
 * Joy Wang

  rec08_starter.cpp
  Starter Code for required functionality

  Yes, of course, you may add other methods.

  And no, this won't compile. You have to fix the cyclic association
  and implement the methods.
  
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* course);

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course* course);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string& course);
    // Creates a new student, if none with that name
    bool addStudent(const string& course);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string& student) const;
    size_t findCourse(const string& course) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main()
{

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main

// Course

// output operator
ostream &operator<<(ostream &os, const Course& course) {
    os << course.name << ": ";
    if (course.students.size() == 0){
        os << "No Students";
    } else {
        for (const Student* student : course.students){
            os << " " << student->getName();
        }
    }
    os << endl;
    return os;
}

// Course constructor
Course::Course(const string &courseName) : name(courseName) {
}

// getName() definition
const string &Course::getName() const {
    return name;
}

// addStudent() definition
bool Course::addStudent(Student* student) {
    for (const Student* person : students){
        if (person == student) return false;
    }
    students.push_back(student);
    return true;
}

// removeStudentsFromCourse() definition
void Course::removeStudentsFromCourse() {
    for (Student* student : students){
        student->removedFromCourse(this);
    }
    // this gets rid of all of them
    students.clear();
}

// Student

ostream &operator<<(ostream &os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.empty()){
        os << "No Courses";
    } else {
        for (const Course* course : rhs.courses){
            os << " " << course->getName();
        }
    }
    os << endl;
    return os;
}

// constructor
Student::Student(const string& name) : name(name) {
}

// getName() def in student
const string &Student::getName() const {
    return name;
}

// addCourse() definition
bool Student::addCourse(Course* theCourse) {
    // check for repeats
    for (const Course* course : courses){
        if (course->getName() == theCourse->getName()){
            return false;
        }
    }
    courses.push_back(theCourse);
    return true;
}

// removedFromCourse() in Student class
void Student::removedFromCourse(Course* course) {
    for (size_t i=0; i<courses.size(); i++){
        if (courses[i] == course){
            // order does actually matter when removing
            // swap(courses[i], courses.back());
            for (size_t j=i; j<courses.size()-1; j++){
                courses[j] = courses[j+1];
            }
            courses.pop_back();
            break;
        }
    }
}

// Registrar

ostream &operator<<(ostream &os, const Registrar& rhs) {
    os << "Registrar's Report" << endl;
    os << "Courses:" << endl;
    for (const Course* course : rhs.courses){
        if (course != nullptr){
            os << *course;
        }
    }
    os << "Students:" << endl;
    for (const Student* student : rhs.students){
        if (student != nullptr){
            os << *student;
        }
    }
    return os;
}

// default constructor
Registrar::Registrar() {}   // says to use default

// addCourse() for registrar
bool Registrar::addCourse(const string& courseName) {
    // check if the name is unique
    for (const Course* course : courses){
        if (course->getName() == courseName){
            return false;
        }
    }
    // create a new course
    if (findCourse(courseName) == courses.size()){
        courses.push_back(new Course(courseName));
        return true;
    }
    return false;
}

// addStudent() for registrar
bool Registrar::addStudent(const string& student) {
    if (findStudent(student) == students.size()) {
        students.push_back(new Student(student));
        return true;
    }
    return false;
}

// enrollStudentInCourse() definition
bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
    size_t student_i = findStudent(studentName);
    size_t course_i = findCourse(courseName);
    // check if student exists and course exists
    if (student_i < students.size() && course_i < courses.size()) {
        return courses[course_i]->addStudent(students[student_i]) &&
        students[student_i]->addCourse(courses[course_i]);
    }
    return false;
}

// cancelCourse() definition
bool Registrar::cancelCourse(const string &courseName) {
    size_t course_i = findCourse(courseName);
    if (course_i < courses.size()) {
        courses[course_i]->removeStudentsFromCourse();
        delete courses[course_i];
        // does order still matter here?
        // courses[course_i] = courses[courses.size() - 1];
        for (size_t i = course_i; i < courses.size()-1; i++){
            courses[i] = courses[i+1];
        }
        courses.pop_back();
        return true;
    }
    return false;
}

// purge() definition
void Registrar::purge() {
    for (Student* student : students){
        delete student;
    }
    students.clear();
    for (Course* course : courses){
        delete course;
    }
    courses.clear();
}

// private in registrar class
size_t Registrar::findStudent(const string& student) const {
    // returns the index of student in vector
    for (size_t i=0; i<students.size(); i++){
        if (students[i]->getName() == student){
            return i;
        }
    }
    return students.size();
}

// private in registrar class
size_t Registrar::findCourse(const string& course) const {
    // returns the index of course in vector
    for (size_t i=0; i<courses.size(); i++){
        if (courses[i]->getName() == course){
            return i;
        }
    }
    return courses.size();
}
