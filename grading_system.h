#ifndef GRADING_SYSTEM_H
#define GRADING_SYSTEM_H

#include <string>
#include <vector>

struct Assessment {
    std::string name;
    double score;
    double weight;
};

struct Course {
    std::string name;
    std::vector<Assessment> assessments;
};

struct Student {
    std::string name;
    std::vector<Course> courses;
};

double calculateCGPA(const Student& student);
std::string getLetterGrade(double cgpa);

#endif
