#include <array>
#include <iostream>
#include <string>

// I don't like to use `using namespace`. It help me read the code better and see where all the methods are comming from.

// Use global constants to avoid errors.
// And if you want to change it later you change the value once throughout your code base
constexpr std::size_t QUIZZES_COUNT = 2;

/*
 * Try to consolidate all your struct. You were having a struct named Student with fields
 * that can be included in a student record. Hence the elmination.
*/

class StudentRecord {
public:
    std::string name;
    char finalLetterGrade;

private:
    // Try to use standard containers where posible
    std::array<double, QUIZZES_COUNT> quiz;
    double midterm, finalExam;
    double finalGrade;

public:
    void inputQuizzes();
    void inputMidtermGrade();
    void inputFinalGrade();

    double* getQuizzes();
    double getMidterm();
    double getFinalExam();

    // If a method doesn't access a field of the class, that method could be static.
    static double calcPercent(double grade, double outOfTotalPts, double percentOfTotal);
    static char calcFinalLetterGrade(double finalGrade);

    // Since this method are only setters there is no need for them to return the value
    void setFinalNumericGrade(double newFinalGrade);
    void setFinalLetterGrade(char newFinalLetterGrade);
};

double* StudentRecord::getQuizzes() {
    /*
        C style arrays are basically pointer to memory too. So you could have done something like this

            double data[2];
            return data;

        This would have returned a pointer of data. Without the necesity to create an extra variable
    */
    return quiz.data();
}

double StudentRecord::getMidterm() { return midterm; }
double StudentRecord::getFinalExam() { return finalExam; }

double StudentRecord::calcPercent(double grade, double outOfTotalPts, double percentOfTotal) {
    return (grade / outOfTotalPts) * percentOfTotal;
}

void StudentRecord::setFinalNumericGrade(double newFinalGrade) {
    // Since this method are only setters there is no need for them to return the value
    finalGrade = newFinalGrade;
}

// This method is static because doesn't access any of the member of StudentRecord
char StudentRecord::calcFinalLetterGrade(double finalGrade) {
    if (finalGrade >= 90.0)
        return 'A';
    // You don't need to prove `finalGrade < 90` since it would automatically be qualified for the above if clause.
    else if (finalGrade >= 80.0) 
        return 'B';
    else if (finalGrade >= 70.0)
        return 'C';
    else if (finalGrade >= 60.0)
        return 'D';
    else
        return 'F';
}

void StudentRecord::setFinalLetterGrade(char newFinalLetterGrade) {
    // Since this method are only setters there is no need for them to return the value
    finalLetterGrade = newFinalLetterGrade;
}

void StudentRecord::inputQuizzes() {
    // This method is unnecessary since they are only called once. Their code could be putted where they are called
    std::cout << "Enter quiz grades : ";
    for (int i = 0; i < QUIZZES_COUNT; i++) {
        std::cin >> quiz[i];
    }
}

void StudentRecord::inputMidtermGrade() {
    // This method is unnecessary since they are only called once. Their code could be putted where they are called
    std::cout << "Enter midterm grade : ";
    std::cin >> midterm;
}

void StudentRecord::inputFinalGrade() {
    // This methods is unnecessary since they are only called once. Their code could be putted where they are called
    std::cout << "Enter final grade : ";
    std::cin >> finalExam;
}

int main() {
    StudentRecord student;

    std::cout << "Enter name : ";
    std::cin >> student.name;

    student.inputQuizzes();
    student.inputMidtermGrade();
    student.inputFinalGrade();

    // General iostream tip: Don't use std::endl since it flush the stream buffer. That have performance impact
    // Source: Video by Jason Turner https://www.youtube.com/watch?v=GMqQOEZYVJQ

    double* ptr = student.getQuizzes();
    for (int i = 0; i < QUIZZES_COUNT; i++)
        std::cout << "Quiz " << i + 1 << ": " << ptr[i] << '\n';


    std::cout << "Midterm : " << student.getMidterm() << '\n';

    std::cout << "Final Exam : " << student.getFinalExam() << '\n';

    // calculations //

    double quizSum = 0.0;
    for (int i = 0; i < QUIZZES_COUNT; i++)
        quizSum += ptr[i];

    // All of this "random" numbers (20.0, 25.0, 50.0, 100.0) can be made into constant to make the code reader aware of their significance
    double quizPercent = StudentRecord::calcPercent(quizSum, 20.0, 25.0);
    double midtermPercent = StudentRecord::calcPercent(student.getMidterm(), 100.0, 25.0);
    double finalPercent = StudentRecord::calcPercent(student.getFinalExam(), 100.0, 50.0);

    double finalNumGrade = quizPercent + midtermPercent + finalPercent;

    student.setFinalNumericGrade(finalNumGrade);

    char letterGrade = StudentRecord::calcFinalLetterGrade(finalNumGrade);

    student.setFinalLetterGrade(letterGrade);

    std::cout << "Name : " << student.name << '\n';
    std::cout << "Final Grade : " << student.finalLetterGrade << '\n';

    return 0;
}
