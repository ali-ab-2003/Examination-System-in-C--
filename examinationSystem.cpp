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
    cout << "Type the option number of what you want to select: ";
    cin >> input;

    return input;
}

Teacher::Teacher(const string &name) : User(name)
{
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