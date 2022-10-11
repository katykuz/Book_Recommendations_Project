//
// Created by evken on 10/5/2022.
//

#ifndef PROJECT1_MEMBERLIST_H
#define PROJECT1_MEMBERLIST_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MemberList {

public:

    MemberList();             // Constructor
    ~MemberList();                // Destructor
    MemberList(const MemberList &);               // Copy constructor
    MemberList &operator=(const MemberList &);    // Overloaded = operator
    void add(string);             // add element to array
    string addManually(string name); //adding member manually
    bool find(int) const;        // find element in array; return true if found
    bool empty() const;         // determines if list is empty or not
    int size() const;           // number of elements in array
    int numberOfMembers() const;
    string getNameOfMember(int el) const;
    void saveLoggedInMem(int acctNum);     //assign logged in member
    int getLoggedInMem();           //retrieve accnt num of logged in member
    string to_string() const;   // returns string representation of
    // the MemberList class

private:

    //Book struct with attributes
    struct Member {
        int account;             //account number to track members
        string name;             //name of member

    };

    Member *list;             // Pointer to the array
    int capacity;            // capacity of array
    int numMembers;         // Number of elements for array indexing
    int memberCount;        //number of members added
    int loggedInAccntNum;   //currently logged in member account number
    void resize();          // resize array (when full)

};

#endif //PROJECT1_MEMBERLIST_H