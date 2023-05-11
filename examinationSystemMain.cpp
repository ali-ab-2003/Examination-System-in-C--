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

    Course pf("Programming Fundamentals", "CS 101", "Dr. Hassan Mujtaba"); // Available Courses
    Course oop("Object Oriented Programming", "CS 201", "Dr. Ishtiaq");
    Course itc("Introduction to Computing", "CS 102", "Dr. Hassan Raza");
    Course ds("Data Structures", "CS 301", "Dr. Adil Majeed");
    Course aoa("Analysis of Algorithms", "CS 302", "Dr. Omer Beig");
    Course sre("Software Requirements Engineering", "SE 301", "Dr. Naveed");
    Course rm("Research Methodology", "CS 501", "Dr. Abdul Salam");
    Course bda("Big Data Analytics", "CS 407", "Dr. Khubaib Amjad");
    Course ai("Artificial Intelligence", "CS 307", "Dr. Waseem Shahzad");
    Course dl("Deep Learning", "CS 601", "Dr. Hammad Majeed");
    Course dip("Digital Image Processing", "CS 409", "Dr. Muhammad Asim");

    Menu userTypeMenu("Welcome to FAST Spring 2023 OOP Project\nExamination System\nSelect the user type to proceed to the next menu", userTypeOptions, 2);
    userTypeMenu.displayMenu();
    // int stdOrTeacher = userTypeMenu.getUserInput();
    int stdOrTeacher = 0;
    cout << "Type the option number of what you want to select: ";
    cin >> stdOrTeacher;

    string email = " ", pass = " "; // login menu data members
    User user;
    Student student;
    cout << "Login Menu" << endl;

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

        bool emailCheck = false; // email and password validation for teachers
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

        bool passCheck = false;
        while (!passCheck)
        {
            cout << "Password: "; // password input
            cin >> pass;

            bool passCrossCheck = false;
            for (int i = 0; i < 11; i++)
            {
                if (userData[i][1] == pass)
                {
                    passCrossCheck = true;
                    break;
                }
            }

            if (Authenticator::authenticatePass(pass) && passCrossCheck)
            {
                user.setPassword(pass);
                passCheck = true;
            }
            else
            {
                cout << "Password is not correct, try again" << endl;
            }
        }

        int numOfTeachers = 11; // code to check the teacher's name agianst the email provided

        ifstream namesFile1("Teacher Names.txt");
        ifstream emailsFile1("Teacher Emails.txt");

        if (!namesFile1.is_open() || !emailsFile1.is_open())
        {
            cout << "unable to open files";
        }

        string **teacherCredentials = new string *[numOfTeachers];
        for (int i = 0; i < numOfTeachers; i++)
        {
            teacherCredentials[i] = new string[2];
        }

        for (int i = 0; i < numOfTeachers; i++)
        {
            getline(emailsFile1, teacherCredentials[i][0]);
            getline(namesFile1, teacherCredentials[i][1]);
        }

        namesFile1.close();
        emailsFile1.close();

        // for (int i = 0; i < 11; i++)
        // {
        //     for (int j = 0; j < 2; j++)
        //     {
        //         cout << teacherCredentials[i][j];
        //         cout << " ";
        //     }
        //     cout << endl;
        // }

        for (int i = 0; i < numOfTeachers; i++)
        {
            if (teacherCredentials[i][0] == email)
            {
                user.setName(teacherCredentials[i][1]);
                break;
            }
            else if (i == numOfTeachers - 1)
            {
                cout << "No user record found for " << email << endl;
            }
        }

        Teacher teacher;
        bool pfCheck = false, oopCheck = false, itcCheck = false, dsCheck = false, aoaCheck = false, sreCheck = false, rmCheck = false, bdaCheck = false, aiCheck = false, dlCheck = false, dipCheck = false;

        if (user.getName() == pf.getCourseInstructor())
        {
            teacher.setCourse(pf);
            pfCheck = true;
        }
        else if (user.getName() == oop.getCourseInstructor())
        {
            teacher.setCourse(oop);
            oopCheck = true;
        }
        else if (user.getName() == itc.getCourseInstructor())
        {
            teacher.setCourse(itc);
            itcCheck = true;
        }
        else if (user.getName() == ds.getCourseInstructor())
        {
            teacher.setCourse(ds);
            dsCheck = true;
        }
        else if (user.getName() == aoa.getCourseInstructor())
        {
            teacher.setCourse(aoa);
            aoaCheck = true;
        }
        else if (user.getName() == sre.getCourseInstructor())
        {
            teacher.setCourse(sre);
            sreCheck = true;
        }
        else if (user.getName() == rm.getCourseInstructor())
        {
            teacher.setCourse(rm);
            rmCheck = true;
        }
        else if (user.getName() == bda.getCourseInstructor())
        {
            teacher.setCourse(bda);
            bdaCheck = true;
        }
        else if (user.getName() == ai.getCourseInstructor())
        {
            teacher.setCourse(ai);
            aiCheck = true;
        }
        else if (user.getName() == dl.getCourseInstructor())
        {
            teacher.setCourse(dl);
            dlCheck = true;
        }
        else
        {
            teacher.setCourse(dip);
            dipCheck = true;
        }

        string *teacherFunctions = new string[3];
        teacherFunctions[0] = "1. Update Quiz Bank";
        teacherFunctions[1] = "2. Create Quiz";
        teacherFunctions[2] = "3. View Analytics";

        cout << "Welcome back, " << user.getName() << "!" << endl;
        Menu teacherOptions("Teacher Functions Menu", teacherFunctions, 3);
        int tOpts = 0;
        teacherOptions.displayMenu();
        tOpts = teacherOptions.getUserInput();

        if (tOpts == 1)
        {
            // teacher.updateQuizBank("Questions for TestBank.txt"); // just to check if function is working properly
            if (pfCheck == true)
            {
                teacher.updateQuizBank("Programming Fundamentals Quiz Bank.txt");
            }
            else if (oopCheck == true)
            {
                teacher.updateQuizBank("Object Oriented Programming Quiz Bank.txt");
            }
            else if (itcCheck == true)
            {
                teacher.updateQuizBank("Introduction to Computing Quiz Bank.txt");
            }
            else if (dsCheck == true)
            {
                teacher.updateQuizBank("Data Structures Quiz Bank.txt");
            }
            else if (aoaCheck == true)
            {
                teacher.updateQuizBank("Analysis of Algorithms Quiz Bank.txt");
            }
            else if (sreCheck == true)
            {
                teacher.updateQuizBank("Software Requirements Engineering Quiz Bank.txt");
            }
            else if (rmCheck == true)
            {
                teacher.updateQuizBank("Research Methodology Quiz Bank.txt");
            }
            else if (bdaCheck == true)
            {
                teacher.updateQuizBank("Big Data Analysis Quiz Bank.txt");
            }
            else if (aiCheck == true)
            {
                teacher.updateQuizBank("Artificial Intelligence Quiz Bank.txt");
            }
            else if (dlCheck == true)
            {
                teacher.updateQuizBank("Deep Learning Quiz Bank.txt");
            }
            else if (dipCheck == true)
            {
                teacher.updateQuizBank("Digital Image Processing Quiz Bank.txt");
            }
        }

        // for (int i = 0; i < 11; i++)   //code to check if checks implemented are working correctly
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

        bool emailCheck = false; // email and password validation for teachers
        while (!emailCheck)
        {
            cout << "Email: ";
            cin >> email;

            bool emailCrossCheck = false;
            for (int i = 0; i < 216; i++)
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

        bool passCheck = false;
        while (!passCheck)
        {
            cout << "Password: "; // password input
            cin >> pass;

            bool passCrossCheck = false;
            for (int i = 0; i < 216; i++)
            {
                if (userData[i][1] == pass)
                {
                    passCrossCheck = true;
                    break;
                }
            }

            if (Authenticator::authenticatePass(pass) && passCrossCheck)
            {
                user.setPassword(pass);
                passCheck = true;
            }
            else
            {
                cout << "Password is not correct, try again" << endl;
            }
        }

        int numOfStudents = 216; // code to check the student's name and roll number agianst the email provided

        ifstream namesFile("Student Names.txt");
        ifstream emailsFile("Student Emails.txt");
        ifstream rollNoFile("Roll Numbers.txt");

        if (!namesFile.is_open() || !emailsFile.is_open() || !rollNoFile.is_open())
        {
            cout << "unable to open files";
        }

        string **studentCredentials = new string *[numOfStudents];
        for (int i = 0; i < numOfStudents; i++)
        {
            studentCredentials[i] = new string[3];
        }

        for (int i = 0; i < numOfStudents; i++)
        {
            getline(emailsFile, studentCredentials[i][0]);
            getline(namesFile, studentCredentials[i][1]);
            getline(rollNoFile, studentCredentials[i][2]);
        }

        namesFile.close();
        emailsFile.close();
        rollNoFile.close();

        for (int i = 0; i < numOfStudents; i++)
        {
            if (studentCredentials[i][0] == email)
            {
                user.setName(studentCredentials[i][1]);
                student.setRollNo(studentCredentials[i][2]);
                break;
            }
            else if (i == numOfStudents - 1)
            {
                cout << "No user record found for " << email << endl;
            }
        }

        // for (int i = 0; i < 11; i++)    //code to check if checks implemented are working correctly
        // {
        //     for (int j = 0; j < 2; j++)
        //     {
        //         cout << userData[i][j];
        //         cout << " ";
        //     }
        //     cout << endl;
        // }
    }

    return 0;
}