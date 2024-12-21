#ifndef USER_H
#define USER_H


#include <iostream>
#include "Date.h"
using namespace std;


class User {
    private:
        string firstName;
        string lastName;
        string userName;
        string emailAddress;
        string password;
        string date;

    public:
        //Getters
        string getFirstName(void){return firstName;}
        string getLastName(void){return lastName;}
        string getUserName(void){return userName;}
        string getEmailAddress(void){return emailAddress;}
        string getPassword(void){return password;}
        string getDate(void){return date;}


        //Setters
        void setFirstName(string FirstName){firstName = FirstName;}
        void setLastName(string LastName){lastName = LastName;}
        void setUserName(string UserName){userName = UserName;}
        void setEmailAddress(string EmailAddress){emailAddress = EmailAddress;}
        void setPassword(string Password){password = Password;}
        void setDate(string Date){date = Date;}


};
#endif