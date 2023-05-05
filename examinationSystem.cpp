#include <iostream>
#include <fstream>
#include <ctime>
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

    if (lenCheck == false)
    {
        cout << "Error: The password should only contain 6-50 characters" << endl;
    }

    if (isUpper == false)
    {
        cout << "Error: The password should contain atleast one uppercase character" << endl;
    }

    if (isLower == false)
    {
        cout << "Error: The password should contain atleast one lowercase character" << endl;
    }

    if (digitCheck == false)
    {
        cout << "Error: The password should contain atleast one digit" << endl;
    }

    if (isLower == true && isUpper == true && digitCheck == true && lenCheck == true)
    {
        passCheck = true;
    }
    else
    {
        passCheck = false;
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