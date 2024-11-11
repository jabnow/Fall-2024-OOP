//
// Created by wangj on 10/25/2024.
// Joy Wang


#include <iostream>
#include <string>
#include <vector>

#include "course.h"
#include "student.h"

using namespace std;

namespace BrooklynPoly {
    class Student;

    // Course

    // output operator
    ostream &operator<<(ostream &os, const Course &course) {
        os << course.name << ": ";
        if (course.students.size() == 0) {
            os << "No Students";
        } else {
            for (const Student *student: course.students) {
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
    bool Course::addStudent(Student *student) {
        for (const Student *person: students) {
            if (person == student) return false;
        }
        students.push_back(student);
        return true;
    }

    // removeStudentsFromCourse() definition
    void Course::removeStudentsFromCourse() {
        for (Student *student: students) {
            student->removedFromCourse(this);
        }
        // this gets rid of all of them
        students.clear();
    }

}