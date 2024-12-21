#ifndef TODO_H
#define TODO_H

#include "Options.h"
class ToDo {
    Options options;  

public:
void ToDorun() {
    int option;
    while (true) {
    cout << "Welcome To My To-Do Application\n"
         << "Options: \n"
         << "1. Account Maintenance \n"
         << "2. Entry Maintenance\n"
         << "3. Exit\n"
         << endl;
   
        cin >> option;

        switch (option) {
            case 1: {
                int accountOption;
                 while (true) {
                cout << "Account Maintenance Menu\n"
                     << "1. Create an Account\n"
                     << "2. Update an Account\n"
                     << "3. Delete an Account\n"
                     << "4. Exit\n"
                     << endl;
               
                    cin >> accountOption;

                    switch (accountOption) {
                        case 1:
                            options.createAccount();
                            break;
                        case 2:
                            options.updateAccount();
                            break;
                        case 3:
                            options.deleteAccount();
                            break;
                        case 4:
                            cout << "Returning to the main menu...\n";
                            break;  // Back to the main menu
                        default:
                            cout << "Invalid Option" << endl;
                    }
                    if (accountOption == 4) break; 
                }
                break;
            }
            case 2: {
                cout << "Please enter the USERNAME for the account you'd like to make an ENTRY to:" << endl;
                string username, password;
                cin >> username;

                cout << "Please enter your password:" << endl;
                cin >> password;
                
                ifstream myFile;
                myFile.open("users.txt", ios::in);

                if (!myFile) {
                    cout << "Failed to open the file." << endl;
                    return;
                }                
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
                        break;
                    } 
                }
                if (!accountFound) {
                cout << "Incorrect username or password. Access Declined." << endl;
                break; }

                int entryOption;
                while (true) {
                    cout << "Entry Maintenance Menu\n"
                         << "1. Add Entry\n"
                         << "2. Update Entry\n"
                         << "3. Delete Entry\n"
                         << "4. View All Entries\n"
                         << "5. Exit\n"
                         << endl;
    
                    cin >> entryOption;
    
                    switch (entryOption) {
                        case 1:
                            options.addEntry();
                            break;
                        case 2:
                            options.updateEntry();
                            break;
                        case 3:
                            options.deleteEntry();
                            break;
                        case 4:
                            options.viewAllEntry();
                            break;
                        case 5:
                            cout << "Returning to the main menu...\n";
                            break;   // Back to the main menu
                        default:
                            cout << "Invalid Option" << endl;
                    }if (entryOption == 5) break; 
                }
                    break;
            }
            case 3:
                cout << "Thank you for using our program" << endl;
                return;  // Exit the application
            default:
                cout << "Invalid Option" << endl;
        }
    }
};
    
};
#endif
