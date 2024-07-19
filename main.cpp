#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;

#define ADD_QUESTION 1
#define EDIT_QUESTION 2
#define DELETE_QUESTION 3
#define VIEW_ALL_QUESTIONS 4
#define VIEW_RESULTS_BY_USER 5
#define VIEW_RESULTS_BY_QUIZ 6
#define GENERATE_REPORT 7
#define ADMIN_LOGOUT 8

#define TAKE_QUIZ 1
#define VIEW_SCORES 2
#define RESET_PASSWORD 3
#define USER_LOGOUT 4

#define SIGNUP_ADMIN 1
#define SIGNUP_USER 2
#define LOGIN_ADMIN 3
#define LOGIN_USER 4
#define EXIT 5

struct Question {
    int id;
    int quizId;
    string question;
    string answer;
};

struct User {
    int id;
    string username;
    string password;
    bool isAdmin;
};

struct Result {
    int userId;
    int quizId;
    int score;
    string dateTaken;
};

vector<Question> questions;
vector<User> users;
vector<Result> results;

int nextQuestionId = 1;
int nextUserId = 1;

bool isUsernameExists(const string& username){
    auto it = find_if(users.begin(), users.end(), [&](const User& user){
        return user.username == username;
    });
    return it != users.end();
}

bool authenticateAdmin(const string& username, const string& password){
    auto it = find_if(users.begin(), users.end(), [&](const User& user){
        return user.username == username && user.password == password && user.isAdmin;
    }):
    return it != users.end();
}

bool authenticateUser(const string& username, const string& password){
    auto it = find_if(users.begin(), users.end(), [&](const User& user){
        return user.username == username && user.password == password && !user.isAdmin;
    });
    return it != users.end();
}
