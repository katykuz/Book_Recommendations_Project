// AUTHOR:   Ekaterina Kuznetsova
// FILENAME:
// DATE:
// PURPOSE:
// INPUT:
// PROCESS:
// OUTPUT:

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "BookList.h"
#include "MemberList.h"
#include "RatingsList.h"
using namespace std;

bool getFilePathBooks(string &filepathBooks);

bool getFilePathRatings(string &filepathRatings);

void printMenu(bool loggedIn);

void menuLogic(bool loggedIn);

void addBook();

void addMember();

void loginLogic();

void logoutLogic();

void intakeBookFileLogic(string &filepathBooks);

void intakeMemberRatingLogic(string &filepathRatings);

void printNumberOfContentsInFiles();


static bool quit;
static bool loggedIn;
static int currentNumOfBooks;

static RatingsList * ratings = new RatingsList();

static MemberList * members = new MemberList();

static BookList * arrayOfBooks = new BookList();

int main() {

    //welcome message&welcome function

    bool gotBooks;
    bool gotRatings;



    //do-while loop to enter files - program will not proceed without files
    do{
        string filepathBooks;
        string filepathRatings;

        //call viewRatings filepath function 1
        gotBooks = getFilePathBooks(filepathBooks);
        //call viewRatings filepath function 2
        gotRatings = getFilePathRatings(filepathRatings);

    }while(!gotBooks || !gotRatings);

    printNumberOfContentsInFiles();

    do{

        printMenu(loggedIn);
        menuLogic(loggedIn);

    }while(!quit);



    return 0;
}


bool getFilePathBooks(string &filepathBooks) {

    //prompt user for filepath
    cout << "\nEnter the file with books: ";
    //C:\Users\evken\CLionProjects\Project1\books.txt

    //read in user input
    cin >> filepathBooks;
    //cout << endl;

    //open the file - ifstream is a datatype used to read from file
    ifstream inFile;
    inFile.open(filepathBooks);

    //if the file opens, return true, otherwise return false
    if (inFile.is_open()) {
        //call function to take in content from file
        intakeBookFileLogic(filepathBooks);
        return true;
    } else {
        return false;
    }

}

bool getFilePathRatings(string &filepathRatings) {

    //prompt user for filepath
    cout << "Enter the file with ratings: ";
    //C:\Users\evken\CLionProjects\Project1\ratings.txt

    //read in user input
    cin >> filepathRatings;
    cout << endl;

    //open the file - ifstream is a datatype used to read from file
    ifstream inFile;
    inFile.open(filepathRatings);

    //if the file opens, return true, otherwise return false
    if (inFile.is_open()) {
        intakeMemberRatingLogic(filepathRatings);
        return true;
    } else {
        return false;
    }

}

void intakeBookFileLogic(string &filepathBooks) {


    //declare string variables to hold a line from file and a section of line
    string line, section;

    //open the file - ifstream is a datatype used to read from file
    ifstream inFile;
    inFile.open(filepathBooks);

    //loop until the end of the file
    while (getline(inFile, line)) {

        //read in a line as a string
        arrayOfBooks->add(line);

    }


}

void intakeMemberRatingLogic(string &filepathRatings){

    //declare and initiate necessary variables
    string name;            //string to hold member name values
    string numbers;         //string to hold the line of numbers
    int num;                //integer to hold individual numbers
    int countMembers = 0;   //integer to count number of members

    //open the file - ifstream is a datatype used to read from file
    ifstream inFile;
    inFile.open(filepathRatings);

    //initiate indexing integer for 1D array
    int i = 0;

    //loop until the end of the file
    while (!inFile.eof()) {

        //read in a line as a string
        getline(inFile, name);

        //allocate string to the members 1D array
        members->add(name);

        //advance counter
        countMembers++;

        //initiate index integer for columns of 2D array
        int j = 0;

        //read in the next line - a line of numbers
        getline(inFile, numbers);

        //split the string into individual numbers
        istringstream ss(numbers);
        while (ss >> num)
        {
            //allocate individual numbers to a member's row
            ratings->add(i, j, num);
            //advance the index of columns
            j++;

        }

        //advance the row index
        i++;
    }


}

