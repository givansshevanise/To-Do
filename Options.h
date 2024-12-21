// Options.h
#ifndef OPTIONS_H
#define OPTIONS_H
#include <iostream>
#include <regex>
#include "User.h"
#include "Date.h"
#include "Entry.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Options {
    User currentUser;
    Entry currentEntry;

public:
    void createAccount() {
        cout << "Thank You For Selecting Our To-Do Application\n\n";
        cout << "Please Enter The Required Information" << endl;

        string firstName, lastName, userName, emailAddress, password;

        cout << "First Name: ";
        cin >> firstName;

        cout << "Last Name: ";
        cin >> lastName;

        cout << "UserName: ";
        cin >> userName;

        cout << "Email Address: ";
        cin >> emailAddress;

        if (isValid(emailAddress)) {
            cout << emailAddress << " is valid." << endl;
        } else {
            cout << emailAddress << " is invalid. Please try again." << endl;
            return;
        }

        cout << "Password (must be at least 8 characters): ";
        cin >> password;

        if (password.length() < 8) {
            cout << "Your password must have at least 8 characters." << endl;
            return;
        }

        fstream myFile;
        myFile.open("users.txt", ios::out | ios::app);

        if (!myFile) {
            cout << "Failed to open the file." << endl;
            return;
        }

        currentUser.setFirstName(firstName);
        currentUser.setLastName(lastName);
        currentUser.setUserName(userName);
        currentUser.setEmailAddress(emailAddress);
        currentUser.setPassword(password);

        myFile << currentUser.getFirstName() << ","
               << currentUser.getLastName() << ","
               << currentUser.getUserName() << ","
               << currentUser.getEmailAddress() << ","
               << currentUser.getPassword() << "\n";
        
        myFile.flush();

        if (myFile.fail()) {
            cout << "Error writing to file." << endl;
        } else {
            cout << "Account created successfully!" << endl;
        }
    
        myFile.close();  
    }

    void updateAccount() {
        cout << "Update Menu\nPlease enter your USERNAME to update: ";
        string username, password;
        cin >> username;

        cout << "Please enter your password: ";
        cin >> password;

        fstream myFile("users.txt", ios::in);
        if (!myFile) {
            cout << "Failed to open the file." << endl;
            return;
        }

        vector<string> users;
        string line;
        bool accountFound = false;

        while (getline(myFile, line)) {
            stringstream ss(line);
            string firstName, lastName, userName, email, pass;
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, userName, ',');
            getline(ss, email, ',');
            getline(ss, pass);

            if (userName == username && pass == password) {
                accountFound = true;

                cout << "Enter New First Name: ";
                cin >> firstName;

                cout << "Enter New Last Name: ";
                cin >> lastName;

                cout << "Enter New UserName: ";
                cin >> userName;

                cout << "Enter New Email Address: ";
                cin >> email;
                if (!isValid(email)) {
                    cout << "Invalid email format. Update canceled." << endl;
                    return;
                }

                cout << "Enter New Password (8+ characters): ";
                cin >> pass;
                if (pass.length() < 8) {
                    cout << "Password too short. Update canceled." << endl;
                    return;
                }

                line = firstName + "," + lastName + "," + userName + "," + email + "," + pass;
                cout << "Account updated successfully!" << endl;
            }
            users.push_back(line);
        }
        myFile.close();

        if (!accountFound) {
            cout << "Invalid username or password." << endl;
            return;
        }

        myFile.open("users.txt", ios::out);
        for (const string &user : users) {
            myFile << user << "\n";
        }
        myFile.close();
    }

    void deleteAccount() {
        cout << "Delete Menu\nPlease enter your USERNAME to delete: ";
        string username, password;
        cin >> username;

        cout << "Please enter your password: ";
        cin >> password;

        fstream myFile("users.txt", ios::in);
        if (!myFile) {
            cout << "Failed to open the file." << endl;
            return;
        }

        vector<string> users;
        string line;
        bool accountDeleted = false;

        while (getline(myFile, line)) {
            stringstream ss(line);
            string firstName, lastName, userName, email, pass;
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, userName, ',');
            getline(ss, email, ',');
            getline(ss, pass);

            if (userName == username && pass == password) {
                accountDeleted = true;
                cout << "Are you sure you want to delete your account? (yes/no): ";
                string confirmation;
                cin >> confirmation;

                if (confirmation == "yes") {
                    cout << "Account deleted successfully." << endl;
                    continue;
                } else {
                    cout << "Account deletion canceled." << endl;
                    users.push_back(line);
                }
            } else {
                users.push_back(line);
            }
        }
        myFile.close();

        if (!accountDeleted) {
            cout << "Invalid username or password. Deletion failed." << endl;
            return;
        }

        myFile.open("users.txt", ios::out);
        for (const string &user : users) {
            myFile << user << "\n";
        }
        myFile.close();
    }

    void addEntry() {
        fstream myFile;
        myFile.open("to-do.txt", ios::app);

        if (!myFile) {
            cout << "Failed to open the file." << endl;
            return;
        }

        int day, month, year, entryNumber;
        string title, details;

        cout << "ENTRY ADDITION MENU\n"
             << "Enter Entry Date\n--------------" << endl;

        if (!getDate(day, month, year)) return;

        Date entryDate;
        entryDate.setDay(day);
        entryDate.setMonth(month);
        entryDate.setYear(year);
        currentEntry.setEntryDate(entryDate);

        cout << "Enter Due Date\n--------------" << endl;

        if (!getDate(day, month, year)) return;

        Date dueDate;
        dueDate.setDay(day);
        dueDate.setMonth(month);
        dueDate.setYear(year);
        currentEntry.setDueDate(dueDate);

        cout << "Please enter your Entry Number: ";
        cin >> entryNumber;
        currentEntry.setEntryNumber(entryNumber);

        cin.ignore();
        cout << "Enter To-Do Title: ";
        getline(cin, title);
        currentEntry.setTitle(title);

        cout << "Enter Details: ";
        getline(cin, details);
        currentEntry.setDetails(details);

        myFile << currentEntry.getDueDate() << ","
               << currentEntry.getEntryDate() << ","
               << currentEntry.getEntryNumber() << ","
               << currentEntry.getTitle() << ","
               << currentEntry.getDetails() << "\n";
        cout << "Entry added successfully!" << endl;
        myFile.close();
    }

    void updateEntry() {
        fstream myFile;
        myFile.open("to-do.txt", ios::in);

        if (!myFile) {
            cout << "Failed to open the file." << endl;
            return;
        }

        int targetEntryNumber;
        cout << "ENTRY UPDATE MENU\n"
             << "Please enter your entry number to update: ";
        cin >> targetEntryNumber;

        vector<string> entries;
        string line;
        bool entryFound = false;

        while (getline(myFile, line)) {
            stringstream ss(line);
            string dueDate, entryDate, entryNumStr, title, details;
            
            getline(ss, dueDate, ',');
            getline(ss, entryDate, ',');
            getline(ss, entryNumStr, ',');
            getline(ss, title, ',');
            getline(ss, details);

            int currentEntryNum = stoi(entryNumStr);

            if (currentEntryNum == targetEntryNumber) {
                entryFound = true;
                continue; // Skip adding the old entry
            }
            entries.push_back(line);
        }
        myFile.close();

        if (!entryFound) {
            cout << "Entry not found." << endl;
            return;
        }

        // Get new entry details
        int day, month, year;
        string title, details;

        cout << "Enter New Entry Date\n--------------" << endl;
        if (!getDate(day, month, year)) return;

        Date entryDate;
        entryDate.setDay(day);
        entryDate.setMonth(month);
        entryDate.setYear(year);
        currentEntry.setEntryDate(entryDate);

        cout << "Enter New Due Date\n--------------" << endl;
        if (!getDate(day, month, year)) return;

        Date dueDate;
        dueDate.setDay(day);
        dueDate.setMonth(month);
        dueDate.setYear(year);
        currentEntry.setDueDate(dueDate);

        currentEntry.setEntryNumber(targetEntryNumber);

        cin.ignore();
        cout << "Enter New To-Do Title: ";
        getline(cin, title);
        currentEntry.setTitle(title);

        cout << "Enter New Details: ";
        getline(cin, details);
        currentEntry.setDetails(details);

        // Write back all entries including the updated one
        myFile.open("to-do.txt", ios::out);
        for (const string &entry : entries) {
            myFile << entry << "\n";
        }
        
        // Add the updated entry
        myFile << currentEntry.getDueDate() << ","
               << currentEntry.getEntryDate() << ","
               << currentEntry.getEntryNumber() << ","
               << currentEntry.getTitle() << ","
               << currentEntry.getDetails() << "\n";

        cout << "Entry updated successfully!" << endl;
        myFile.close();
    }

    void deleteEntry() {
        int deleteEntry;
        cout << "Welcome To The Deletion Menu" << endl;
        cout << "Enter the entryNumber of the To-Do you would like to delete: " << endl;
        cin >> deleteEntry;

        fstream myFile;
        myFile.open("to-do.txt", ios::in);

        if (!myFile) {
            cout << "Failed to open the file." << endl;
            return;
        }

        vector<string> fileLines;
        string line;
        bool entryFound = false;

        while (getline(myFile, line)) {
            stringstream ss(line);
            string dueDate, entryDate, entryNumStr, title, details;

            getline(ss, dueDate, ',');
            getline(ss, entryDate, ',');
            getline(ss, entryNumStr, ',');
            getline(ss, title, ',');
            getline(ss, details);

            int entryNum = stoi(entryNumStr);

            if (deleteEntry == entryNum) {
                entryFound = true;
                continue;  // Skip this entry to delete it
            }
            fileLines.push_back(line);
        }
        myFile.close();

        if (!entryFound) {
            cout << "Entry not found." << endl;
            return;
        }

        myFile.open("to-do.txt", ios::out);
        for (const string &fileLine : fileLines) {
            myFile << fileLine << "\n";
        }
        myFile.close();
        cout << "Entry deleted successfully." << endl;
    }

    void viewAllEntry() {
        cout << "Welcome To Your To-Do List" << endl;
        cout << "----------------------------------------" << endl;
        
        fstream myFile;
        myFile.open("to-do.txt", ios::in);

        if (!myFile) {
            cout << "Failed to open the file." << endl;
            return;
        }

        string line;
        bool hasEntries = false;
        
        while (getline(myFile, line)) {
            hasEntries = true;
            stringstream ss(line);
            string dueDate, entryDate, entryNumStr, title, details;

            getline(ss, dueDate, ',');
            getline(ss, entryDate, ',');
            getline(ss, entryNumStr, ',');
            getline(ss, title, ',');
            getline(ss, details);

            cout << "Entry Number: " << entryNumStr << endl;
            cout << "Title: " << title << endl;
            cout << "Details: " << details << endl;
            cout << "Entry Date: " << entryDate << endl;
            cout << "Due Date: " << dueDate << endl;
            cout << "----------------------------------------" << endl;
        }

        if (!hasEntries) {
            cout << "No entries found." << endl;
        }

        myFile.close();
    }

private:
    bool isValid(const string &emailAddress) {
        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(emailAddress, pattern);
    }

    bool getDate(int &day, int &month, int &year) {
        cout << "Enter Day: ";
        cin >> day;
        if (day <= 0 || day > 31) {
            cout << "Select a day between 1 and 31." << endl;
            return false;
        }

        cout << "Enter Month: ";
        cin >> month;
        if (month <= 0 || month > 12) {
            cout << "Select a month between 1 and 12." << endl;
            return false;
        }

        cout << "Enter Year: ";
        cin >> year;
        if (year <= 2000 || year > 2030) {
            cout << "Select a year between 2000 and 2030." << endl;
            return false;
        }

        return true;
    }
};

#endif