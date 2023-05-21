#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "grading_system.h"

void addStudent(Student* students, int& numStudents);
void addCourse(Course* courses, int& numCourses);
void addAssessment(Assessment* assessments, int& numAssessments);
void inputAssessments(Course* course);
void displayStudentInfo(const Student& student);
void displayOverallInfo(const Student* students, int numStudents);

int main() {
    int numStudents = 0;
    std::cout << "Enter the number of students: ";
    std::cin >> numStudents;

    std::cin.ignore(); // Ignore the newline character

    Student* students = new Student[numStudents];

    for (int i = 0; i < numStudents; ++i) {
        addStudent(students, numStudents);

        int numCourses = 0;
        std::cout << "Enter the number of courses for " << students[i].name << ": ";
        std::cin >> numCourses;

        std::cin.ignore(); // Ignore the newline character

        Course* courses = new Course[numCourses];

        for (int j = 0; j < numCourses; ++j) {
            addCourse(courses, numCourses);
            inputAssessments(&courses[j]);
        }

        students[i].courses = std::vector<Course>(courses, courses + numCourses);

        delete[] courses;
    }

    displayOverallInfo(students, numStudents);

    // Clean up dynamically allocated memory
    delete[] students;

    return 0;
}

void addStudent(Student* students, int& numStudents) {
    std::cout << "Enter the name of student " << numStudents + 1 << ": ";
    std::getline(std::cin, students[numStudents].name);

    ++numStudents;
}

void addCourse(Course* courses, int& numCourses) {
    std::cout << "Enter the name of the course: ";
    std::getline(std::cin, courses[numCourses].name);

    ++numCourses;
}

void addAssessment(Assessment* assessments, int& numAssessments) {
    std::cout << "Enter the name of the assessment: ";
    std::getline(std::cin, assessments[numAssessments].name);

    std::cout << "Enter the score for the assessment (out of 100): ";
    std::cin >> assessments[numAssessments].score;

    std::cout << "Enter the weight of the assessment (in credits): ";
    std::cin >> assessments[numAssessments].weight;

    std::cin.ignore(); // Ignore the newline character

    ++numAssessments;
}

void inputAssessments(Course* course) {
    int numAssessments = 0;
    std::cout << "Enter the number of assessments for " << course->name << ": ";
    std::cin >> numAssessments;

    std::cin.ignore(); // Ignore the newline character

    Assessment* assessments = new Assessment[numAssessments];

    for (int i = 0; i < numAssessments; ++i) {
        addAssessment(assessments, numAssessments);
    }

    course->assessments = std::vector<Assessment>(assessments, assessments + numAssessments);

    delete[] assessments;
}

void displayStudentInfo(const Student& student) {
    std::cout << "Student Name: " << student.name << std::endl;

    for (const Course& course : student.courses) {
        std::cout << "Course: " << course.name << std::endl;
        std::cout << "Assessments:" << std::endl;

        for (const Assessment& assessment : course.assessments) {
            std::cout << "  - " << assessment.name << ": " << assessment.score << " / " << assessment.weight << std::endl;
        }
    }

    double cgpa = calculateCGPA(student);
    std::cout << "CGPA: " << std::fixed << std::setprecision(2) << cgpa << std::endl;
    std::cout << "Letter Grade: " << getLetterGrade(cgpa) << std::endl;
    std::cout << std::endl;
}

void displayOverallInfo(const Student* students, int numStudents) {
    std::cout << "---------- Overall Information ----------" << std::endl;

    for (int i = 0; i < numStudents; ++i) {
        displayStudentInfo(students[i]);
    }

    double totalCGPA = 0.0;
    double totalLetterGrade = 0.0;

    for (int i = 0; i < numStudents; ++i) {
        double cgpa = calculateCGPA(students[i]);
        totalCGPA += cgpa;
        totalLetterGrade += static_cast<int>(getLetterGrade(cgpa)[0]);
    }

    double averageCGPA = totalCGPA / numStudents;
    char averageLetterGrade = static_cast<char>(totalLetterGrade / numStudents);

    std::cout << "Average CGPA: " << std::fixed << std::setprecision(2) << averageCGPA << std::endl;
    std::cout << "Average Letter Grade: " << averageLetterGrade << std::endl;
}
