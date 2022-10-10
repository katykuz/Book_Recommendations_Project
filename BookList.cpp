// Ekaterina Kuznetsova
// BookList.cpp
// Purpose: Implementation for className described in BookList.h

#include <iostream>
#include "BookList.h"
#include <string>
#include <sstream>

using namespace std;

//declare static integer for counting number of books
//static int bookCount;

//constructor
BookList::BookList() {
    const int CAP = 100;
    list = new Book[CAP];
    capacity = CAP;
    numElements = 0;
    bookCount = 1;
}

//destructor
BookList::~BookList() { //when an object goes out of scope, the destructor is
    // called and the object is deleted (automatically)
    delete [] list;
}

//copy constructor
BookList::BookList(const BookList &obj) {
    // assign numElements and capacity (from obj)
    capacity = obj.capacity;
    numElements = obj.numElements;

    // allocate memory based on new capacity
    list = new Book[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numElements; i++)
        list[i] = obj.list[i];
}

//equals operator
BookList& BookList::operator=(const BookList &obj) {
    if (this != &obj) {     //checking if this has the same memory address as
        // &obj because they would be the same thing
        // deallocate memory
        delete [] list; //this refers to the list that is calling the operator
        //this is list1 in this case: list1 = list2

        // assign numElements and capacity (from obj)
        capacity = obj.capacity;
        //^^ refers to list1's capacity
        numElements = obj.numElements;

        // allocate memory based on new capacity
        list = new Book[capacity];

        // copy over elements (from obj)
        for (int i = 0; i < numElements; i++)
            list[i] = obj.list[i];
    }
    //dereferencing the pointer this
    return *this;   //returns the contents of the pointer - which is an IntList
}

void BookList::add(string el) {
    if (numElements >= capacity) //check if the array is full
        resize();                // resize doubles the size of the array

    //declare string  to pass sections of the element string into struct
    string str;

    //assign isbn value from static int counter of books while incrementing it
    list[numElements].isbn = ++bookCount;

    //push el string into istringstream to be able to parse it
    istringstream ss(el);

    //assign first section of string to author
    getline(ss, str, ',');
    list[numElements].author = str;

    //assign next section of string to title
    getline(ss, str, ',');
    list[numElements].title = str;

    //assign last section of string to year
    getline(ss, str, ',');
    list[numElements].year = str;

    //increment the number of elements for array indexing
    numElements++;

}

int BookList::get(int el) const {

    //to see if certain element is present in array, loop through array to find
    // element
    for (int i = 0; i < numElements; i++) {
        if (list[i].isbn == (el))
            // return i
            return i;
    }
    // if not found, return -1
    return -1;
}

int BookList::find(string authorName, string bookName, string yearPublished) {

    bool found;
    int i;

    for (i = 0; i < numElements; i++) {
        if ((list[i].author.compare(authorName) == 0) &&
            (list[i].title.compare(bookName) == 0) && (list[i].year.compare
                (yearPublished)) == 0) {
            //
            return i + 1;
        }

    }
    return -1;
}

bool BookList::empty() const {

    //returns true if number of elements is zero and array is empty
    return numElements == 0;

}

int BookList::size() const {

    //returns number of elements in array
    return numElements;

}

int BookList::numberOfBooks() const{

    //returns number of books added
    return bookCount;
}


//use to_string to pass needed strings to be printed into driver file
string BookList::to_string() const {

    //declare stringstream
    stringstream ss;

    //pass number of books into stringsream
    ss << "Number of books: " << bookCount << "\n" << endl;

    //go through array and pass each element struct into ss
    for (int i = 0; i < numElements; i++)

        //push into ss attributes with formatting
        ss << list[i].isbn << ", " << list[i].author << ", " << list[i].title
           << ", " << list[i].year << endl;

    //return the string
    return ss.str();

}

void BookList::resize() {
    // update capacity
    capacity *= 2;              //doubles the value of capacity

    // create a new array with new capacity
    Book * tempArr = new Book[capacity];

    // copy contents of old array into new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = list[i];

    // delete old array
    delete [] list;

    // reassign old array to new array
    list = tempArr;
}
