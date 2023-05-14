#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
#include "examinationSystem.h"

using namespace std;

User::User()
{
    name = " ";
    email = " ";
    password = " ";
}

User::User(string Name, string Email, string Password) : name(Name), email(Email), password(Password)
{
}

User::User(const string &name) : name(name)
{
}

void User::setName(string n)
{
    name = n;
}

void User::setEmail(string Email)
{
    email = Email;
}

void User::setPassword(string p)
{
    password = p;
}

string User::getName()
{
    return name;
}

string User::getEmail()
{
    return email;
}

string User::getPassword()
{
    return password;
}

Authenticator::Authenticator()
{
}

bool Authenticator::authenticatePass(string pass)
{
    bool isUpper = false;
    bool isLower = false;
    bool digitCheck = false;
    bool lenCheck = false;
    int passLen = 0;
    bool passCheck = false;

    for (int i = 0; pass[i] != '\0'; i++) /* Array Length Calculator */
    {
        passLen++;
    }

    if (passLen >= 6 && passLen <= 50) // password length check
    {
        lenCheck = true;
    }

    for (int i = 0; i < passLen; i++) // uppercase character check
    {
        if (pass[i] >= 65 && pass[i] <= 90)
        {
            isUpper = true;
            break;
        }
    }

    for (int i = 0; i < passLen; i++) // lowercase character check
    {
        if (pass[i] >= 97 && pass[i] <= 122)
        {
            isLower = true;
            break;
        }
    }

    for (int i = 0; i < passLen; i++) // digit check
    {
        if (pass[i] >= 48 && pass[i] <= 57)
        {
            digitCheck = true;
            break;
        }
    }

    if (isLower == true && isUpper == true && digitCheck == true && lenCheck == true)
    {
        passCheck = true;
    }

    if (lenCheck == false || isUpper == false || isLower == false || digitCheck == false)
    {
        cout << "The password be atleast 6 characters long and should contain atleast one uppercase, one lowercase character and a digit" << endl;
    }

    return passCheck;
}

bool Authenticator::authenticateEmail(string email)
{
    bool atSymbolCheck = false;
    bool dotSymbolCheck = false;
    bool validCharsBeforeAtSymbol = false;
    bool validCharsAfterAtSymbol = false;
    bool emailCheck = false;

    for (int i = 0; i < email.length(); i++)
    {
        char c = email[i];

        //@ symbol checker
        if (c == '@')
        {
            // to make sure @ symbol only appears once
            if (atSymbolCheck)
            {
                return false;
            }
            atSymbolCheck = true;
        }
        else if (c == '.') // to make sure '.' only appears after @ symbol
        {
            if (!atSymbolCheck)
            {
                return false;
            }
            dotSymbolCheck = true;
        }
        else if (!atSymbolCheck) // to check if the character before the @ symbol us valid
        {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.' || c == '_' || c == '-')) // to check if the character is an allowed character
            {
                return false;
            }
            validCharsBeforeAtSymbol = true;
        }
        else if (atSymbolCheck && !dotSymbolCheck) // to check if the character after the @ symbol is valid
        {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.' || c == '_' || c == '-')) // to check if the character is an allowed character
            {
                return false;
            }
            validCharsAfterAtSymbol = true;
        }
        else if (dotSymbolCheck) // to check if the character after '.' symbol is valid
        {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.' || c == '_' || c == '-')) // to check if the character is an allowed character
            {
                return false;
            }
        }
    }

    if (!validCharsBeforeAtSymbol || !validCharsAfterAtSymbol)
    {
        return false;
    }

    return true;
}

Menu::Menu()
{
    title = " ";
    options = new string[1];
    options[0] = '\0';
    numOfOptions = 0;
}

Menu::Menu(string Title, string *opts, int numOfOpts)
{
    title = Title;
    numOfOptions = numOfOpts;
    options = new string[numOfOpts];
    for (int i = 0; i < numOfOpts; i++)
    {
        options[i] = opts[i];
    }
}

