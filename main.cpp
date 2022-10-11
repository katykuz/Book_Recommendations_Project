// AUTHOR:   Ekaterina Kuznetsova
// FILENAME:
// DATE:
// PURPOSE:
// INPUT:
// PROCESS:
// OUTPUT:

//TODO: what happens if brand new member (added manually) immediately wants
// to see recommendations? Need to add a condition if they have no ratings,
// they have to add a rating before proceeding.

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

void intakeBookFileLogic(string &filepathBooks);

void intakeMemberRatingLogic(string &filepathRatings);

void printNumberOfContentsInFiles();

void printMenu(bool loggedIn);

void menuLogic(bool loggedIn);

void addBook();

void addMember();

void loginLogic();

void logoutLogic();

void rateBookLogic();

void rateBook(int inputISBN);

void rateChart();

void viewAllRatings();

void viewRecommendations();

void compatibleMemberBooks(int compatibleMember);

bool membersReadSameBooks(int compatibleMember);


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
    int i = 1;

    //loop until the end of the file
    while (!inFile.eof()) {

        //read in a line as a string
        getline(inFile, name);

        //allocate string to the members 1D array
        members->add(name);

        //advance counter
        countMembers++;

        //initiate index integer for columns of 2D array
        int j = 1;

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
                rateBookLogic();
                break;
            case 4:
                //view ratings
                viewAllRatings();
                break;
            case 5:
                //See recommendations
                viewRecommendations();
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

    cout << "Enter the title of the new book: ";
    getline (cin, title);

    cout << "Enter the year (or range of years) of the new book: ";
    getline (cin, year);

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
    //print confirmation statement with new member's account number
    cout << members->addManually(name) << endl;

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
            cout << "This member was not found.\n";
            cout << "Try again: ";
            cin >> memberAccountNum;
        }

        proceed = true;

    }while(!proceed);

    loggedIn = true;

    members->saveLoggedInMem(memberAccountNum);

    //print confirmation statement of logging in with member's name
    cout << members->getNameOfMember(memberAccountNum) << " is logged "
                                                          "in!" << endl;
}

void logoutLogic(){

    loggedIn = false;

    int loggedOutAccntPlaceholder = -1;

    members->saveLoggedInMem(loggedOutAccntPlaceholder);

}

void rateBookLogic(){

    int inputISBN;
    int inputRating;
    int changeInput;

    rateChart();

    cout << "Enter ISBN of book you'd like to rate: ";
    cin >> inputISBN;


    while (!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input type. Try again: ";
        cin >> inputISBN;
    }

    //pass the user account number and isbn to get rating of the book
    int ratingOfRequestedBook = ratings->getRating(members->getLoggedInMem(),
                                            inputISBN);

    if (ratingOfRequestedBook == 0) {

        rateBook(inputISBN);

    } else {
        //prints "(Title) by (author) already has a rating of (rating), would
        //you like to change it?"
        cout << arrayOfBooks->getBookTitle(inputISBN)
             << " by " << arrayOfBooks->getBookAuthor(inputISBN) << " already "
                "has a rating of " << ratingOfRequestedBook << "." << endl;
        cout << "Would you like to change it? Press 1 for yes: ";
        cin >> changeInput;

        cin.clear();
        cin.ignore();

        //validate input
        if (changeInput == 1)
        {
            rateBook(inputISBN);
        } else {

            cout << "Rating remains unchanged.\n";

        }


    }

}

void rateBook(int inputISBN) {

    int inputRating;

    cout << "Enter rating for " << arrayOfBooks->getBookTitle(inputISBN)
         << " by " << arrayOfBooks->getBookAuthor(inputISBN) << ": ";
    cin >> inputRating;

    while ((inputRating != -5) && (inputRating != -3) &&
    (inputRating != 0) && (inputRating != 3) && (inputRating != 5))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Must enter a rating from options listed. Try again: ";
        cin >> inputRating;
    }

    ratings->add(members->getLoggedInMem(), inputISBN, inputRating);

}

