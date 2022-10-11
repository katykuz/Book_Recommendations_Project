//
// Created by evken on 10/8/2022.
//

#ifndef PROJECT1_RATINGSLIST_H
#define PROJECT1_RATINGSLIST_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class RatingsList {


public:

    RatingsList();             // Constructor
    ~RatingsList();                // Destructor
    RatingsList(const RatingsList &);               // Copy constructor
    RatingsList& operator=(const RatingsList &);    // Overloaded = operator
    void add(int, int, int);             // add element to array
    int returnRatings(int) const;        //
    int getRating(int, int);    //get book's rating from specific account
    int getISBN(int account, int rating);   //get isbn's with specific ratings
                                            // of specific member
    bool empty() const;         // determines if list is empty or not
    int size() const;           // number of elements in array
    string to_string() const;   // returns string representation of
    // the BookList class

private:

    int ** ratingsArr;             // Pointer to the array
    int rowMemMax;            // capacity of array
    int colBookMax;            // capacity of array
    int numRatings;         // Number of elements
    void resize();           // resize array (when full)


};


#endif //PROJECT1_RATINGSLIST_H
