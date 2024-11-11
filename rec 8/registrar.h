//
// Created by wangj on 10/25/2024.
//

#ifndef UNTITLED_REGISTRAR_H
#define UNTITLED_REGISTRAR_H

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Course;

    class Student;

    class Registrar {
        friend std::ostream &operator<<(std::ostream &os, const Registrar &rhs);

    public:
        Registrar();

        // Creates a new course, if none with that name
        bool addCourse(const std::string &course);

        // Creates a new student, if none with that name
        bool addStudent(const std::string &course);

        // If the student and the course exist, then enroll the student.
        bool enrollStudentInCourse(const std::string &studentName,
                                   const std::string &courseName);

        // Unenroll the students from the course and remove the course
        // from the Registrar.
        bool cancelCourse(const std::string &courseName);

        // Get rid of everything!!!
        void purge();

    private:
        size_t findStudent(const std::string &student) const;

        size_t findCourse(const std::string &course) const;

        std::vector<Course *> courses;
        std::vector<Student *> students;
    };

}

#endif //UNTITLED_REGISTRAR_H
