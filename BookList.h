// Ekaterina Kuznetsova
// BookList.h
// October 12, 2022
// Purpose: This class creates a dynamic array with each element consisting
// of a Book struct, which is defined in the private section of this class.
// The class also provides functions needed to modify the array and to gather
// information from the array.

#ifndef LAB2_BOOKLIST_H
#define LAB2_BOOKLIST_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class BookList {
public:

    BookList();             // Constructor
    ~BookList();                // Destructor
    BookList(const BookList &);               // Copy constructor
    BookList& operator=(const BookList &);    // Overloaded = operator
    void add(string);             // add element to array
    int get(int) const;        // find element in array; return index
    int getISBN(int el);
    // where found or -1 if not found
    int find(string, string, string); //find repeating books in list
    string getBookTitle(int); //returns title of book based on isbn
    string getBookAuthor(int);  //returns author of book based on isbn
    string getBookYear(int);    //return year of book based on isbn
    bool empty() const;         // determines if list is empty or not
    int size() const;           // number of elements in array
    int numberOfBooks() const;  //number of books added
    string to_string() const;   // returns string representation of
    // the BookList class

private:

    //Book struct with attributes
    struct Book {
        int isbn;               //isbn number to track book
        string author;          //string variable holding author of book data
        string title;           //string variable holding title of book data
        string year;            //string variable holding year(s) data
    };

    Book * list;             // Pointer to the array
    int capacity;            // capacity of array
    int numElements;         // Number of elements for array indexing
    int bookCount;           //number of books
    void resize();           // resize array (when full)

};


#endif //LAB2_BOOKLIST_H