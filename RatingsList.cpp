// Ekaterina Kuznetsova
// RatingsList.h
// October 12, 2022
// Purpose: Implementation for className described in RatingsList.h

#include "RatingsList.h"
#include <iostream>
#include <string>
#include <sstream>


//declare static integer for counting number of total ratings
static int ratingsCount;

//declare static int for counting the number of members in this 2D array
static int ratingsMembers;

//constructor
RatingsList::RatingsList() {

//creating a 2D array
    const int ROW = 100; //rows = members
    const int COL = 100; //cols = ratingsArr
    rowMemMax = ROW;
    colBookMax = COL;
    this->ratingsArr = new int *[rowMemMax];

//to assign each integer pointer an integer array, use for-loop
    for (int i = 0; i < rowMemMax; i++) {
        this->ratingsArr[i] = new int[colBookMax];
    }
}

//destructor
RatingsList::~RatingsList() {

    //when an object goes out of scope, the destructor
    // is called and the object is deleted (automatically)
    for (int i = 0; i < rowMemMax; i++)
        delete [] ratingsArr[i];
    delete [] ratingsArr;
}

//copy constructor
RatingsList::RatingsList(const RatingsList &obj) {

    // assign numElements and capacity (from obj)
    rowMemMax = obj.rowMemMax;
    colBookMax = obj.colBookMax;
    numRatings = obj.numRatings;

    // allocate memory based on new capacity
    ratingsArr = new int *[rowMemMax];

    // copy over elements (from obj)
    for (int i = 0; i < rowMemMax; i++) {
        for (int j = 0; i < colBookMax; j++)
            ratingsArr[i][j] = obj.ratingsArr[rowMemMax][colBookMax];
    }
}

//equals operator
RatingsList& RatingsList::operator=(const RatingsList &obj) {

    if (this != &obj) {     //checking if this has the same memory address as
        // &obj because they would be the same thing
        // deallocate memory
        delete [] ratingsArr; //this refers to the ratingsArr that is calling the operator
        //this is list1 in this case: list1 = list2

        // assign numElements and capacity (from obj)
        rowMemMax = obj.rowMemMax;
        colBookMax = obj.colBookMax;
        //^^ refers to list1's capacity
        numRatings = obj.numRatings;

        // allocate memory based on new capacity
        ratingsArr = new int *[rowMemMax];

        // copy over elements (from obj)
        for (int i = 0; i < rowMemMax; i++) {
            for (int j = 0; i < colBookMax; j++)
                ratingsArr[i][j] = obj.ratingsArr[rowMemMax][colBookMax];
            }
    }
    //dereferencing the pointer this
    return *this;   //returns the contents of the pointer

}

//adds a rating to the array based on the user account number, book ISBN, and
// the rating value
void RatingsList::add(int account, int bookISBN, int rating) {

    //check if the array is full
    if (account >= rowMemMax || bookISBN >= colBookMax)
        resize();                // resize doubles the size of the array

    //assign rating into array
    ratingsArr[account][bookISBN] = rating;

    //increment the count of total ratings
    ratingsCount++;
    ratingsMembers = account;

}

//adds a rating to the array based on the user account number, book ISBN, and
// the rating value
void RatingsList::addMember() {

    //check if the array is full
    if (ratingsMembers >= rowMemMax)
        resize();                // resize doubles the size of the array

    //increment number of members
    ratingsMembers++;

    //create vector for new member
    for (int i = 0; i < rowMemMax; i++) {
        ratingsArr[ratingsMembers][i] = 0;
    }

}

//Method returns a rating based on account number and book ISBN
int RatingsList::getRating(int account, int isbn) {

    // return rating of book
    return ratingsArr[account][isbn];

}

//Method returns integer value based on whether an account's rating list is
// full, empty, or neither
int RatingsList::emptyFullVector(int account, int bookNum) const {

    int zeros = 0;
    int numbers = 0;

    for (int i = 0; i < bookNum; i++) {
        if (ratingsArr[account][i] == 0) {
            //increment number of zero's
            zeros++;
        } else if (ratingsArr[account][i] != 0) {
            //increment number of not zeros
            numbers++;
        }
    }

    //if the list is empty, return -3
    if (zeros == bookNum) {
        return -3;
    //if the list is full, return -2
    } else if (numbers == bookNum) {
        return -2;
    //if the list is neither, return -1
    } else {
        return -1;
    }


}

//Method returns true if the entire 2D array is empty/0
bool RatingsList::empty() const {

    //returns true if number of elements is zero and array is empty
    if (ratingsCount == 0) {
        return true;
    }

    return false;

}

//Method returns the number of ratings in the whole 2D array
int RatingsList::size() const {

    //returns number of elements in array
    return ratingsCount;

}


void RatingsList::resize() {
    // update capacity
    rowMemMax *= 2;     //doubles the value of capacity
    colBookMax *=2 ;

    // create a new array with new capacity

    int** tempArr = new int *[rowMemMax];

    // copy contents of old array into new array
    for (int i = 0; i < rowMemMax; i++)
        for (int j = 0; j < colBookMax; i++) {
            tempArr[i][j] = ratingsArr[i][j];
        }

    // delete old array
    delete [] ratingsArr;

    // reassign old array to new array
    ratingsArr = tempArr;
}