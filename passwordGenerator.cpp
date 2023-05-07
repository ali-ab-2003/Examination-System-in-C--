#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void generatePassword()
{
    const int numOfPasswords = 11;
    const int minLen = 6;
    const int maxLen = 12;

    const int numOfDigits = 10;

    const string upperChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string lowerChars = "abcdefghijklmnopqrstuvwxyz";
    const char digits[numOfDigits] = {'0',
                                      '1',
                                      '2',
                                      '3',
                                      '4',
                                      '5',
                                      '6',
                                      '7',
                                      '8',
                                      '9'};
    const string specialChars = "!@#$%^&*()-_=+[]{}|;:/?.,<>";

    ofstream outFile("Teacher Passwords.txt");

    if (outFile.is_open())
    {
        srand(time(NULL));

        for (int i = 0; i < numOfPasswords; i++)
        {
            int passLen = minLen + rand() % (maxLen - minLen + 1);

            string password = "";

            bool upperCheck = false;
            bool lowerCheck = false;
            bool digitCheck = false;
            bool spcCharCheck = false;

            for (int j = 0; j < passLen; j++)
            {
                int charType = rand() % 4;

                if (charType == 0)
                {
                    password += upperChars[rand() % upperChars.length()];
                    upperCheck = true;
                }
                else if (charType == 1)
                {
                    password += lowerChars[rand() % lowerChars.length()];
                    lowerCheck = true;
                }
                else if (charType == 2)
                {
                    password += digits[rand() % numOfDigits];
                    digitCheck = true;
                }
                else
                {
                    password += specialChars[rand() % specialChars.length()];
                    spcCharCheck = true;
                }
            }

            if (upperCheck && lowerCheck && digitCheck && spcCharCheck)
            {
                outFile << password << endl;
            }
            else
            {
                i--;
            }
        }

        outFile.close();
    }
    else
    {
        cout << "Error: Could not open file for writing." << endl;
    }
}

int main()
{
    generatePassword();

    return 0;
}