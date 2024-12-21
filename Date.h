#ifndef DATE_H
#define DATE_H


#include <iostream>
using namespace std;

class Date {
    private:
        int day;
        int month;
        int year;

    public:

        friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.day << "/" << date.month << "/" << date.year;
        return os;
        }    
        //Getters
        int getDay(void){return day;}
        int getMonth(void){return month;}
        int getYear(void){return year;}

        //Setters
        void setDay(int Day){day = Day;}
        void setMonth(int Month){month = Month;}
        void setYear(int Year){year = Year;}

        void display(void){
            cout<<day<<"/"<<month<<"/"<<year<<endl;
        }
};
#endif