#ifndef EXAM_H
#define EXAM_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

class User
{
protected:
    string name;
    string email;
    string password;

public:
    User();
    User(string Name, string Email, string Password);
    User(const string &name);
    void setName(string n);
    void setEmail(string Email);
    void setPassword(string p);
    string getName();
    string getEmail();
    string getPassword();
};

class Course
{
private:
    string courseName;
    string courseCode;
    string courseInstructor;

public:
    Course();
    Course(string cName, string cCode, string cInstructor);
    void setCourseName(string cName);
    void setCourseCode(string cCode);
    void setCourseInstructor(string insDetails);
    string getCourseName();
    string getCourseCode();
    string getCourseInstructor();
};

class Teacher : public User
{
private:
    Course course;

public:
    Teacher();
    Teacher(Course c);
    void setCourse(Course c);
    Course getCourse();
    void updateQuizBank(string courseName);
    void createQuiz(string qBankFileName);
    void viewAnalytics();
};

class Student : public User
{
private:
    string registeredCourses;
    int numRegisteredCourses;
    string rollNo;

public:
    Student();
    Student(string rCourses, int nRCourses, string RollNo);
    void setRollNo(string RollNo);
    string getRollNo();
    void setNoRegCourses(int nrc);
    int getNoRegCourses();
    void setRegCourses(string regCourses);
    string getRegCourses();
    void attemptQuiz(string quizFileName);
    void viewResults();
};

// class Result
// {
// private:
//     Student *student;
//     Quiz *quiz;
//     float score;
//     Answer *ans;
//     int numofAns;

// public:
//     Result();
//     Result(Student *s, Quiz *q, float Score, Answer *answer, int numOfAns);
//     Student *getStudent() const;
//     Quiz *getQuiz() const;
//     float getScore() const;
//     Answer *getAnswers() const;
//     void addAnswer(Answer *answer);
// };

// class Answer
// {
// private:
//     string correctAnsMCQs;
//     string correctAnsTrueFalse;

// public:
//     Answer();
//     Answer(string ca, string catf);
//     void setAnsMCQs(string ca);
//     void setAnsTf(string catf);
//     string getAnsMCQs();
//     string getAnsTf();
// };

// class Analytics
// {
// public:
//     void generateAttendance();
//     void generateQDifficulty();
//     void generateAvgPerCourse();
// };

class Menu
{
private:
    string title;
    string *options;
    int numOfOptions;

public:
    Menu();
    Menu(string Title, string *opts, int numOfOpts);
    void displayMenu();
    int getUserInput();
};

class Authenticator
{
public:
    Authenticator();
    static bool authenticatePass(string pass);
    static bool authenticateEmail(string email);
};

#endif