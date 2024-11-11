//
// Created by wangj on 10/25/2024.
// Joy Wang

#include <iostream>
#include <string>
#include <vector>

#include "registrar.h"
#include "course.h"
#include "student.h"

using namespace std;

// Registrar

namespace BrooklynPoly {
    ostream &operator<<(ostream &os, const Registrar &rhs) {
        os << "Registrar's Report" << endl;
        os << "Courses:" << endl;
        for (const Course *course: rhs.courses) {
            if (course != nullptr) {
                os << *course;
            }
        }
        os << "Students:" << endl;
        for (const Student *student: rhs.students) {
            if (student != nullptr) {
                os << *student;
            }
        }
        return os;
    }

    // default constructor
    Registrar::Registrar() {}   // says to use default

    // addCourse() for registrar
    bool Registrar::addCourse(const string &courseName) {
        // check if the name is unique
        for (const Course *course: courses) {
            if (course->getName() == courseName) {
                return false;
            }
        }
        // create a new course
        if (findCourse(courseName) == courses.size()) {
            courses.push_back(new Course(courseName));
            return true;
        }
        return false;
    }

    // addStudent() for registrar
    bool Registrar::addStudent(const string &student) {
        if (findStudent(student) == students.size()) {
            students.push_back(new Student(student));
            return true;
        }
        return false;
    }

    // enrollStudentInCourse() definition
    bool Registrar::enrollStudentInCourse(const string &studentName, const string &courseName) {
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
            for (size_t i = course_i; i < courses.size() - 1; i++) {
                courses[i] = courses[i + 1];
            }
            courses.pop_back();
            return true;
        }
        return false;
    }

    // purge() definition
    void Registrar::purge() {
        for (Student *student: students) {
            delete student;
        }
        students.clear();
        for (Course *course: courses) {
            delete course;
        }
        courses.clear();
    }

    // private in registrar class
    size_t Registrar::findStudent(const string &student) const {
        // returns the index of student in vector
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i]->getName() == student) {
                return i;
            }
        }
        return students.size();
    }

    // private in registrar class
    size_t Registrar::findCourse(const string &course) const {
        // returns the index of course in vector
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i]->getName() == course) {
                return i;
            }
        }
        return courses.size();
    }

}