void Menu::displayMenu()
{
    cout << title << endl;
    for (int i = 0; i < numOfOptions; i++)
    {
        cout << options[i] << endl;
    }
}

int Menu::getUserInput()
{
    int input = 0;
    cout << "Type the option number that you want to select: ";
    cin >> input;

    return input;
}

Teacher::Teacher()
{
}

Teacher::Teacher(Course c)
{
    course = c;
}

void Teacher::setCourse(Course c)
{
    course = c;
}

Course Teacher::getCourse()
{
    return course;
}

void Teacher::updateQuizBank(string courseName)
{
    // open the existing file and read all existing questions
    // string fileName = courseName;
    ifstream inputfile(courseName);
    string line = "", questions = "";
    while (getline(inputfile, line))
    {
        questions += line += "\n";
    }
    inputfile.close();

    ofstream outputFile(courseName, ios_base::app); // open the quiz bank file in append mode to add new questions

    string newQuestion = "", qType = "", topic = "", qText = "", options = "", correctOption = ""; // create a new question of user requested type

    cout << "Enter the type of question (MCQ, True/False, Subjective): ";
    cin >> qType; // ask user to choose the type of question to be added

    cout << "Enter the topic: ";
    // cin.ignore();
    getline(cin, topic);

    bool topicAlreadyExists = false; // to check if the topic already exists
    int position = 0;
    while (position < questions.length())
    {
        int topicPosition = questions.find("a5380ee", position);
        if (topicPosition == -1)
        {
            break;
        }
        int nextTopicPosition = questions.find("a5380ee", topicPosition + 1);
        if (nextTopicPosition == -1)
        {
            nextTopicPosition = questions.length();
        }
        if (questions.substr(topicPosition + 10, nextTopicPosition - (topicPosition + 10)) == topic)
        {
            newQuestion += "a5380ee\n" + topic + "\n\n";
            if (qType == "MCQ")
            {
                cout << "Enter the question: ";
                getline(cin, qText);
                newQuestion += "2efcde9\n" + qText + "\n";
            }
            else if (qType == "True/False")
            {
                cout << "Enter the statement: ";
                getline(cin, qText);
                newQuestion += "b94d27b\n" + qText + "\n";
            }
            else if (qType == "Subjective")
            {
                cout << "Enter the question: ";
                getline(cin, qText);
                newQuestion += "88f7ace\n" + qText + "\n";
            }

            if (qType == "MCQ" || qType == "True/False")
            {
                cout << "Enter the options (one per line, enter a period to stop):\n";
                while (true)
                {
                    getline(cin, options);
                    if (options == ".")
                    {
                        break;
                    }
                    newQuestion += options + "\n";
                }
                cout << "Enter the correct option: ";
                getline(cin, correctOption);
                newQuestion += "dabfac4: " + correctOption + "\n";
            }
            newQuestion += "\n";

            questions.insert(nextTopicPosition, newQuestion);
            topicAlreadyExists = true;
            break;
        }
        position = nextTopicPosition;
    }

    if (!topicAlreadyExists) // in case topic does not already exist
    {
        newQuestion += "a5380ee\n" + topic + "\n\n";
        if (qType == "MCQ")
        {
            cout << "Enter the question: ";
            getline(cin, qText);
            newQuestion += "2efcde9\n" + qText + "\n";
        }
        else if (qType == "True/False")
        {
            cout << "Enter the statement: ";
            getline(cin, qText);
            newQuestion += "b94d27b\n" + qText + "\n";
        }
        else if (qType == "Subjective")
        {
            cout << "Enter the question: ";
            getline(cin, qText);
            newQuestion += "88f7ace\n" + qText + "\n";
        }

        if (qType == "MCQ" || qType == "True/False")
        {
            cout << "Enter the options (one per line, enter a period to stop):\n";
            while (true)
            {
                getline(cin, options);
                if (options == ".")
                {
                    break;
                }
                newQuestion += options + "\n";
            }
            cout << "Enter the correct option: ";
            getline(cin, correctOption);
            newQuestion += "dabfac4: " + correctOption + "\n";
        }
        newQuestion += "\n";

        outputFile << newQuestion; // write the new question to the end of quiz bank
    }

    outputFile.close(); // close the output stream
}

