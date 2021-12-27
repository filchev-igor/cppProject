
#include <iostream>
#include "Student.h"

Student::Student() = default;

Student::Student(const Student &student) {
    setName(student.name);
    setSurname(student.surname);
    setHomeworksMark(student.homeworksMark);
    setExamMark(student.examMark);
}

void Student::setName(string name) {
    this->name = name;
}

void Student::setSurname(string surname) {
    this->surname = surname;
}

void Student::setHomeworksMark(vector<double> homeworksMark) {
    this->homeworksMark = homeworksMark;
}

void Student::setExamMark(double examMark) {
    this->examMark = examMark;
}

Student::~Student() {
    this->setName("");
    this->setSurname("");
    this->setHomeworksMark({});
    this->setExamMark(0);
}

void Student::handleInput() {
    int homeworksNumber;
    double homeworksMarkResult = 0;

    string inputName;
    string inputSurname;
    vector<double> inputHomeworksMark;
    double inputExamMark = 0.0;

    cout << NAME_LT << endl;
    cin >> inputName;

    cout << SURNAME_LT << endl;
    cin >> inputSurname;

    cout << SEMESTER_HOMEWORK_NUMBER << endl;
    cin >> homeworksNumber;

    for (int i = 0; i < homeworksNumber; i++) {
        double mark;

        cout << i + 1 << " " << HOMEWORK_MARK << endl;
        cin >> mark;

        inputHomeworksMark.push_back(mark);
    }

    cout << EXAM_MARK << endl;
    cin >> inputExamMark;

    setName(inputName);
    setSurname(inputSurname);
    setHomeworksMark(inputHomeworksMark);
    setExamMark(inputExamMark);

    cout << "Call printData method to see the results" << endl;
}

void Student::printData() {
    double homeworksMarkResult = 0;
    int chosenValue;

    cout << "How would you like to count homework marks (mean or median)?";
    cout << " 1 for mean and 2 for median" << endl;
    cin  >> chosenValue;

    if (chosenValue == 1) {
        for (double mark: homeworksMark)
            homeworksMarkResult += mark;

        homeworksMarkResult /= (double) homeworksMark.size();
    }
    else if (chosenValue == 2) {
        int arrayLength = (int) homeworksMark.size();

        if (arrayLength % 2 == 1) {
            int position = (arrayLength + 1) / 2;

            homeworksMarkResult = homeworksMark[position];
        }
        else {
            int position = arrayLength / 2;

            homeworksMarkResult = (homeworksMark[position] + homeworksMark[position + 1]) / 2;
        }
    }

    const double finalMark = 0.4 * homeworksMarkResult + 0.6 * examMark;

    cout << SURNAME_LT << " " << NAME_LT << " ";
    cout << (chosenValue == 1 ? RESULT_MARK_MEAN_LT : RESULT_MARK_MEDIAN_LT) << endl;
    cout << name << " " << surname << " " << finalMark << endl;
}
