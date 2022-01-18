#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <iterator>
#include "SortedStudent.h"

SortedStudent::SortedStudent() = default;

SortedStudent::SortedStudent(const SortedStudent &student) {
    setName(student.name);
    setSurname(student.surname);
    setHomeworksMark(student.homeworksMark);
    setExamMark(student.examMark);
}

void SortedStudent::setName(string name) {
    this->name = name;
}

void SortedStudent::setSurname(string surname) {
    this->surname = surname;
}

void SortedStudent::setHomeworksMark(vector<double> homeworksMark) {
    this->homeworksMark = homeworksMark;
}

void SortedStudent::setExamMark(double examMark) {
    this->examMark = examMark;
}

SortedStudent::~SortedStudent() {
    this->setName("");
    this->setSurname("");
    this->setHomeworksMark({});
    this->setExamMark(0);
}

void SortedStudent::handleInput() {
    int homeworksNumber;

    string inputName;
    string inputSurname;
    vector<double> inputHomeworksMark;
    double inputExamMark = 0.0;
    bool areResultsRandom = false;
    int inputValue = 0;

    cout << NAME_LT << endl;
    cin >> inputName;

    cout << SURNAME_LT << endl;
    cin >> inputSurname;

    cout << RANDOM_MARKS_RESULT << endl;
    cin >> inputValue;

    if (inputValue)
        areResultsRandom = true;

    if (areResultsRandom) {
        random_device rd;   // non-deterministic generator
        mt19937 gen(rd());  // to seed mersenne twister.
        uniform_int_distribution<> generatedHomeworksNumber(1,5);
        uniform_int_distribution<> generatedMark(1,10);

        homeworksNumber = generatedHomeworksNumber(gen);

        for (int i = 0; i < homeworksNumber; i++) {
            inputHomeworksMark.push_back(generatedMark(gen));
        }

        inputExamMark = generatedMark(gen);
    }
    else {
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
    }

    setName(inputName);
    setSurname(inputSurname);
    setHomeworksMark(inputHomeworksMark);
    setExamMark(inputExamMark);

    writeFile();

    printData();
}

void SortedStudent::printData() {
    const bool isMeanResult = isCalculatedByMean();

    const double finalMark = calculateFinalMark(homeworksMark, examMark, isMeanResult);

    cout << SURNAME_LT << " " << NAME_LT << " ";
    cout << (isMeanResult == 1 ? RESULT_MARK_MEAN_LT : RESULT_MARK_MEDIAN_LT) << endl;
    cout << name << " " << surname << " " << finalMark << endl;
}

void SortedStudent::createFile() {
    string fileName = DEFAULT_FILE_NAME;
    int inputValue = 0;

    cout << CREATE_FILE_QUESTION << endl;
    cin >> inputValue;

    if (inputValue != 1)
        return;

    cout << TYPE_FILE_NAME << endl;
    cin >> fileName;

    ofstream fileOut;

    fileOut.open(fileName, ios_base::in);

    if (fileOut)
        return;

    fileOut.open(fileName, ios_base::app);

    fileOut << "Pavarde Vardas ND1 ND2 ND3 ND4 ND5 ND6 ND7 ND8 ND9 ND10 Egzaminas" << endl;
}

void SortedStudent::writeFile() {
    ofstream fileOut;

    fileOut.open(DEFAULT_FILE_NAME, ios_base::app);

    fileOut << surname << " " << name << " ";

    for (double mark: homeworksMark)
        fileOut << mark << " ";

    const int length = (int) homeworksMark.size();

    for (int i = 0; i < 5 - length; i++)
        fileOut << 0 << " ";

    fileOut << examMark << endl;
}