void Teacher::createQuiz(string qBankFileName)
{
    int mcqMarks = 0, tfMarks = 0, subMarks = 0, totalMarks = 0;
    cout << "Enter marks for MCQs: ";
    cin >> mcqMarks;
    cout << "Enter marks for True/False: ";
    cin >> tfMarks;
    cout << "Enter marks for Subjectives: ";
    cin >> subMarks;

    cout << "Enter the quiz (YYYY-MM-DD HH:MM): ";
    string deadlineStr = "";
    cin.ignore();
    getline(cin, deadlineStr);

    ifstream quizBank(qBankFileName);

    if (!quizBank.is_open())
    {
        cout << "Failed to open the file: " << qBankFileName << endl;
        return;
    }

    string line = "";
    int numOfMCQs = 0;
    int numOfTrueFalse = 0;
    int numOfSubjectives = 0;
    int numOfTopics = 0;
    string questions = "";

    while (getline(quizBank, line))
    {
        questions += line + "\n"; // store all the questions

        if (line.find("a5380ee") != string::npos)
        {
            numOfTopics++;
        }
        else if (line.find("2efcde9") != string::npos)
        {
            numOfMCQs++;
        }
        else if (line.find("b94d27b") != string::npos)
        {
            numOfTrueFalse++;
        }
        else if (line.find("88f7ace") != string::npos)
        {
            numOfSubjectives++;
        }
    }

    totalMarks = (numOfMCQs * mcqMarks) + (numOfSubjectives * subMarks) + (numOfTrueFalse * tfMarks);

    // time_t currentTime = time(nullptr);

    int quizNo = 1;
    string userInput = "";

    string fileNamesFileName = course.getCourseName() + " Quizzes.txt";
    ofstream fileNamesFile(fileNamesFileName);
    if (!fileNamesFile.is_open())
    {
        cout << "Failed to create file names file" << endl;
    }

    do
    {
        string quizFileName = course.getCourseName() + " Quiz " + to_string(quizNo) + ".txt";
        ofstream quizFile(quizFileName);
        if (!quizFile.is_open())
        {
            cout << "Failed to create the quiz file";
            return;
        }

        quizFile << course.getCourseName() << " Quiz" << endl;
        quizFile << "Rubric: Each mcq contains " << mcqMarks << " marks, each true/false has " << tfMarks << " marks and each subjective question has " << subMarks << " marks!" << endl;
        quizFile << "Total Marks: " << totalMarks << endl;
        quizFile << "Deadline: " << deadlineStr << endl;
        quizFile << questions;

        quizFile.close();

        cout << "Do you want to create more quizzes? (yes/no): ";
        cin >> userInput;

        fileNamesFile << quizFileName << endl;
        quizNo++;
    } while (userInput == "yes");

    quizBank.close();
    fileNamesFile.close();

    // to check if the code is working correctly
    // cout << "Number of MCQs: " << numOfMCQs << endl;
    // cout << "Number of True/False: " << numOfTrueFalse << endl;
    // cout << "Number of Subjectives: " << numOfSubjectives << endl;

    cout << "Quiz created successfully!" << endl;
}

Student::Student()
{
    numRegisteredCourses = 0;
    rollNo = "";
    registeredCourses = "";
}

Student::Student(string rCourses, int nRCourses, string RollNo)
{
    numRegisteredCourses = nRCourses;
    rollNo = RollNo;
    int size = 0;
    registeredCourses = rCourses;
}

void Student::setRollNo(string RollNo)
{
    rollNo = RollNo;
}

string Student::getRollNo()
{
    return rollNo;
}

