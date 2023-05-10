#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
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
                newQuestion += "2efcde9\n" + qText + "\n";
            }
            else if (qType == "True/False")
            {
                newQuestion += "b94d27b\n" + qText + "\n";
            }
            else if (qType == "Subjective")
            {
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
            newQuestion += "2efcde9\n" + qText + "\n";
        }
        else if (qType == "True/False")
        {
            newQuestion += "b94d27b\n" + qText + "\n";
        }
        else if (qType == " Subjective")
        {
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

Teacher::Teacher(Course c)
{
    course = c;
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
