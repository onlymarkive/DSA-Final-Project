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

void addQuizQuestion(int quizId, const string& question, const string& answer) {
    questions.push_back({nextQuestionId++, quizId, question, answer});
}

void editQuizQuestion() {
    cout << "Available Questions:" << endl;
    for (const auto& question : questions) {
        cout << "ID: " << question.id << ", Quiz ID: " << question.quizId << ", Question: " << question.question << endl;
    }

    int questionId;
    cout << "Enter Question ID to edit: ";
    cin >> questionId;

    auto it = find_if(questions.begin(), questions.end(), [&](const Question& q) {
        return q.id == questionId;
    });

    if (it != questions.end()) {
        string newQuestion, newAnswer;
        cout << "Enter New Question: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        getline(cin, newQuestion);
        cout << "Enter New Answer: ";
        getline(cin, newAnswer);

        it->question = newQuestion;
        it->answer = newAnswer;
        cout << "Question ID " << questionId << " has been updated successfully." << endl;
    } else {
        cout << "Question ID " << questionId << " not found." << endl;
    }
}

void deleteQuizQuestion() {
    cout << "Available Questions:" << endl;
    for (const auto& question : questions) {
        cout << "ID: " << question.id << ", Quiz ID: " << question.quizId << ", Question: " << question.question << endl;
    }

    int questionId;
    cout << "Enter Question ID to delete: ";
    cin >> questionId;

    auto it = find_if(questions.begin(), questions.end(), [&](const Question& q) {
        return q.id == questionId;
    });

    if (it != questions.end()) {
        questions.erase(it);
        cout << "Question ID " << questionId << " has been deleted successfully." << endl;
    } else {
        cout << "Question ID " << questionId << " not found." << endl;
    }
}

void viewAllQuestions() {
    for (const auto& question : questions) {
        cout << "ID: " << question.id << ", Quiz ID: " << question.quizId << ", Question: " << question.question << ", Answer: " << question.answer << endl;
    }
}

void viewResultsByUser(const string& userID) {
    bool foundResults = false;
    for (const auto& result : results) {
        if (to_string(result.userId) == userID) {
            auto userIt = find_if(users.begin(), users.end(), [&](const User& user) {
                return user.id == result.userId;
            });
            if (userIt != users.end()) {
                cout << "User: " << userIt->username << ", Quiz ID: " << result.quizId << ", Score: " << result.score << ", Date: " << result.dateTaken << endl;
                foundResults = true;
            }
        }
    }
    if (!foundResults) {
        cout << "No results found for User ID " << userID << "." << endl;
    }
}

void viewResultsByQuiz(int quizId) {
    for (const auto& result : results) {
        if (result.quizId == quizId) {
            auto userIt = find_if(users.begin(), users.end(), [&](const User& user) {
                return user.id == result.userId;
            });
            string username = (userIt != users.end()) ? userIt->username : "Unknown";
            cout << "User: " << username << ", Score: " << result.score << ", Date: " << result.dateTaken << endl;
        }
    }
}
