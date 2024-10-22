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
    });
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

void takeQuiz(int quizId, int userId) {
    int score = 0;
    int totalQuestions = 0;

    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now_c));
    string dateStr(buffer);

    for (const auto& question : questions) {
        if (question.quizId == quizId) {
            cout << "+---------------------------------------+" << endl;
            cout << "| ************ Question " << question.id << " ************ |" << endl;
            cout << "+---------------------------------------+" << endl;
            cout << "| " << question.question << endl;
            cout << "+---------------------------------------+" << endl;

            string userAnswer;
            cout << "Your answer: ";
            cin >> userAnswer;

            if (userAnswer == question.answer) {
                score++;
            }
            totalQuestions++;
        }
    }

    results.push_back({userId, quizId, score, dateStr}); 
    cout << "+---------------------------------------+" << endl;
    cout << "| ************* Quiz Complete ********** |" << endl;
    cout << "+---------------------------------------+" << endl;
    cout << "Your score: " << score << "/" << totalQuestions << endl;
}

void generateReport() {
    for (const auto& result : results) {
        auto userIt = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.id == result.userId;
        });
        string username = (userIt != users.end()) ? userIt->username : "Unknown";

        cout << "User: " << username << ", Quiz ID: " << result.quizId << ", Score: " << result.score << ", Date: " << result.dateTaken << endl;
    }
}

void signUp(bool isAdmin) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    if (isUsernameExists(username)) {
        cout << "Username already exists. Please choose a different one." << endl;
        return;
    }

    cout << "Enter password: ";
    cin >> password;
    users.push_back({nextUserId++, username, password, isAdmin});
    cout << (isAdmin ? "Admin" : "User") << " account created successfully." << endl;
}

void resetPassword(int userId) {
    string newPassword;
    cout << "Enter new password: ";
    cin >> newPassword;

    auto it = find_if(users.begin(), users.end(), [&](const User& user) {
        return user.id == userId;
    });

    if (it != users.end()) {
        it->password = newPassword;
        cout << "Password reset successfully." << endl;
    } else {
        cout << "User not found." << endl;
    }
}

void handleAdminLogin() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (authenticateAdmin(username, password)) {
        int userId = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.username == username;
        })->id;

        while (true) {
            cout << "+----------------------------------------+" << endl;
            cout << "| ************** Admin Menu ************ |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << "| 1. Add Question                        |" << endl;
            cout << "| 2. Edit Question                       |" << endl;
            cout << "| 3. Delete Question                     |" << endl;
            cout << "| 4. View All Questions                  |" << endl;
            cout << "| 5. View Results by User                |" << endl;
            cout << "| 6. View Results by Quiz                |" << endl;
            cout << "| 7. Generate Report                     |" << endl;
            cout << "| 8. Logout                              |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << "Choose an option: ";

            int choice;
            while (!(cin >> choice) || (choice < ADD_QUESTION || choice > ADMIN_LOGOUT)) {
                cout << "Invalid option. Please enter a number between 1 and 8." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            switch (choice) {
                case ADD_QUESTION: {
                    int quizId;
                    string question, answer;
                    cout << "Enter Quiz ID: ";
                    while (!(cin >> quizId)) {
                        cout << "Invalid input. Please enter a valid Quiz ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter Question: ";
                    getline(cin, question);
                    cout << "Enter Answer: ";
                    getline(cin, answer);
                    addQuizQuestion(quizId, question, answer);
                    break;
                }
                case EDIT_QUESTION: {
                    editQuizQuestion();  
                    break;
                }
                case DELETE_QUESTION: {
                    deleteQuizQuestion(); 
                    break;
                }
                case VIEW_ALL_QUESTIONS:
                    viewAllQuestions();
                    break;
                case VIEW_RESULTS_BY_USER: {
                    string username;
                    cout << "Enter Username: ";
                    cin >> username;

                    auto userIt = find_if(users.begin(), users.end(), [&](const User& user) {
                        return user.username == username;
                    });

                    if (userIt != users.end()) {
                        viewResultsByUser(to_string(userIt->id)); 
                    } else {
                        cout << "User '" << username << "' not found." << endl;
                    }
                    break;
                }
                case VIEW_RESULTS_BY_QUIZ: {
                    int quizId;
                    cout << "Enter Quiz ID: ";
                    while (!(cin >> quizId)) {
                        cout << "Invalid input. Please enter a valid Quiz ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    viewResultsByQuiz(quizId);
                    break;
                }
                case GENERATE_REPORT:
                    generateReport();
                    break;
                case ADMIN_LOGOUT:
                    cout << "Logging out..." << endl;
                    return;
                default:
                    cout << "Invalid option. Please try again." << endl;
                    break;
            }
        }
    } else {
        cout << "Invalid username or password." << endl;
    }
}

void handleUserLogin() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (authenticateUser(username, password)) {
        int userId = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.username == username;
        })->id;

        while (true) {
            cout << "+----------------------------------------+" << endl;
            cout << "| ************** User Menu ************* |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << "| 1. Take Quiz                           |" << endl;
            cout << "| 2. View Scores                         |" << endl;
            cout << "| 3. Reset Password                      |" << endl;
            cout << "| 4. Logout                              |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << "Choose an option: ";

            int choice;
            while (!(cin >> choice) || (choice < TAKE_QUIZ || choice > USER_LOGOUT)) {
                cout << "Invalid option. Please enter a number between 1 and 4." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            switch (choice) {
                case TAKE_QUIZ: {
                    int quizId;
                    cout << "Enter Quiz ID: ";
                    while (!(cin >> quizId)) {
                        cout << "Invalid input. Please enter a valid Quiz ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    takeQuiz(quizId, userId);
                    break;
                }
                case VIEW_SCORES:
                    viewResultsByUser(to_string(userId));
                    break;
                case RESET_PASSWORD:
                    resetPassword(userId);
                    break;
                case USER_LOGOUT:
                    cout << "Logging out..." << endl;
                    return;
                default:
                    cout << "Invalid option. Please try again." << endl;
                    break;
            }
        }
    } else {
        cout << "Invalid username or password." << endl;
    }
}

