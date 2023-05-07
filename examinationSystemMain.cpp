#include <iostream>
#include "examinationSystem.cpp"

using namespace std;

int main()
{
    string *userTypeOptions = new string[2]; // menu to determine the user type and direct them to appropriate menu type
    userTypeOptions[0] = "1. Teacher";
    userTypeOptions[1] = "2. Student";

    Menu userTypeMenu("Welcome to FAST Spring 2023 OOP Project\nExamination System\nSelect the user type to proceed to the next menu", userTypeOptions, 2);
    userTypeMenu.displayMenu();
    userTypeMenu.getUserInput();

    string email = " ", pass = " "; // login menu data members
    User user;
    cout << "Login Menu" << endl
         << "Email: ";
    cin >> email;
    if (Authenticator::authenticateEmail(email) == true) // email input
    {
        user.setEmail(email);
    }
    else
    {
        while (Authenticator::authenticateEmail(email) != true)
        {
            cout << "Email is not correct, try again" << endl
                 << "Email: ";
            cin >> email;
        }
        user.setEmail(email);
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