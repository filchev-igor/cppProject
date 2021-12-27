
#ifndef CPPPROJECT_STUDENT_H
#define CPPPROJECT_STUDENT_H


#include "vector"
#include "string"

using namespace std;

const string NAME_LT = "Vardas";
const string SURNAME_LT = "Pavarde";
const string SEMESTER_HOMEWORK_NUMBER = "Number of homeworks per semester";
const string HOMEWORK_MARK = "homework mark";
const string EXAM_MARK = "exam mark";
const string RESULT_MARK_MEAN_LT = "Galutinis (Vid.)";
const string RESULT_MARK_MEDIAN_LT = "Galutinis (Med.)";


class Student {
private:
    string name;
    string surname;

    vector<double> homeworksMark;
    double examMark;

public:
    Student();

    Student(const Student &student);

    ~Student();

    void handleInput();

    void printData();

private:
    void setName(string name);

    void setSurname(string surname);

    void setHomeworksMark(vector<double> homeworksMark);

    void setExamMark(double examMark);
};


#endif //CPPPROJECT_STUDENT_H