int main() {
        cout << "+-----------------------------------------+" << endl;
        cout << "| ************** WELCOME TO ************* |" << endl;
        cout << "+-----------------------------------------+" << endl;
        cout << "       _______ ______  _____ _______ " << endl;
        cout << "      |__   __|  ____|/ ____|__   __|" << endl;
        cout << "         | |  | |__  | (___    | |   " << endl;
        cout << "         | |  |  __|  \\___ \\   | |   " << endl;
        cout << "         | |  | |____ ____) |  | |   " << endl;
        cout << "         |_|  |______|_____/   |_|   " << endl;
        cout << "   _____ ______ _   _ _____ _    _  _____ " << endl;
        cout << "  / ____|  ____| \\ | |_   _| |  | |/ ____|" << endl;
        cout << " | |  __| |__  |  \\| | | | | |  | | (___  " << endl;
        cout << " | | |_ |  __| | . ` | | | | |  | |\\___ \\ " << endl;
        cout << " | |__| | |____| |\\  |_| |_| |__| |____) |" << endl;
        cout << "  \\_____|______|_| \\_|_____|\\____/|_____/ " << endl;
        cout << "                                          " << endl;
    while (true) {
        cout << "+-----------------------------------------+" << endl;
        cout << "|        1. Admin Sign Up                 |" << endl;
        cout << "|        2. User Sign Up                  |" << endl;
        cout << "|        3. Admin Login                   |" << endl;
        cout << "|        4. User Login                    |" << endl;
        cout << "|        5. Exit                          |" << endl;
        cout << "+-----------------------------------------+" << endl;
        cout << "Choose an option: ";

        int choice;
        while (!(cin >> choice) || choice < SIGNUP_ADMIN || choice > EXIT) {
            cout << "Invalid option. Please enter a number between 1 and 5." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case SIGNUP_ADMIN:
                signUp(true);
                break;
            case SIGNUP_USER:
                signUp(false);
                break;
            case LOGIN_ADMIN:
                handleAdminLogin();
                break;
            case LOGIN_USER:
                handleUserLogin();
                break;
            case EXIT:
                cout << "Exiting the program..." << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }

    return 0;
}

