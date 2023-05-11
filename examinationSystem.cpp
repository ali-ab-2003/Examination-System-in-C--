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

void getRandomQuestions(const string &topics, int numOfQuestions, string &selectedQuestions)
{
    string t = topics;
    vector<string> questions;

    int startPosition = 0, endPosition = 0;

    while ((endPosition = t.find("\n\n", startPosition)) != string::npos)
    {
        string question = t.substr(startPosition, endPosition - startPosition);
        questions.push_back(question);

        startPosition = endPosition + 2;
    }

    if (questions.size() < numOfQuestions)
    {
        cout << "Not enough questions to select from\n";
        return;
    }

    srand(time(0));
    vector<bool> selected(questions.size(), false);

    for (int i = 0; i < numOfQuestions;)
    {
        int index = rand() % questions.size();

        if (!selected[index])
        {
            selectedQuestions += questions[index] + "\n\n";
            selected[index] = true;
            i++;
        }
    }
}

string getTimeStamp()
{
    time_t now = time(0);
    struct tm *timeInfo;
    char buffer[80];
    timeInfo = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeInfo);
    return string(buffer);
}

void Teacher::createQuiz(string qBankFileName)
{
    ifstream inputFile(qBankFileName); // open quiz bank file
    if (!inputFile)
    {
        cout << "Quiz bank file does not exist for this course\n";
        return;
    }

    string line = "";
    string questions = "", question = "";
    while (getline(inputFile, line))
    {
        if (line == "a5380ee" || line == "2efcde9" || line == "b94d27b" || line == "88f7ace")
        {
            if (!question.empty())
            {
                questions += question;
                question.clear();
            }
            question += line + "\n";
        }
        else
        {
            question += line + "\n";
        }
    }
    if (!question.empty())
    {
        questions += question;
    }

    inputFile.close();

    string selectedTopics = ""; // asl teacher to select topics for the quiz
    int numOfTopics = 0;
    cout << "Enter the number of topics you want to include in this quiz: ";
    cin >> numOfTopics;
    cin.ignore();

    vector<string> topicNames;
    vector<int> topicNumQuestions;
    vector<int> topicMarks;

    for (int i = 0; i < numOfTopics; i++)
    {
        cout << "Enter topic " << i + 1 << ": ";
        string topic = "";
        getline(cin, topic);
        selectedTopics += topic + "\n";
        topicNames.push_back(topic);
    }

    for (int i = 0; i < numOfTopics; i++)
    {
        string topic = topicNames[i];
        cout << "Enter the number of questions for topic '" << topicNames[i] << "': ";
        int temp = 0;
        cin >> temp;
        topicNumQuestions.push_back(temp);

        cout << "Enter the marks for each question in topic '" << topicNames[i] << "': ";
        int marks = 0;
        cin >> marks;
        topicMarks.push_back(marks);
        cin.ignore();
    }

    int timeLimit = 0; // ask teacher to set time limit for the quiz
    cout << "Enter the time limit for the quiz (in mins): ";
    cin >> timeLimit;

    auto now = chrono::system_clock::now();
    auto endTime = now + chrono::minutes(timeLimit);
    srand(time(0));

    cout << "\nQuiz Generated:\n"; // just to display the time limits in the quiz file
    cout << "******************\n";
    cout << "Time Limit: " << timeLimit << " minutes\n";
    cout << "End time: " << chrono::system_clock::to_time_t(endTime) << "\n";
    cout << "******************\n";

    int totalMarks = 0;

    string deadLine = to_string(chrono::system_clock::to_time_t(endTime));

    string timeStamp = getTimeStamp();
    string quizFileName = course.getCourseCode() + " Quiz " + timeStamp + ".txt";
    ofstream outputFile(quizFileName);
    if (outputFile)
    {
        outputFile << "Quiz Generated:\n";
        outputFile << "******************\n";
        outputFile << "Time Limit: " << timeLimit << " minutes\n";
        outputFile << "Deadline: " << deadLine << "\n";
        outputFile << "******************\n\n";

        for (int i = 0; i < numOfTopics; i++)
        {
            string topic = topicNames[i];

            int topicStartPosition = questions.find("a5380ee\n" + topic + "\n");
            int topicEndPosition = questions.find("a5380ee", topicStartPosition + topic.length() + 9);

            // if (topicEndPosition == string::npos)
            // {
            //     topicEndPosition = questions.size();
            // }

            if (topicStartPosition != string::npos && topicEndPosition != string::npos)
            {
                string topicQuestions = questions.substr(topicStartPosition, topicEndPosition - topicStartPosition);
                int numTopicQuestions = countOccurence(topicQuestions, "a5380ee:");

                if (numTopicQuestions < topicNumQuestions[i])
                {
                    cout << "Insufficient questions in topic '" << topic << "'. Skipping the topic\n";
                    continue;
                }

                cout << "Topic: " << topic << " (Number of Questions: " << topicNumQuestions[i] << ", Marks per Question: " << topicMarks[i] << ")\n\n";
                outputFile << "Topic: " << topic << " (Number of Questions: " << topicNumQuestions[i] << ", Marks per Question: " << topicMarks[i] << ")\n\n";

                string selectedQuestions = "";
                getRandomQuestions(topicQuestions, topicNumQuestions[i], selectedQuestions);

                int questionStartPosition = 0;
                for (int j = 0; j < topicNumQuestions[i]; j++)
                {
                    int questionEndPosition = selectedQuestions.find("\n\n", questionStartPosition);
                    string question2 = selectedQuestions.substr(questionStartPosition, questionEndPosition - questionStartPosition);

                    cout << question2 << "\n";
                    outputFile << question2 << "\n";
                    totalMarks += topicMarks[i];

                    questionStartPosition = questionEndPosition + 2;
                }
                cout << "\n";
                outputFile << "\n";
                // totalMarks += topicNumQuestions[i] * topicMarks[i];
            }
        }

        outputFile << "**************\n";
        outputFile << "Total marks: " << totalMarks << "\n";
        outputFile << "**************\n";
        // outputFile.close();
        cout << "Quiz generated and saved to file: " << quizFileName << "\n";
    }
    else
    {
        cout << "Failed to create quiz file\n";
    }
    outputFile.close();
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
