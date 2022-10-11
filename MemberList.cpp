//
// Created by evken on 10/5/2022.
//

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

void MemberList::add(string name) {
    if (numMembers >= capacity) //check if the array is full
        resize();                // resize doubles the size of the array

    //declare string  to pass sections of the element string into struct
    //string str;

    //
    list[numMembers].account = memberCount;

    memberCount++;

    //push el string into istringstream to be able to parse it
    //istringstream ss(el);

    //assign first section of string to author
    //getline(ss, str, ',');
    list[numMembers].name = name;

    //increment the number of elements for array indexing
    numMembers++;
}

string MemberList::addManually(string name) {
    if (numMembers >= capacity) //check if the array is full
        resize();                // resize doubles the size of the array

    //declare string  to pass sections of the element string into struct
    //string str;

    //
    list[numMembers].account = memberCount;

    //push el string into istringstream to be able to parse it
    //istringstream ss(el);

    //assign first section of string to author
    //getline(ss, str, ',');
    list[numMembers].name = name;

    //increment the number of elements for array indexing
    numMembers++;

    string memAddConfirmation = name + "'s account number is: " +
            ::to_string(memberCount);

    memberCount++;

    return memAddConfirmation;
}

bool MemberList::find(int el) const {

    //to see if member account is present in array, loop through array to find
    // element
    for (int i = 0; i < numMembers; i++) {
        if (list[i].account == (el))
            // return true
            return true;
    }
    // if not found, return false
    return false;
}

string MemberList::getNameOfMember(int el) const {

    string noName = "No one";
    int num = el - 1;

    if (el == -1)
        return noName;
    else
        return list[num].name;

}

void MemberList::saveLoggedInMem(int acctNum) {

    loggedInAccntNum = acctNum;

}

int MemberList::getLoggedInMem(){

    return loggedInAccntNum;

}

int MemberList::numberOfMembers() const{

    //returns number of books added
    return memberCount - 1;
}

bool MemberList::empty() const {

    //returns true if number of elements is zero and array is empty
    return numMembers == 0;

}

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