void rateChart(){

    string rateHeader, rateFooter;
    string rateNegFive, rateNegThree, rateNegOne, rateZero, rateOne, rateThree,
            rateFive,
    rtBk,
    viewRat,
    viewRec,
    logout;
    rateHeader = "********** RATINGS **********";
    rateFooter = "*****************************\n";
    rateNegFive ="* -5     |     Hated it!    *";
    rateNegThree="* -3     |  Didn't like it  *";
    rateZero =   "*  0     |  Haven't read it *";
    rateThree =   "*  3     |     Liked it!    *";
    rateFive=   "*  5     | Really liked it  *";

    cout << "\n" << rateHeader << endl;
    cout << rateNegFive << "\n" << rateNegThree << "\n";
    cout << rateZero << "\n" << rateThree << "\n" << rateFive << endl;
    cout << rateFooter << endl;

}

void viewAllRatings(){

    for (int i = 1; i <= arrayOfBooks->size(); i++){

        cout << arrayOfBooks->getISBN(i) << ", " <<
        arrayOfBooks->getBookAuthor
        (i) << ", " << arrayOfBooks->getBookTitle(i) << " => rating: " <<
        ratings->getRating(members->getLoggedInMem(), i) << endl;

    }

}

void viewRecommendations(){

    int max = 0;
    int max2 = 0;
    int maxCompatibleMemberAccntNum;
    int maxCompatibleMemberAccntNum2;

    //calculate the 'compatibility' between logged in user and all other members
    //keep track of the maximum compatibility number


    for (int i = 1; i <= members->size(); i++) {
        int num = 0;
        if (i == members->getLoggedInMem()) {
            i++;
        }
        for (int j = 1; j <= arrayOfBooks->size(); j++){

            num += ratings->getRating(members->getLoggedInMem(), j) *
                    ratings->getRating(i, j);

        }

        //update the max if current compatibility num is greater
        if (max < num) {
            max = num;
            maxCompatibleMemberAccntNum = i;
        } else if (max > num && num > max2) {
                max2 = num;
                maxCompatibleMemberAccntNum2 = i;
        }

    }

    //check if members read all the same books, if so, provide recommendations
    //based on second to max compatible member
    if (!membersReadSameBooks(maxCompatibleMemberAccntNum)) {

        compatibleMemberBooks(maxCompatibleMemberAccntNum);

    } else {

        compatibleMemberBooks(maxCompatibleMemberAccntNum2);

    }

}

void compatibleMemberBooks(int compatibleMember) {

    cout << "You have similar taste as " <<
         members->getNameOfMember(compatibleMember) << "!\n" << endl;

    //books other member 'really liked', rating of 5
    cout << "Books they really liked:" << endl;
    for (int i = 1; i <= arrayOfBooks->size(); i++) {
        if (ratings->getRating(compatibleMember, i) == 5) {
            cout << arrayOfBooks->getISBN(i) << ", " <<
                 arrayOfBooks->getBookAuthor
                         (i) << ", " << arrayOfBooks->getBookTitle(i) <<
                 ", " << arrayOfBooks->getBookYear(i) << endl;
        }
    }

    //books other member 'liked', rating of 3
    cout << "Books they liked:" << endl;
    for (int i = 1; i <= arrayOfBooks->size(); i++) {
        if (ratings->getRating(compatibleMember, i) == 5) {
            cout << arrayOfBooks->getISBN(i) << ", " <<
                 arrayOfBooks->getBookAuthor
                         (i) << ", " << arrayOfBooks->getBookTitle(i) <<
                 ", " << arrayOfBooks->getBookYear(i) << endl;
        }
    }

}

bool membersReadSameBooks(int maxCompatibleMemberAccntNum){

    for (int i = 1; i <= arrayOfBooks->size(); i++) {
        if (ratings->getRating(maxCompatibleMemberAccntNum, i) != 0 &&
        ratings->getRating(members->getLoggedInMem(), i) != 0) {
            return true;
        }
    }
    return false;
}