void printNumberOfContentsInFiles(){

    cout << "Number of Books: " << arrayOfBooks->numberOfBooks() << endl;
    cout << "Number of Members: " << members->numberOfMembers() << endl;


}

void printMenu(bool loggedIn) {

    string menuHeader, menuFooter;
    string addMem, addBook, login, quitString, rtBk, viewRat, viewRec, logout;
    menuHeader = "************** MENU **************";
    menuFooter = "**********************************";
    addMem = "* 1. Add a new member            *";
    addBook = "* 2. Add a new book              *";
    login = "* 3. Login                       *" ;
    quitString = "* 4. Quit                        *";
    rtBk = "* 3. Rate book                   *";
    viewRat = "* 4. View ratings                *";
    viewRec = "* 5. See recommendations         *";
    logout = "* 6. Logout                      *";

    //if logged out
    cout << "\n" << menuHeader << endl;
    cout << addMem << "\n" << addBook << "\n";
    //if logged out
    if (!loggedIn)
        cout << login << "\n" << quitString << endl;
    //if logged in
    if (loggedIn)
        cout << rtBk << "\n" << viewRat << "\n" << viewRec << "\n" << logout <<
            endl;
    cout << menuFooter << endl;

}

void menuLogic(bool loggedIn){

    int userChoice;

    cout << "\nEnter menu option: ";
    cin >> userChoice;

    cin.clear();
    cin.ignore();

    if (!loggedIn){
        switch(userChoice){
            case 1:
                //add a new member
                addMember();
                break;
            case 2:
                //add new book
                addBook();
                break;
            case 3:
                //login
                loginLogic();
                break;
            case 4:
                //quit
                quit = true;
                break;
        }
    } else if (loggedIn) {
        switch(userChoice) {
            case 1:
                //add a new member
                addMember();
                break;
            case 2:
                //add new book
                addBook();
                break;
            case 3:
                //rate book
                break;
            case 4:
                //view ratings
                break;
            case 5:
                //See recommendations
                break;
            case 6:
                //logout
                logoutLogic();
                break;
        }

    }
}

void addBook() {

    string author, title, year;

    cout << "Enter the author of the new book: ";
    getline (cin, author);
    //cin.clear();
    //cin.ignore();
    cout << "Enter the title of the new book: ";
    getline (cin, title);
    //cin >> title;
    //cin.clear();
    //cin.ignore();
    cout << "Enter the year (or range of years) of the new book: ";
    getline (cin, year);
    //cin >> year;
    //cin.clear();
    //cin.ignore();

    stringstream ss;
    ss << author << ", " << title << ", " << year;

    //check if the title of the book already exists in the list;
    int ifFound = arrayOfBooks->find(author, title, year);


    //if it is found, state it's isbn
    if (ifFound != -1) {

        cout << "\nThis book is already added, its ISBN is: " << ifFound <<
        endl;
     } else {
        //if it is not found, add this new book to the book array
        arrayOfBooks->add(ss.str());
        //print confirmation statement with new books' isbn
        cout << "\nAdded! This book's ISBN is: " << arrayOfBooks->numberOfBooks
                 () << endl;
     }

}

void addMember(){

    string name;

    cout << "Enter the name of the new member: ";
    cin >> name;

    //push values to the add method from Memberlist
    cout << members->addManually(name) << endl;

    //same names of members is allowed

    //print confirmation statement with new member's account number

}

void loginLogic(){

    int memberAccountNum;
    bool proceed;
    cout << "Enter member account: ";


    //push account number into memberlist to retrieve the name of member if
    //the member account number exists

    do{

        cin >> memberAccountNum;

        //if member number does not exist or invalid, allow them to enter it
        // again
        while (!members->find(memberAccountNum)) {
            proceed = false;
            cout << "This member was not found or number is invalid.\n";
            cout << "Try again: ";
            cin >> memberAccountNum;
        }

        proceed = true;

    }while(!proceed);

    loggedIn = true;

    members->loggedInMem(memberAccountNum);

    cout << members->getNameOfMember(memberAccountNum) << " is logged "
                                                          "in!" << endl;
    //print confirmation statement of logging in with member's name

}

void logoutLogic(){

    loggedIn = false;

    int loggedOutAccntPlaceholder = -1;

    members->loggedInMem(loggedOutAccntPlaceholder);

}

