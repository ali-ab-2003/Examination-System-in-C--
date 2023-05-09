#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include "examinationSystem.cpp"

using namespace std;

int main()
{
    string *userTypeOptions = new string[2]; // menu to determine the user type and direct them to appropriate menu type
    userTypeOptions[0] = "1. Teacher";
    userTypeOptions[1] = "2. Student";

    Menu userTypeMenu("Welcome to FAST Spring 2023 OOP Project\nExamination System\nSelect the user type to proceed to the next menu", userTypeOptions, 2);
    userTypeMenu.displayMenu();
    // int stdOrTeacher = userTypeMenu.getUserInput();
    int stdOrTeacher = 0;
    cout << "Type the option number of what you want to select: ";
    cin >> stdOrTeacher;

    string **userData;
    if (stdOrTeacher == 1) // user data reading and storing for teachers
    {
        userData = new string *[11];
        for (int i = 0; i < 11; i++)
        {
            userData[i] = new string[2];
        }

        ifstream inputFile("Teacher Emails.txt");
        ifstream passInput("Teacher Passwords.txt");

        if (!inputFile.is_open() || !passInput.is_open())
        {
            cout << "Error: Failed to open the file." << endl;
        }

        string line = "";
        string passLine = "";
        // string *data = nullptr;
        int numOfLines = 0; // to keep track of the number of lines in the file
        int numOfPass = 0;

        while (getline(inputFile, line))
        {
            userData[numOfLines][0] = line;
            numOfLines++;

            if (numOfLines == 11)
            {
                break;
            }
        }

        while (getline(passInput, passLine))
        {
            userData[numOfPass][1] = passLine;
            numOfPass++;

            if (numOfPass == 11)
            {
                break;
            }
        }

        inputFile.close();
        passInput.close();

        // for (int i = 0; i < 11; i++)
        // {
        //     for (int j = 0; j < 2; j++)
        //     {
        //         cout << userData[i][j];
        //         cout << " ";
        //     }
        //     cout << endl;
        // }
    }
    else if (stdOrTeacher == 2) // user data reading and storing for students
    {
        userData = new string *[216];
        for (int i = 0; i < 216; i++)
        {
            userData[i] = new string[2];
        }

        ifstream inputFile1("Student Emails.txt");
        ifstream passInput1("Student Passwords.txt");

        if (!inputFile1.is_open() || !passInput1.is_open())
        {
            cout << "Error: Failed to open the file." << endl;
        }

        string line1 = "";
        string passLine1 = "";
        // string *data = nullptr;
        int numOfLines1 = 0; // to keep track of the number of lines in the file
        int numOfPass1 = 0;

        while (getline(inputFile1, line1))
        {
            userData[numOfLines1][0] = line1;
            numOfLines1++;

            if (numOfLines1 == 11)
            {
                break;
            }
        }

        while (getline(passInput1, passLine1))
        {
            userData[numOfPass1][1] = passLine1;
            numOfPass1++;

            if (numOfPass1 == 11)
            {
                break;
            }
        }

        inputFile1.close();
        passInput1.close();

        // for (int i = 0; i < 11; i++)
        // {
        //     for (int j = 0; j < 2; j++)
        //     {
        //         cout << userData[i][j];
        //         cout << " ";
        //     }
        //     cout << endl;
        // }
    }

    string email = " ", pass = " "; // login menu data members
    User user;
    cout << "Login Menu" << endl;

    bool emailCheck = false;
    while (!emailCheck)
    {
        cout << "Email: ";
        cin >> email;

        bool emailCrossCheck = false;
        for (int i = 0; i < 11; i++)
        {
            if (userData[i][0] == email)
            {
                emailCrossCheck = true;
                break;
            }
        }

        if (Authenticator::authenticateEmail(email) && emailCrossCheck) // email input
        {
            user.setEmail(email);
            emailCheck = true;
        }
        else
        {
            cout << "Email is not correct, try again" << endl;
        }
    }

    cout << "Password: "; // password input
    cin >> pass;
    bool passCheck = Authenticator::authenticatePass(pass);
    if (passCheck)
    {
        user.setPassword(pass);
    }
    else
    {
        while (!passCheck)
        {
            cout << "Password is not correct, try again" << endl
                 << "Password: ";
            cin >> pass;
            passCheck = Authenticator::authenticatePass(pass);
        }
        user.setPassword(pass);
    }

    return 0;
}