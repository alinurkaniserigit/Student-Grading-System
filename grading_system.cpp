#include "grading_system.h"

double calculateCGPA(const Student& student) {
    double totalGradePoints = 0.0;
    double totalCredits = 0.0;

    for (const Course& course : student.courses) {
        double courseGradePoints = 0.0;
        double courseCredits = 0.0;

        for (const Assessment& assessment : course.assessments) {
            double assessmentGradePoints = (assessment.score / 100.0) * assessment.weight;
            courseGradePoints += assessmentGradePoints;
            courseCredits += assessment.weight;
        }

        if (courseCredits > 0.0) {
            totalGradePoints += (courseGradePoints / courseCredits) * courseCredits;
            totalCredits += courseCredits;
        }
    }

    if (totalCredits == 0.0) {
        return 0.0;
    }

    return totalGradePoints / totalCredits;
}

std::string getLetterGrade(double cgpa) {
    if (cgpa >= 4.0) {
        return "A";
    } else if (cgpa >= 3.0) {
        return "B";
    } else if (cgpa >= 2.0) {
        return "C";
    } else if (cgpa >= 1.0) {
        return "D";
    } else {
        return "F";
    }
}
