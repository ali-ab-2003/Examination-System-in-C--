#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream inputFile("roll.txt");
    ofstream outputFile("Emails.txt");

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cout << "Error: Failed to open the file." << endl;
        return 1;
    }

    string name = "";

    while (getline(inputFile, name))
    {
        string email = name + "@nu.edu.pk";
        outputFile << email << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}