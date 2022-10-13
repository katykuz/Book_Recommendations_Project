// Ekaterina Kuznetsova
// MemberList.h
// October 12, 2022
// Purpose: This class creates a dynamic array with each element consisting
// of a Member struct, which is defined in the private section of this class.
// The class also provides functions needed to modify the array and to gather
// information from the array.

#ifndef PROJECT1_MEMBERLIST_H
#define PROJECT1_MEMBERLIST_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MemberList {

public:

    MemberList();                                   // Constructor
    ~MemberList();                                  // Destructor
    MemberList(const MemberList &);                 // Copy constructor
    MemberList &operator=(const MemberList &);      // Overloaded = operator
    void add(string);                               //add element to array
    string addManually(string name);                //adding member manually
    bool find(int) const;        //find element in array; return true if found
    bool empty() const;          //determines if list is empty or not
    int size() const;            //returns number of elements in array
    int numberOfMembers() const;            //returns number of members
    string getNameOfMember(int el) const;   //returns name of member
    void saveLoggedInMem(int acctNum);      //tracks/assigns logged in member
    int getLoggedInMem();                   //return accnt # of logged in mem
    string to_string() const;               // returns string representation of
                                            // the MemberList class

private:

    //Book struct with attributes
    struct Member {
        int account;             //account number to track members
        string name;             //name of member

    };

    Member *list;             // Pointer to the array
    int capacity;             // capacity of array
    int numMembers;           // Number of elements for array indexing
    int memberCount;          //number of members added
    int loggedInAccntNum;     //currently logged in member account number
    void resize();            // resize array (when full)

};

#endif //PROJECT1_MEMBERLIST_H