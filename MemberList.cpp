// Ekaterina Kuznetsova
// MemberList.h
// October 12, 2022
// Purpose: Implementation for className described in MemberList.h

#include <iostream>
#include "MemberList.h"
#include <string>
#include <sstream>


//constructor
MemberList::MemberList() {
    const int CAP = 100;
    list = new Member[CAP];
    capacity = CAP;
    numMembers = 0;
    memberCount = 1;
}

//destructor
MemberList::~MemberList() { //when an object goes out of scope, the destructor is
    // called and the object is deleted (automatically)
    delete [] list;
}

//copy constructor
MemberList::MemberList(const MemberList &obj) {
    // assign numElements and capacity (from obj)
    capacity = obj.capacity;
    numMembers = obj.numMembers;

    // allocate memory based on new capacity
    list = new Member[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numMembers; i++)
        list[i] = obj.list[i];
}

//equals operator
MemberList& MemberList::operator=(const MemberList &obj) {
    if (this != &obj) {     //checking if this has the same memory address as
        // &obj because they would be the same thing
        // deallocate memory
        delete [] list; //this refers to the list that is calling the operator
        //this is list1 in this case: list1 = list2

        // assign numElements and capacity (from obj)
        capacity = obj.capacity;
        //^^ refers to list1's capacity
        numMembers = obj.numMembers;

        // allocate memory based on new capacity
        list = new Member[capacity];

        // copy over elements (from obj)
        for (int i = 0; i < numMembers; i++)
            list[i] = obj.list[i];
    }
    //dereferencing the pointer this
    return *this;   //returns the contents of the pointer - which is an IntList
}

//method for adding members to array
void MemberList::add(string name) {
    if (numMembers >= capacity)     //check if the array is full
        resize();                   // resize doubles the size of the array

    //assign the new member an account number based on how many members in array
    list[numMembers].account = memberCount;

    //increment the count of members
    memberCount++;

    //assign the name attribute based on method input
    list[numMembers].name = name;

    //increment the number of elements for array indexing
    numMembers++;
}

//method for adding members to array by taking in name of member from user
string MemberList::addManually(string name) {
    if (numMembers >= capacity) //check if the array is full
        resize();                // resize doubles the size of the array

    //assign the new member an account number based on how many members in array
    list[numMembers].account = memberCount;

    //increment the count of members
    list[numMembers].name = name;

    //increment the number of elements for array indexing
    numMembers++;

    //create string that states new member's account number
    string memAddConfirmation = name + "'s account number is: " +
            ::to_string(memberCount);

    //increment count of members
    memberCount++;

    //return string
    return memAddConfirmation;
}

//Method takes in the account number of the member and returns true if it is
//in the array
bool MemberList::find(int account) const {

    //to see if member account is present in array, loop through array to find
    // element
    for (int i = 0; i < numMembers; i++) {
        if (list[i].account == (account))
            //return true
            return true;
    }
    //if not found, return false
    return false;
}

//Method returns the name of the member when provided the account number
string MemberList::getNameOfMember(int account) const {

    //back up variable in case this function is reached with invalid input
    string noName = "No one";

    //adjust for difference between account number and index
    int el = account - 1;

    //if the account isn't in the list, return no name
    if (!find(account))
        return noName;
    else
        //otherwise return the name in the element
        return list[el].name;
}

//save the account number of the logged in member
void MemberList::saveLoggedInMem(int account) {

    //assign the variable to the account number
    loggedInAccntNum = account;

}

//get the account number of the logged in member
int MemberList::getLoggedInMem(){

    //return the int variable representing the account number
    return loggedInAccntNum;

}

//returns the number of members that have been added to the list
int MemberList::numberOfMembers() const{

    //returns number of books added
    return memberCount - 1;
}

//returns true if there are no members
bool MemberList::empty() const {

    //returns true if number of elements is zero and array is empty
    return numMembers == 0;

}

//returns the number of elements
int MemberList::size() const {

    //returns number of elements in array
    return numMembers;

}


//use to_string to pass needed strings to be printed into driver file
string MemberList::to_string() const {

    //declare stringstream
    stringstream ss;

    //pass number of books into stringsream
    ss << "Number of books: " << memberCount << "\n" << endl;

    //go through array and pass each element struct into ss
    for (int i = 0; i < numMembers; i++)

        //push into ss attributes with formatting
        ss << list[i].account << ", " << list[i].name << ", " << endl;

    //return the string
    return ss.str();

}

//doubles the capacity of the member array
void MemberList::resize() {
    // update capacity
    capacity *= 2;              //doubles the value of capacity

    // create a new array with new capacity
    Member * tempArr = new Member[capacity];

    // copy contents of old array into new array
    for (int i = 0; i < numMembers; i++)
        tempArr[i] = list[i];

    // delete old array
    delete [] list;

    // reassign old array to new array
    list = tempArr;
}
