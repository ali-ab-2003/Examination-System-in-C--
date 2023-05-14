#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
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
            teacher.updateQuizBank("Questions for TestBank.txt"); // just to check if function is working properly
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
        else if (tOpts == 2)
        {
            teacher.createQuiz("Questions for TestBank.txt");
            if (pfCheck == true)
            {
                teacher.createQuiz("Programming Fundamentals Quiz Bank.txt");
            }
            else if (oopCheck == true)
            {
                teacher.createQuiz("Object Oriented Programming Quiz Bank.txt");
            }
            else if (itcCheck == true)
            {
                teacher.createQuiz("Introduction to Computing Quiz Bank.txt");
            }
            else if (dsCheck == true)
            {
                teacher.createQuiz("Data Structures Quiz Bank.txt");
            }
            else if (aoaCheck == true)
            {
                teacher.createQuiz("Analysis of Algorithms Quiz Bank.txt");
            }
            else if (sreCheck == true)
            {
                teacher.createQuiz("Software Requirements Engineering Quiz Bank.txt");
            }
            else if (rmCheck == true)
            {
                teacher.createQuiz("Research Methodology Quiz Bank.txt");
            }
            else if (bdaCheck == true)
            {
                teacher.createQuiz("Big Data Analysis Quiz Bank.txt");
            }
            else if (aiCheck == true)
            {
                teacher.createQuiz("Artificial Intelligence Quiz Bank.txt");
            }
            else if (dlCheck == true)
            {
                teacher.createQuiz("Deep Learning Quiz Bank.txt");
            }
            else if (dipCheck == true)
            {
                teacher.createQuiz("Digital Image Processing Quiz Bank.txt");
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

            if (numOfLines1 == 216)
            {
                break;
            }
        }

        while (getline(passInput1, passLine1))
        {
            userData[numOfPass1][1] = passLine1;
            numOfPass1++;

            if (numOfPass1 == 216)
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
            cout << "Unable to open required files";
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

        // for (int i = 0; i < 216; i++) // code to check if checks implemented are working correctly
        // {
        //     for (int j = 0; j < 2; j++)
        //     {
        //         cout << userData[i][j];
        //         cout << ": ";
        //     }
        //     cout << endl;
        // }

        string *studentOptions = new string[3];
        studentOptions[0] = "1. See Registered Courses";
        studentOptions[1] = "2. Attempt Quiz";
        studentOptions[2] = "3. View your result";

        cout << "Welcome back, " << user.getName() << "!" << endl;
        Menu studentOptionsMenu("Student Functions Menu", studentOptions, 3);
        studentOptionsMenu.displayMenu();
        int studentChoice = 0;
        studentChoice = studentOptionsMenu.getUserInput();

        string courseRegData[12][216];

        ifstream sNames("Student Names.txt");
        ifstream cRegData("Course Registration Data.txt");
        if (!sNames)
        {
            cout << "Error opening the file" << endl;
        }
        if (!cRegData)
        {
            cout << "Error opening the file." << endl;
        }

        for (int i = 0; i < 216; ++i)
        {
            if (!getline(sNames, courseRegData[0][i]))
            {
                cout << "Error reading the file." << endl;
            }
        }

        string line0 = "";
        int column = 0;
        while (getline(cRegData, line0))
        {
            istringstream iss(line0);
            string value = "";
            int row = 1;
            while (getline(iss, value, ','))
            {
                courseRegData[row][column] = value;
                ++row;
            }
            ++column;
        }

        // for (int i = 0; i < 12; i++)
        // {
        //     cout << courseRegData[i][0] << endl;
        // }

        sNames.close();
        cRegData.close();

        int nameIndex = -1;

        for (int i = 0; i < 216; ++i)
        {
            if (courseRegData[0][i] == user.getName())
            {
                nameIndex = i;
                break;
            }
        }

        int numOfRegCourses = 0;
        string listOfRegCourses = "";

        for (int i = 1; i < 12; i++)
        {
            if (courseRegData[i][nameIndex] == "1")
            {
                numOfRegCourses++;
            }
        }

        // cout << "Reg courses: " << numOfRegCourses << endl;
        student.setNoRegCourses(numOfRegCourses);
        // listOfRegCourses = new string[numOfRegCourses];

        if (courseRegData[1][nameIndex] == "1")
        {
            listOfRegCourses += pf.getCourseName() + "\n";
        }

        if (courseRegData[2][nameIndex] == "1")
        {
            listOfRegCourses += oop.getCourseName() + "\n";
        }

        if (courseRegData[3][nameIndex] == "1")
        {
            listOfRegCourses += itc.getCourseName() + "\n";
        }

        if (courseRegData[4][nameIndex] == "1")
        {
            listOfRegCourses += ds.getCourseName() + "\n";
        }

        if (courseRegData[5][nameIndex] == "1")
        {
            listOfRegCourses += aoa.getCourseName() + "\n";
        }

        if (courseRegData[6][nameIndex] == "1")
        {
            listOfRegCourses += sre.getCourseName() + "\n";
        }

        if (courseRegData[7][nameIndex] == "1")
        {
            listOfRegCourses += rm.getCourseName() + "\n";
        }

        if (courseRegData[8][nameIndex] == "1")
        {
            listOfRegCourses += bda.getCourseName() + "\n";
        }

        if (courseRegData[9][nameIndex] == "1")
        {
            listOfRegCourses += ai.getCourseName() + "\n";
        }

        if (courseRegData[10][nameIndex] == "1")
        {
            listOfRegCourses += dl.getCourseName() + "\n";
        }

        if (courseRegData[11][nameIndex] == "1")
        {
            listOfRegCourses += dip.getCourseName() + "\n";
        }

        // cout << "List of registered courses: " << listOfRegCourses << endl;
        student.setRegCourses(listOfRegCourses);

        if (studentChoice == 1)
        {
            cout << "You are currently enrolled in the following courses:" << endl
                 << listOfRegCourses << endl;
        }
        else if (studentChoice == 2)
        {
            student.attemptQuiz("Object Oriented Programming Quiz 1.txt");
            cout << "Available quizzes:-" << endl;
            if (courseRegData[1][nameIndex] == "1")
            {
                cout << "Programming fundamentals available quizzes:" << endl;
                ifstream pfQuizzesFile("Programming Fundamentals Quizzes.txt");
                string pfLine = "";
                if (pfQuizzesFile.is_open())
                {
                    while (getline(pfQuizzesFile, pfLine))
                    {
                        cout << pfLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Programming fundamentals' quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[2][nameIndex] == "1")
            {
                cout << "Object Oriented Programming available quizzes:" << endl;
                ifstream oopQuizzesFile("Object Oriented Programming Quizzes.txt");
                string oopLine = "";
                if (oopQuizzesFile.is_open())
                {
                    while (getline(oopQuizzesFile, oopLine))
                    {
                        cout << oopLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Object Oriented Programming's quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[3][nameIndex] == "1")
            {
                cout << "Introduction to Computing available quizzes:" << endl;
                ifstream itcQuizzesFile("Introduction to Computing Quizzes.txt");
                string itcLine = "";
                if (itcQuizzesFile.is_open())
                {
                    while (getline(itcQuizzesFile, itcLine))
                    {
                        cout << itcLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Introduction to Computing's quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[4][nameIndex] == "1")
            {
                cout << "Data Structures available quizzes:" << endl;
                ifstream dsQuizzesFile("Data Structures Quizzes.txt");
                string dsLine = "";
                if (dsQuizzesFile.is_open())
                {
                    while (getline(dsQuizzesFile, dsLine))
                    {
                        cout << dsLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Data Structures' quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[5][nameIndex] == "1")
            {
                cout << "Analysis of Algorithms available quizzes:" << endl;
                ifstream aoaQuizzesFile("Analysis of Algorithms Quizzes.txt");
                string aoaLine = "";
                if (aoaQuizzesFile.is_open())
                {
                    while (getline(aoaQuizzesFile, aoaLine))
                    {
                        cout << aoaLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Analysis of Algorithms' quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[6][nameIndex] == "1")
            {
                cout << "Software Research Engineering available quizzes:" << endl;
                ifstream sreQuizzesFile("Software Research Engineering Quizzes.txt");
                string sreLine = "";
                if (sreQuizzesFile.is_open())
                {
                    while (getline(sreQuizzesFile, sreLine))
                    {
                        cout << sreLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Software Research Engineering's quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[7][nameIndex] == "1")
            {
                cout << "Research Methodology available quizzes:" << endl;
                ifstream rmQuizzesFile("Research Methodology Quizzes.txt");
                string rmLine = "";
                if (rmQuizzesFile.is_open())
                {
                    while (getline(rmQuizzesFile, rmLine))
                    {
                        cout << rmLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Research Methodology's quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[8][nameIndex] == "1")
            {
                cout << "Big Data Analytics available quizzes:" << endl;
                ifstream bdaQuizzesFile("Big Data Analytics Quizzes.txt");
                string bdaLine = "";
                if (bdaQuizzesFile.is_open())
                {
                    while (getline(bdaQuizzesFile, bdaLine))
                    {
                        cout << bdaLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Big Data Analytics' quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[9][nameIndex] == "1")
            {
                cout << "Artificial Intelligence available quizzes:" << endl;
                ifstream aiQuizzesFile("Artificial Intelligence Quizzes.txt");
                string aiLine = "";
                if (aiQuizzesFile.is_open())
                {
                    while (getline(aiQuizzesFile, aiLine))
                    {
                        cout << aiLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Artificial Intelligence's quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[10][nameIndex] == "1")
            {
                cout << "Deep Learning available quizzes:" << endl;
                ifstream dlQuizzesFile("Deep Learning Quizzes.txt");
                string dlLine = "";
                if (dlQuizzesFile.is_open())
                {
                    while (getline(dlQuizzesFile, dlLine))
                    {
                        cout << dlLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Deep Learning's quizzes file/it doesn't exist!" << endl;
                }
            }

            if (courseRegData[11][nameIndex] == "1")
            {
                cout << "Digital Image Processing available quizzes:" << endl;
                ifstream dipQuizzesFile("Digital Image Processing Quizzes.txt");
                string dipLine = "";
                if (dipQuizzesFile.is_open())
                {
                    while (getline(dipQuizzesFile, dipLine))
                    {
                        cout << dipLine << endl;
                    }
                }
                else
                {
                    cout << "Error opening Digital Image Processing's quizzes file/it doesn't exist!" << endl;
                }
            }
        }
    }

    return 0;
}