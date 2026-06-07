Student Learning Management System (C++)

Overview 
This is a console-based Student Learning Management System developed in C++.
It allows admins and students to interact with educational content stored in text files. The system supports authentication, file handling, topic management, and a simple Q&A history system.

Features:

Admin Features
Login system with role-based access
Add new topics
Update existing topics
Delete topics
Search topics
Display all topics
Subject selection (PF, OOP, DSA, DLD, Ideology)

Student Features
Login system with role-based access
Select subject
View sorted topic list (Alphabetical order)
Ask questions based on topics
View answer history
View last answered response

Authentication System:
Sign up with username, password, and role
Login validation using file storage
Forgot password feature
Password length restriction (8 characters)

File Handling:
Stores users in users.txt
Stores subject data in .txt files:
PF.txt
OOP.txt
DSA.txt
DLD.txt
Ideology.txt
Supports:
Load
Save
Append
Update
Delete

Data Structures Used
Arrays (for storing topics and file lines)
Queue (for storing answer history)
File handling (ifstream, ofstream, fstream)
Manual sorting (Insertion Sort)
Concepts Implemented

Object-Oriented Programming (OOP)
File Handling in C++
Encapsulation (classes for Admin, Student, Auth, File)
Data Structures (Queue, Arrays)
String manipulation without built-in helpers
Searching and Sorting algorithms

Project Structure
Student System/
│
├── dsaproject.cpp
├── users.txt
├── PF.txt
├── OOP.txt
├── DSA.txt
├── DLD.txt
├── Ideology.txt

Author
Developed by: Fatima Tanveer
Project Type: Academic C++ OOP + File Handling Project
