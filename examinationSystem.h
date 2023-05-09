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

class Teacher : public User
{
public:
    Teacher();
    Teacher(const string &name);
    static void updateQuizBank();
    static void createQuiz();
    static void viewAnalytics();
};

class Student : public User
{
private:
    // Course *registeredCourses;
    int numRegisteredCourses;
    string rollNo;

public:
    Student();
    // Student(Course *rCourses, int nRCourses, string RollNo);
    void setRollNo(string RollNo);
    void setNoRegCourses(int nrc);
    void setRegCourses();
    void attemptQuiz();
    void viewResults();
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
    void setInstructor(Teacher insDetails);
    string getCourseName();
    string getCourseCode();
    Teacher getCourseInstructor();
};

// class Question
// {
// protected:
//     string questionText;
//     string questionType;

// public:
//     Question();
//     Question(string qText, string qtype);
//     void setQuestionText(string qText);
//     void setQuestionType(string qType);
//     string getQuestionText();
//     string getQuestionType();
// };

// class Mcqs : public Question
// {
// private:
//     string choices[4];
//     string correctAns;

// public:
//     Mcqs();
//     Mcqs(string Choices[4], string cAns);
//     string *getChoices() const;
//     string getCorrectAns();
// };

// class TrueFalse : public Question
// {
// private:
//     bool correctAns;

// public:
//     TrueFalse();
//     TrueFalse(bool cAns);
//     bool getCorrectAns() const;
// };

// class Subjective : public Question
// {
// private:
//     string suggestedAns;
//     string gradingRubric;

// public:
//     Subjective();
//     Subjective(string suggAns, string rubric);
//     void setGradingRubric(string rubric);
//     string getSuggestedAns();
//     string getGradingRubric();
// };

// class QuestionBank
// {
// private:
//     Question *questions;
//     int numOfQuestions;

// public:
//     QuestionBank();
//     QuestionBank(Question *q, int numOfQ);
//     void addQuestion(Question *question);
//     void removeQuestion(Question *question);
//     Question *getQuestions(string qText);
// };

// class Quiz
// {
// private:
//     string quizName;
//     Time startTime;
//     Time endTime;
//     Question *questions;
//     int numOfQuestions;

// public:
//     Quiz();
//     Quiz(string qName, Time sTime, Time eTime, Question *Qs, int numOfQs);
//     void generateQuiz();
//     void setDuration();
//     void createAnsKey();
// };

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
//     Question *question;
//     string answer;

// public:
//     Answer();
//     Answer(Question *q, string a);
//     Question *getQuestion() const;
//     string getAnswer() const;
//     void setAnswer(string newAns);
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

// class Date
// {
// private:
//     int day;
//     int month;
//     int year;

// public:
//     Date();
//     Date(int d, int m, int y);
//     int getDay() const;
//     void setDay(int d);
//     int getMonth() const;
//     void setMonth(int m);
//     int getYear();
//     void setYear(int y);
// };

// class Time
// {
// private:
//     int hours;
//     int minutes;
//     int seconds;

// public:
//     int getHours() const;
//     void setHours(int h);
//     int getMinutes() const;
//     void setMinutes(int m);
//     int getSeconds() const;
//     void setSeconds(int s);
// };

class Authenticator
{
public:
    Authenticator();
    static bool authenticatePass(string pass);
    static bool authenticateEmail(string email);
    // static bool crossCheckTeacher(string pass, string email);
    // static bool crossCheckStudent(string pass, string email);
};

#endif