void SortedStudent::readFile() {
    vector<vector<string>> modifiedVector;

    ifstream fileIn(DEFAULT_FILE_NAME);

    if (!fileIn.is_open())
        return;

    const bool isMeanResult = isCalculatedByMean();

    string inputData = string((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());

    vector<vector<string>> arrayVector = splitString(inputData);

    for (const vector sVector: arrayVector) {
        vector<double> homeworkMarksVector;
        vector<string> outputVector;

        homeworkMarksVector.resize(0);
        outputVector.resize(0);

        const int vectorLength = sVector.size();

        for (int i = 2; i < vectorLength - 1; i++) {
            if (sVector[0] == SURNAME_LT)
                break;

            double mark = std::stod(sVector[i]);

            if (mark < 0)
                continue;

            homeworkMarksVector.push_back(mark);
        }

        outputVector.push_back(sVector[0]);
        outputVector.push_back(sVector[1]);

        if (sVector[0] == SURNAME_LT) {
            outputVector.push_back(isMeanResult ? RESULT_MARK_MEAN_LT : RESULT_MARK_MEDIAN_LT);
        }
        else {
            double extractedExamMark = stod(sVector[vectorLength - 1]);
            double finalMark = calculateFinalMark(homeworkMarksVector, extractedExamMark, isMeanResult);
            string stringFinalMark = to_string(finalMark);

            outputVector.push_back(stringFinalMark);
        }

        modifiedVector.push_back(outputVector);
    }

    sort(modifiedVector.begin(), modifiedVector.end(),
         [](const vector<string>& a, const vector<string>& b) {
             string surnameA = a[0];
             string surnameB = b[0];

             if (surnameA == SURNAME_LT)
                 return surnameA < surnameB;
             else if (surnameB == SURNAME_LT)
                 return surnameB < surnameA;

             return surnameA < surnameB;
         });

    for (const vector sVector: modifiedVector) {
        for (const string& dataString: sVector) {
            string stringMixin;
            const int mixinLength = STRING_MIXIN_SIZE - (int) dataString.size();

            for (int i = 0; i < mixinLength; i++)
                stringMixin += " ";

            const string printString = dataString + stringMixin;

            cout << printString << " ";
        }

        cout << endl;
    }
}

vector<vector<string>> SortedStudent::splitString(const string& s, const string& separator) {
    size_t start = 0;
    size_t end = s.find(separator);

    vector<string> stringVector;
    vector<vector<string>> arrayVector;

    while (end != string::npos) {
        const string word = s.substr(start, end - start);

        const size_t wordLineBreakEnd = word.find('\n');

        if (wordLineBreakEnd == string::npos) {
            start = end + separator.size();
            end = s.find(separator, start) != string::npos
                  ? s.find(separator, start)
                  : s.size();

            stringVector.push_back(word);
        }
        else {
            const size_t lineBreakStart = start;
            const size_t lineBreakEnd = s.find('\n', start);

            const string wordBeforeLineBreak = s.substr(lineBreakStart, lineBreakEnd - lineBreakStart);

            start = lineBreakEnd + 1;
            end = s.find(separator, start);

            stringVector.push_back(wordBeforeLineBreak);

            arrayVector.push_back(stringVector);

            stringVector.resize(0);
        }
    }

    return arrayVector;
}

void SortedStudent::handleInputState() {
    bool isAddingData = false;
    int inputValue;

    cout << IS_ADDING_DATA << endl;
    cin >> inputValue;

    if (inputValue)
        isAddingData = true;

    if (isAddingData)
        handleInput();
    else
        readFile();
}

double SortedStudent::calculateFinalMark(vector<double> homeworkMarksVector, double ExamMarkVar, bool isCalculatedByMean) {
    double homeworksMarkResult = 0;

    if (isCalculatedByMean) {
        for (double mark: homeworkMarksVector)
            homeworksMarkResult += mark;

        homeworksMarkResult /= (double) homeworkMarksVector.size();
    }
    else {
        int arrayLength = (int) homeworkMarksVector.size();

        if (arrayLength % 2 == 1) {
            int position = (arrayLength + 1) / 2;

            homeworksMarkResult = homeworkMarksVector[position];
        }
        else {
            int position = arrayLength / 2;

            homeworksMarkResult = (homeworkMarksVector[position] + homeworkMarksVector[position + 1]) / 2;
        }
    }

    return 0.4 * homeworksMarkResult + 0.6 * ExamMarkVar;
}

bool SortedStudent::isCalculatedByMean() {
    bool isCalculatedByMean = false;
    int inputValue;

    cout << HOMEWORK_COUNT_QUESTION << endl;
    cout << HOMEWORK_COUNT_ANSWER << endl;
    cin  >> inputValue;

    if (inputValue == 1)
        isCalculatedByMean = true;

    return isCalculatedByMean;
}

void SortedStudent::fillFileWithRandomData() {
    string fileName = DEFAULT_FILE_NAME;
    int cycleNumber;

    cout << TYPE_FILE_NAME << endl;
    cin >> fileName;

    cout << CYCLE_NUMBER_QUESTION << endl;
    cin >> cycleNumber;

    vector<string> nameArray = {"Harry","Ross",
                                 "Bruce","Cook",
                                 "Carolyn","Morgan",
                                 "Albert","Walker",
                                 "Randy","Reed",
                                 "Larry","Barnes",
                                 "Lois","Wilson",
                                 "Jesse","Campbell",
                                 "Ernest","Rogers",
                                 "Theresa","Patterson",
                                 "Henry","Simmons",
                                 "Michelle","Perry",
                                 "Frank","Butler",
                                 "Shirley", "Brooks",
                                  "Rachel","Edwards",
                                  "Christopher","Perez",
                                  "Thomas","Baker",
                                  "Sara","Moore",
                                  "Chris","Bailey",
                                  "Roger","Johnson",
                                  "Marilyn","Thompson",
                                  "Anthony","Evans",
                                  "Julie","Hall",
                                  "Paula","Phillips",
                                  "Annie","Hernandez",
                                  "Dorothy","Murphy",
                                  "Alice","Howard"};

    vector<string> surnameArray = {
            "Ruth","Jackson", "Debra","Allen",
            "Gerald","Harris", "Raymond","Carter",
            "Jacqueline","Torres", "Joseph","Nelson",
                                "Carlos","Sanchez",
                                "Ralph","Clark",
                                "Jean","Alexander",
                                "Stephen","Roberts",
                                "Eric","Long",
                                "Amanda","Scott",
                                "Teresa","Diaz",
                                "Wanda","Thomas"
    };

    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.

    ofstream fileOut;

    fileOut.open(fileName, ios_base::app);

    cout << cycleNumber << endl;

    for (int i = 0; i < cycleNumber; i++) {
        string outputData;
        vector<string> dataVector;

        dataVector.resize(0);

        uniform_int_distribution<int> generatedHomeworksNumber(1, 10);
        uniform_int_distribution<int> generatedMark(1, 10);
        uniform_int_distribution<int> generatedNameKey(0, (int) nameArray.size());
        uniform_int_distribution<int> generatedSurnameKey(0, (int) surnameArray.size());

        dataVector.push_back(nameArray[generatedNameKey(gen)]);
        dataVector.push_back(surnameArray[generatedSurnameKey(gen)]);

        int homeworksNumber = generatedHomeworksNumber(gen);

        for (int j = 0; j < homeworksNumber; j++) {
            const string mark = to_string(generatedMark(gen));

            dataVector.push_back(mark);
        }

        for (int j = 0; j < 10 - homeworksNumber; j++)
            dataVector.emplace_back("-1");

        const string examMarkVar = to_string(generatedMark(gen));
        dataVector.push_back(examMarkVar);

        for (const string &s: dataVector) {
            outputData += s;
            outputData += " ";
        }

        fileOut << outputData << endl;
    }

    fileOut.close();
}

void SortedStudent::exportSortedData() {
    vector<vector<string>> modifiedVector;
    string fileName = DEFAULT_FILE_NAME;

    cout << TYPE_FILE_NAME << endl;
    cin >> fileName;

    ifstream fileIn(fileName);

    if (!fileIn.is_open())
        return;

    const bool isMeanResult = isCalculatedByMean();

    string inputData = string((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());

    fileIn.close();

    vector<vector<string>> arrayVector = splitString(inputData);

    for (const vector sVector: arrayVector) {
        if (sVector[0] == SURNAME_LT)
            continue;

        vector<double> homeworkMarksVector;
        vector<string> outputVector;

        homeworkMarksVector.resize(0);
        outputVector.resize(0);

        const int vectorLength = (int) sVector.size();

        for (int i = 2; i < vectorLength - 1; i++) {
            if (sVector[0] == SURNAME_LT)
                break;

            double mark = std::stod(sVector[i]);

            if (mark < 0)
                continue;

            homeworkMarksVector.push_back(mark);
        }

        outputVector.push_back(sVector[0]);
        outputVector.push_back(sVector[1]);

        //2 instead of 1 due to existing empty space after last item
        double extractedExamMark = stod(sVector[vectorLength - 2]);
        double finalMark = calculateFinalMark(homeworkMarksVector, extractedExamMark, isMeanResult);
        string stringFinalMark = to_string(finalMark);

        outputVector.push_back(stringFinalMark);

        modifiedVector.push_back(outputVector);
    }

    sort(modifiedVector.begin(), modifiedVector.end(),
         [](const vector<string>& a, const vector<string>& b) {
             string finalMarkA = a[2];
             string finalMarkB = b[2];

             return finalMarkA > finalMarkB;
         });

    vector<vector<string>> passedStudentsVector;
    vector<vector<string>> failedStudentsVector;

    for (const vector sVector: modifiedVector) {
        const double mark = stod(sVector[2]);

        vector<string> passedStudentsV;
        vector<string> failedStudentsV;

        passedStudentsV.resize(0);
        failedStudentsV.resize(0);

        if (mark > 5) {
            passedStudentsV.push_back(sVector[0]);
            passedStudentsV.push_back(sVector[1]);
            passedStudentsV.push_back(sVector[2]);

            passedStudentsVector.push_back(passedStudentsV);
        }
        else {
            failedStudentsV.push_back(sVector[0]);
            failedStudentsV.push_back(sVector[1]);
            failedStudentsV.push_back(sVector[2]);

            failedStudentsVector.push_back(failedStudentsV);
        }
    }

    vector<string> headVector;

    headVector.push_back(arrayVector[0][0]);
    headVector.push_back(arrayVector[0][1]);
    headVector.push_back(isMeanResult ? RESULT_MARK_MEAN_LT : RESULT_MARK_MEDIAN_LT);

    modifiedVector.insert(modifiedVector.begin(), headVector);
    passedStudentsVector.insert(passedStudentsVector.begin(), headVector);
    failedStudentsVector.insert(failedStudentsVector.begin(), headVector);

    ofstream fileOutPassedStudents;
    ofstream fileOutFailedStudents;

    fileOutPassedStudents.open(fileName + "_passed_students", ios_base::app);

    for (vector<string> outputV: passedStudentsVector) {
        string outputString;

        for (const string s: outputV) {
            outputString += s;
            outputString += " ";
        }

        fileOutPassedStudents << outputString << endl;
    }

    fileOutPassedStudents.close();

    fileOutFailedStudents.open(fileName + "_failed_students", ios_base::app);

    for (vector<string> outputV: failedStudentsVector) {
        string outputString;

        for (const string s: outputV) {
            outputString += s;
            outputString += " ";
        }

        fileOutFailedStudents << outputString << endl;
    }

    fileOutFailedStudents.close();
}
