#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
using namespace std;
#include "Date.h"


class Entry {

private:
    int entryNumber;
    string title;
    string details;
    Date entryDate;
    Date dueDate;

public:
    //Getters
    int getEntryNumber(void){return entryNumber;}
    string getTitle(void){return title;} 
    string getDetails(void){return details;}
    Date getEntryDate(void){return entryDate;}
    Date getDueDate(void){return dueDate;}

    //Setters
    void setEntryNumber(int EntryNumber){entryNumber = EntryNumber;}
    void setTitle(string Title){title = Title;} 
    void setDetails(string Details){details = Details;}
    void setEntryDate(Date EntryDate){entryDate = EntryDate;}
    void setDueDate(Date DueDate){dueDate = DueDate;}


};
#endif