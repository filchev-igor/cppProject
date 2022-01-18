
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
const string RANDOM_MARKS_RESULT = "Press 1 to generate random marks. Press anything else to input data manually";
const string HOMEWORK_COUNT_QUESTION = "How would you like to count homework marks (mean or median)?";
const string HOMEWORK_COUNT_ANSWER  = "Press 1 to get results by mean. If something else is pressed, the results will be calculated by median";

const string FILE_NAME = "kursiokai.txt";

const string IS_ADDING_DATA = "Do you want to add data? Press 1 for yes. Press 0 to view data only.";

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

    /*
     * Prints data
     */
    void printData();

    void readFile();

    void createFile();

    /*
     * Asks if user wants to add new data. In other case prints data from file
     */
    void handleInputState();

private:
    void setName(string name);

    void setSurname(string surname);

    void setHomeworksMark(vector<double> homeworksMark);

    void setExamMark(double examMark);

    void writeFile();

    /*
     * Splits string into 2d vector
     */
    vector<vector<string>> splitString(const string& s, const string& separator = " ");

    /*
     * Adds data by the input request. Supports random data adding. Prints new data after adding.
     */
    void handleInput();

    void calculateFinalMark();
};


#endif //CPPPROJECT_STUDENT_H
