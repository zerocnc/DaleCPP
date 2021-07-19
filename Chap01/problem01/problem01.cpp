#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct StudentRecord
{
    std::string firstName;
    std::string lastName;

    char studentTest[15] = {};
    int scoreCorrect = 0;

    void Calculate(std::string ansKey)
    {

        int countCorrect = 0;

        for (int ndx = 0; ndx < 15; ++ndx)
        {
            if (ansKey[ndx] == studentTest[ndx])
            {
                ++countCorrect;
            }
        }

        scoreCorrect = countCorrect;
    }
};

std::ifstream &operator>>(std::ifstream &fs, StudentRecord &sr)
{
    std::string stuAnswer;
    std::string fName;
    std::string lName;
    char ch;

    fs.read(&sr.studentTest[0], 15);

    fs >> sr.firstName;
    fs >> sr.lastName;

    fs.get(ch); // Reads in the \n charcter.

    return fs;
}

void PressAnyKey()
{
    std::cout << std::endl
              << std::endl;
    std::cout << "Press any key to continue" << std::endl;
    std::cin.get();
}

void ReadFile(std::vector<StudentRecord> &classList, std::string &answerKey, std::ifstream &inFile)
{

    getline(inFile, answerKey);
    //inFile >> answerKey;

    std::cout << "Key is " << answerKey << std::endl;

    while (!inFile.eof())
    {

        StudentRecord tempRec;

        inFile >> tempRec;
        classList.push_back(tempRec);
    }
}

void GradeTest(std::vector<StudentRecord> &classList, const std::string &answerKey)
{

    for (StudentRecord &student : classList)
    {
        student.Calculate(answerKey);
    }
}

void Display(std::vector<StudentRecord> &classList)
{

    for (auto student : classList)
    {
        std::cout << "Name: " << student.firstName << " " << student.lastName << '\n';
        std::cout << "Correct: " << student.scoreCorrect << " / 15 \n";
        std::cout << std::endl;
    }
}

int main()
{
    std::ifstream inData;
    inData.open("Quiz.dat", std::ifstream::in);

    // List of students.
    std::vector<StudentRecord> classList = {};

    // Answer Key
    std::string answerKey;

    if (!inData)
    {
        std::cout << "File 'Quiz.dat' was not found. " << std::endl;
        PressAnyKey();
        return 1;
    }
    else
    {
        std::cout << "Opening file 'Quiz.dat' " << std::endl;

        ReadFile(classList, answerKey, inData);

        GradeTest(classList, answerKey);
        Display(classList);

        inData.close();
    }

    PressAnyKey();

    return 0;
}