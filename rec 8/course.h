//
// Created by wangj on 10/25/2024.
// Joy Wang

#ifndef UNTITLED_COURSE_H
#define UNTITLED_COURSE_H

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Student;

    class Course {
        friend std::ostream &operator<<(std::ostream &os, const Course &rhs);

    public:
        // Course methods needed by Registrar
        Course(const std::string &courseName);

        const std::string &getName() const;

        bool addStudent(Student *);

        // Tell the students that they are no longer in the course
        void removeStudentsFromCourse();

    private:
        std::string name;
        std::vector<Student *> students;
    };

}

#endif //UNTITLED_COURSE_H