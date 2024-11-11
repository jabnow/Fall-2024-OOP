//
// Created by wangj on 10/25/2024.
// Joy Wang

#include <iostream>
#include <string>
#include <vector>

#include "student.h"
#include "course.h"

using namespace std;

// Student

namespace BrooklynPoly {
    ostream &operator<<(ostream &os, const Student &rhs) {
        os << rhs.name << ": ";
        if (rhs.courses.empty()) {
            os << "No Courses";
        } else {
            for (const Course *course: rhs.courses) {
                os << " " << course->getName();
            }
        }
        os << endl;
        return os;
    }

    // constructor
    Student::Student(const string &name) : name(name) {
    }

    // getName() def in student
    const string &Student::getName() const {
        return name;
    }

    // addCourse() definition
    bool Student::addCourse(Course *theCourse) {
        // check for repeats
        for (const Course *course: courses) {
            if (course == theCourse) {
                return false;
            }
        }
        courses.push_back(theCourse);
        return true;
    }

    // removedFromCourse() in Student class
    void Student::removedFromCourse(Course *course) {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i] == course) {
                // order does actually matter when removing
                // swap(courses[i], courses.back());
                for (size_t j = i; j < courses.size() - 1; j++) {
                    courses[j] = courses[j + 1];
                }
                courses.pop_back();
                break;
            }
        }
    }

}