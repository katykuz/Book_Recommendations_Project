// Ekaterina Kuznetsova
// RatingsList.h
// October 12, 2022
// Purpose: This class creates a dynamic 2D array that holds a member's
// ratings of books. The class provides functions needed to modify the array
// and to gather information from the array.

#ifndef PROJECT1_RATINGSLIST_H
#define PROJECT1_RATINGSLIST_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class RatingsList {


public:

    RatingsList();                                  // Constructor
    ~RatingsList();                                 // Destructor
    RatingsList(const RatingsList &);               // Copy constructor
    RatingsList& operator=(const RatingsList &);    // Overloaded = operator
    void add(int, int, int);                        // add element to array
    int emptyFullVector(int, int) const;   //returns int based on 1D array
                                            // is full, empty, or neither
    int getRating(int, int);                //get book rating from account
    int getISBN(int account, int rating);   //get isbn's with specific ratings
                                            //of specific member
    void addMember();                       //add member manually
    bool empty() const;                     // determines if list is empty
    int size() const;                       // number of elements in array
    string to_string() const;               // returns string representation of
                                            // the BookList class

private:

    int ** ratingsArr;              // Pointer to the array
    int rowMemMax;                  // capacity of array
    int colBookMax;                 // capacity of array
    int numRatings;                 // Number of elements
    void resize();                  // resize array (when full)


};


#endif //PROJECT1_RATINGSLIST_H