void Student::setNoRegCourses(int nrc)
{
    numRegisteredCourses = nrc;
}

int Student::getNoRegCourses()
{
    return numRegisteredCourses;
}

void Student::setRegCourses(string regCourses)
{
    registeredCourses = regCourses;
}

string Student::getRegCourses()
{
    return registeredCourses;
}

// Answer::Answer()
// {
//     correctAnsMCQs = "";
//     correctAnsTrueFalse = "";
// }

// Answer::Answer(string ca, string catf)
// {
//     correctAnsMCQs = ca;
//     correctAnsTrueFalse = catf;
// }

// void Answer::setAnsMCQs(string ca)
// {
//     correctAnsMCQs = ca;
// }

// void Answer::setAnsTf(string catf)
// {
//     correctAnsTrueFalse = catf;
// }

// string Answer::getAnsMCQs()
// {
//     return correctAnsMCQs;
// }

// string Answer::getAnsTf()
// {
//     return correctAnsTrueFalse;
// }

void Student::attemptQuiz(string quizFileName)
{
    string *correctAns;
    string *userInput;
    int totalQuestions = 0, numOfMCQs = 0, numOfTrueFalse = 0, numOfSubjectives = 0;
    string line = "";
    int totalMarks = 0;

    ifstream quiz(quizFileName);
    if (!quiz.is_open())
    {
        cout << "Error opening the file" << endl;
    }

    while (getline(quiz, line))
    {
        if (line.find("2efcde9") != string::npos)
        {
            numOfMCQs++;
        }
        else if (line.find("b94d27b") != string::npos)
        {
            numOfTrueFalse++;
        }
        else if (line.find("88f7ace") != string::npos)
        {
            numOfSubjectives++;
        }
    }
    totalQuestions = numOfMCQs + numOfSubjectives + numOfTrueFalse;
    // cout << totalQuestions << endl;

    correctAns = new string[numOfMCQs + numOfTrueFalse];
    userInput = new string[totalQuestions];

    quiz.clear();
    quiz.seekg(0, ios::beg); // Reset the file pointer to the beginning of the file

    string in = "";
    int caIndex = 0, uiIndex = 0;
    string line2 = "";
    while (getline(quiz, line2))
    {
        cout << line2 << endl;
        if (line2.find("dabfac4") != string::npos)
        {
            // cout << "ee";
            correctAns[caIndex] = line2;
            stringstream ss;
            ss << "dabfac4: option. ";
            cout << "Enter your answer: ";
            getline(cin, in);
            cin.ignore();
            ss << in;
            userInput[uiIndex] = ss.str(); //"dabfac4: option." + ;
            cout << "User input:" << userInput[uiIndex] << endl;
            cout << "User input:" << correctAns[caIndex] << endl;
            if (correctAns[caIndex] == userInput[uiIndex])
            {
                totalMarks++;
            }
            caIndex++;
            uiIndex++;
            cout << "marks: " << totalMarks << endl;
            continue;
        }
        // else if (line2.find("88f7ace") != string::npos)
        // {
        //     cout << line2 << endl;
        //     cout << "Enter your answer: ";
        //     getline(cin, userInput[uiIndex]);
        //     uiIndex++;
        // }
    }

    quiz.close();
}

Course::Course()
{
    courseName = "";
    courseCode = "";
    courseInstructor = "";
}

Course::Course(string cName, string cCode, string cInstructor)
{
    courseName = cName;
    courseCode = cCode;
    courseInstructor = cInstructor;
}

void Course::setCourseName(string cName)
{
    courseName = cName;
}

void Course::setCourseCode(string cCode)
{
    courseCode = cCode;
}

void Course::setCourseInstructor(string insDetails)
{
    courseInstructor = insDetails;
}

string Course::getCourseName()
{
    return courseName;
}

string Course::getCourseCode()
{
    return courseCode;
}

string Course::getCourseInstructor()
{
    return courseInstructor;
}
