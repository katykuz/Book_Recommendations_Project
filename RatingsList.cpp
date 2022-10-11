//
// Created by evken on 10/8/2022.
//

#include "RatingsList.h"
#include <iostream>
#include <string>
#include <sstream>



//declare static integer for counting number of books
static int ratingsCount;

//constructor
RatingsList::RatingsList() {
//creating a 2D array
    const int ROW = 100; //rows = members
    const int COL = 100; //cols = ratingsArr
    rowMemMax = ROW;
    colBookMax = COL;
    int **ratingsArr;
    ratingsArr = new int *[rowMemMax];

//to assign each integer pointer an integer array, use for-loop
    for (int i = 0; i < rowMemMax; i++) {
        ratingsArr[i] = new int[colBookMax];
    }
}

//destructor
RatingsList::~RatingsList() { //when an object goes out of scope, the destructor is
    // called and the object is deleted (automatically)
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
//    list = new int[rowMemMax];

    // copy over elements (from obj)
//    for (int i = 0; i < rowMemMax; i++) {
//        for (int j = 0; i < colBookMax; j++)
//            list[i][j] = obj.list[rowMemMax][colBookMax];
}

//equals operator
//RatingsList& RatingsList::operator=(const RatingsList &obj) {
//    if (this != &obj) {     //checking if this has the same memory address as
//        // &obj because they would be the same thing
//        // deallocate memory
//        delete [] list; //this refers to the list that is calling the operator
//        //this is list1 in this case: list1 = list2
//
//        // assign numElements and capacity (from obj)
//        rowMemMax = obj.rowMemMax;
//        colBookMax = obj.colBookMax;
//        //^^ refers to list1's capacity
//        numRatings = obj.numRatings;
//
//        // allocate memory based on new capacity
//        list = new int[rowMemMax];
//
//        // copy over elements (from obj)
//        for (int i = 0; i < rowMemMax; i++)
//            list[i] = obj.list[i];
//    }
//    //dereferencing the pointer this
//    return *this;   //returns the contents of the pointer


//}

void RatingsList::add(int account, int bookISBN, int rating) {
    //check if the array is full
    if (account >= rowMemMax || bookISBN >= colBookMax)
        resize();                // resize doubles the size of the array

    //assign rating into array
    ratingsArr[account][bookISBN] = rating;

}

int RatingsList::getRating(int account, int isbn) {

    // return rating of book
    return ratingsArr[account][isbn];

}

int RatingsList::returnRatings(int account) const {

    for (int i = 0; i < colBookMax; i++) {
            if (!ratingsArr[account][i] == 0)
                // return string with ratings
                return ratingsArr[account][i];
    }
    // if not found, return -1
    return -1;
}

int RatingsList::getISBN(int account, int rating) {

    for (int i = 0; i < colBookMax; i++) {
        if (ratingsArr[account][i] == rating)
            // return string with ratings
            return i;
    }
    // if not found, return -1
    return -1;
}

bool RatingsList::empty() const {

    //returns true if number of elements is zero and array is empty
    return false;

}

int RatingsList::size() const {

    //returns number of elements in array
    return -1;

}


void RatingsList::resize() {
    // update capacity
    rowMemMax *= 2;     //doubles the value of capacity
    colBookMax *-2;

    // create a new array with new capacity
    int * tempArr = new int[rowMemMax];

    // copy contents of old array into new array
//    for (int i = 0; i < rowMemMax; i++)
//        tempArr[i] = ratingsArr[i];

    // delete old array
    delete [] ratingsArr;

    // reassign old array to new array
    //ratingsArr = tempArr;
}
