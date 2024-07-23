# ✨Test Genius: Interactive Online Quiz and Exam System✨

## Table of Contents 📚
1. [Project Introduction](#project-introduction)
2. [Objectives](#objectives)
3. [Project Description](#project-description)
   - [Scope](#scope)
   - [Limitations and Constraints](#limitations-and-constraints)
   - [Features](#features)
   - [Problem it Solves](#problem-it-solves)
   - [Sustainable Development Goal](#sustainable-development-goal)
4. [Database Management System](#database-management-system)
5. [Technology Stacks](#technology-stacks)
6. [Contributors, Course, and Course Facilitator](#contributors-course-and-course-facilitator)

## Project Introduction 🚀
The **Interactive Online Quiz and Exam System (IOQES)** is designed to facilitate the creation, management, and administration of quizzes in educational and organizational settings. It provides robust features for both administrators and users to interact with quiz content efficiently and effectively. The purpose of IOQES is to streamline the process of conducting quizzes, making it easier for educators, trainers, and organizations to administer assessments, evaluate knowledge, and provide immediate feedback. The objectives include enhancing user engagement, ensuring secure access and data management, and supporting sustainable educational practices.

## Objectives 💡
- Provide an interactive platform for administering and taking quizzes.
- Allow administrators to manage quiz questions and view results.
- Enable users to take quizzes and view their scores.
- Ensure secure login and authentication for both users and administrators.

## Project Description 👾

### Scope
IOQES enables administrators to create and manage quizzes, including adding, editing, and deleting questions. Administrators can also manage user accounts, view detailed results by user or quiz, and generate comprehensive reports. Users can take quizzes, view immediate feedback on their answers, and track their historical scores over time.

### Limitations and Constraints
- **Concurrent Access**: While the system allows multiple administrators and users, it may face limitations in handling a large number of simultaneous quiz sessions and administrative actions efficiently.
- **User Role Management**: The current implementation does not include advanced role-based access control beyond basic administrator and user roles.
- **Question Types**: The system is designed to handle only text-based and multiple-choice questions, without support for other types of questions or interactive elements.
- **Data Persistence**: The current implementation does not use a database system like SQLite for data persistence, relying on in-memory storage, which means data will not persist between program executions.

### Features
- **Admin Section**:
   - Add, edit, or delete quiz questions.
   - Manage user accounts and reset passwords.
   - View detailed quiz results by user or quiz.
   - Generate comprehensive reports on quiz results.
- **User Section**:
   - Take quizzes and receive immediate feedback.
   - View personal scores and track historical performance.
- **Security**:
   - Secure login system with password encryption for both administrators and users.
- **Reporting**:
   - Generate and review detailed reports on quiz results for both administrative analysis and evaluation.

### Problem it Solves
IOQES simplifies the management and administration of quizzes by providing an intuitive interface for administrators and users. It enhances the efficiency of quiz operations and supports sustainable educational practices.

### Sustainable Development Goal
This project aligns with **Goal 4: Quality Education** of the United Nations Sustainable Development Goals (SDGs). It aims to provide inclusive and equitable quality education and promote lifelong learning opportunities for all.

## Database Management System 📥
The current implementation does not utilize an external database management system such as SQLite. All data is stored in memory during the program's execution and will not persist once the program is terminated.

## Technology Stacks ⚙️ 
- **Programming Language**: C++
- **Libraries**: Standard Template Library (STL)
- **Development Environment**: Any C++ compiler (e.g., GCC, Clang, MSVC)
- **Encryption**: Basic password encryption methods within C++

## Contributors, Course, and Course Facilitator 👷‍ 
 
| Name                         | Role       | Email                         |
|------------------------------|------------|-------------------------------|
| [Lacerna, James Louie](https://github.com/kenwichu) | Developer  | 23-05991@g.batstate-u.edu.ph    |
| [Rectin, Marielle](https://github.com/onlymarkive)   | Developer  | 23-06330@g.batstate-u.edu.ph    |
| [Rivera, Irish](https://github.com/kelleeerrrr)      | Developer  | 23-00679@g.batstate-u.edu.ph  |
 
### Course
Cs 131 - Data Structure and Analysis
 
### Course Facilitator
Ms. Fatima Marie Agdon, MSCS

  

