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
    cin.ignore();
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

int countOccurence(const string &s, const string &subs)
{
    int count = 0;
    int position = 0;
    while ((position = s.find(subs, position)) != string::npos)
    {
        count++;
        position += subs.length();
    }
    return count;
}

// void getRandomQuestions(const string &topics, int numOfQuestions, string &selectedQuestions)
// {
//     string t = topics;
//     vector<string> questions;

//     int startPosition = 0, endPosition = 0;

//     while ((endPosition = t.find("\n\n", startPosition)) != string::npos)
//     {
//         string question = t.substr(startPosition, endPosition - startPosition);
//         questions.push_back(question);

//         startPosition = endPosition + 2;
//     }

//     if (questions.size() < numOfQuestions)
//     {
//         cout << "Not enough questions to select from\n";
//         return;
//     }

//     srand(time(0));
//     vector<bool> selected(questions.size(), false);

//     for (int i = 0; i < numOfQuestions;)
//     {
//         int index = rand() % questions.size();

//         if (!selected[index])
//         {
//             selectedQuestions += questions[index] + "\n\n";
//             selected[index] = true;
//             i++;
//         }
//     }
// }

string getTimeStamp()
{
    time_t now = time(0);
    struct tm *timeInfo;
    char buffer[80];
    timeInfo = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeInfo);
    return string(buffer);
}

// string getTopicQuestions(const string &questions, const string &topic)
// {
//     string topicQuestions = "";
//     int topicStartPosition = questions.find("a5380ee " + topic + "\n");
//     if (topicStartPosition == string::npos)
//     {
//         return topicQuestions;
//     }

//     int qStartPosition = questions.find("a5380ee:", topicStartPosition);
//     int nextTopicStart = questions.find("a5380ee ", qStartPosition);

//     while (qStartPosition != string::npos && (nextTopicStart == string::npos || qStartPosition < nextTopicStart))
//     {
//         int qEndPosition = questions.find("\n\n", qStartPosition);
//         topicQuestions += questions.substr(qStartPosition, qEndPosition - qStartPosition + 1);
//         qStartPosition = questions.find("a5380ee:", qEndPosition);
//         nextTopicStart = questions.find("a5380ee ", qStartPosition);
//     }

//     return topicQuestions;
// }

struct Questions
{
    string topicName = "";
    string questionStatement = "";
    string options[4];
    string descriptiveQuestion;
    string trueFalse;
    int correctOption = 0;
    string optTF[2];
} arr[100];

void Teacher::createQuiz(string qBankFileName)
{
    ifstream inputFile(qBankFileName);
    int index = -1;
    int k = 0;
    string markers[5] = {"a5380ee", "2efcde9", "dabfac4", "b94d27b", "88f7ace"};
    string temp = "";
    string s = "";
    Questions arr[100];

    if (inputFile.is_open())
    {
        while (getline(inputFile, s))
        {
            if (s == markers[0])
            {
                getline(inputFile, temp);
            }
            else if (s == markers[1])
            {
                index++;
                arr[index].topicName = temp;
                getline(inputFile, arr[index].questionStatement);
                getline(inputFile, s);
                if (s[0] == 'o' && s[1] == 'p')
                {
                    arr[index].options[0] = s;
                    getline(inputFile, arr[index].options[1]);
                    getline(inputFile, arr[index].options[2]);
                    getline(inputFile, arr[index].options[3]);
                }
                else
                {
                    arr[index].questionStatement = arr[index].questionStatement + "\n" + s;
                    getline(inputFile, arr[index].options[0]);
                    getline(inputFile, arr[index].options[1]);
                    getline(inputFile, arr[index].options[2]);
                    getline(inputFile, arr[index].options[3]);
                }
                for (int i = 0; i < 4; i++)
                {
                    if (arr[index].options[i].find(markers[2]) != string::npos)
                    {
                        arr[index].correctOption = i + 1;
                    }
                }
            }
            else if (s == markers[3])
            {
                index++;
                arr[index].topicName = temp;
                getline(inputFile, arr[index].trueFalse);
                getline(inputFile, s);
                if (s[0] == 'o' && s[1] == 'p')
                {
                    arr[index].optTF[0] = s;
                    getline(inputFile, arr[index].optTF[1]);
                }
                else
                {
                    arr[index].trueFalse = arr[index].trueFalse + "\n" + s;
                    getline(inputFile, arr[index].optTF[0]);
                    getline(inputFile, arr[index].optTF[1]);
                }
                for (int i = 0; i < 2; i++)
                {
                    if (arr[index].optTF[i].find(markers[2]) != string::npos)
                    {
                        arr[index].correctOption = i + 1;
                    }
                }
            }
            else if (s == markers[4])
            {
                index++;
                arr[index].topicName = temp;
                getline(inputFile, arr[index].descriptiveQuestion);

                while (getline(inputFile, s))
                {
                    if (s == markers[0] || s == markers[1] || s == markers[2] || s == markers[3] || s == markers[4])
                    {
                        break;
                    }
                    else
                    {
                        arr[index].descriptiveQuestion = arr[index].descriptiveQuestion + "\n" + s;
                    }
                }
            }
        }
    }

    inputFile.close();

    string quizFileName = course.getCourseName() + ".txt";
    ofstream quizFile(quizFileName);

    if (quizFile.is_open())
    {
        for (int i = 0; i <= index; i++)
        {
            quizFile << "Topic: " << arr[i].topicName << "\n\n";
            cout << "Topic: " << arr[i].topicName << "\n\n";
            quizFile << "Question: " << arr[i].questionStatement << "\n\n";
            cout << "Question: " << arr[i].questionStatement << "\n\n";

            if (arr[i].options[0].find("op") != string::npos)
            {
                for (int j = 0; j < 4; j++)
                {
                    quizFile << arr[i].options[j] << "\n";
                    cout << arr[i].options[j] << "\n";
                }
            }
            else
            {
                quizFile << "Options:\n";
                cout << "Options:\n";
                for (int j = 0; j < 4; j++)
                {
                    quizFile << j + 1 << ". " << arr[i].options[j] << "\n";
                    cout << j + 1 << ". " << arr[i].options[j] << "\n";
                }
            }
            quizFile << "Correct option: " << arr[i].correctOption << "\n\n";
            cout << "Correct option: " << arr[i].correctOption << "\n\n";
        }
    }

    quizFile.close();
}

Student::Student()
{
    numRegisteredCourses = 0;
    rollNo = "";
}

void Student::setRollNo(string RollNo)
{
    rollNo = RollNo;
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

// Question::Question()
// {
//     questionText = "";
//     questionType = "";
// }

// Question::Question(string qText, string qType)
// {
//     questionText = qText;
//     questionType = qType;
// }

// void Question::setQuestionText(string qText)
// {
//     questionText = qText;
// }

// void Question::setQuestionType(string qType)
// {
//     questionType = qType;
// }

// string Question::getQuestionText()
// {
//     return questionText;
// }

// string Question::getQuestionType()
// {
//     return questionType;
// }
