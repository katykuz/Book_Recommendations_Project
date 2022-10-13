// AUTHOR:   Ekaterina Kuznetsova
// FILENAME: project1.cpp
// DATE:     October 11, 2022
// PURPOSE:  The purpose of this class is to build the driving methods needed
//           to successfully run the program with BookList, RatingsList, and
//           MemberList classes. The program takes in a file with book
//           information and a file with customer names and ratings of the
//           books in the previous file. The program draws information from
//           both of these files to provide action items the user of the
//           program can interact with. A logged in user of the program can
//           view recommendations of books they have not read based on books
//           that other members (with similar tastes) have read. These users
//           can also view their rating history and rate/re-rate books. All
//           users/guests can add a book to the 'library' and add a member to
//           the program's member 'history'.
// INPUT:    books.txt and ratings.txt
// PROCESS:  Read files and allocate information to dynamic arrays on the heap.
// OUTPUT:   Various outputs to the terminal based on menu options chosen by
//           the user.

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "BookList.h"
#include "MemberList.h"
#include "RatingsList.h"

using namespace std;

void welcome();
// Welcome user to program and provide introduction
// IN: none
// MODIFY: none
// OUT: none

bool getFilePathBooks(string &filepathBooks);
// Request and acquire filepath for book info (equalling null at this point)
// IN: string variable representing the filepath
// MODIFY: none
// OUT: Return true if file is valid, false if it is not

bool getFilePathRatings(string &filepathRatings);
// Request and acquire filepath for member and rating information
// IN: string variable representing the filepath (equalling null at this point)
// MODIFY: none
// OUT: Return true if file is valid, false if it is not

void intakeBookFileLogic(string &filepathBooks);
// Reads the file and calls function that allocates file content into a
// dynamic array
// IN: string variable representing file with book content
// MODIFY: pass into add function of BookList class instance
// OUT: none

void intakeMemberRatingLogic(string &filepathRatings);
// Reads the file and calls function that allocates file content into a
// dynamic array
// IN: string variable representing file with book content
// MODIFY: pass into add function of MemberList & RateList class instance
// OUT: none

void printNumberOfContentsInFiles();
// Prints the number of books and members counted from file inputs
// IN: none
// MODIFY: none
// OUT: print to terminal number of books and members that were collected in
// files by using getter function from respective class instances

void printMenu(bool loggedIn);
// Prints specific menu options based on whether or not a user is logged in
// IN: bool variable representing if a user is logged in
// MODIFY: none
// OUT: print menu option to the terminal

void menuLogic(bool loggedIn);
// Calls function chosen by user from a switch statement based on if user is
// logged in or not
// IN: bool variable representing if a user is logged in
// MODIFY: none
// OUT: none

void addBook();
// Method allows the user to add a book to the dynamic array of books by
// entering book info, method checks if the book is already on the array,
// does not add book if it is in array already, adds book if it is not. In
// both cases, the method prints the isbn of the book (existing or new).
// IN: Strings representing book title, author, and year published
// MODIFY: none
// OUT: Prints string stating the isbn of the book

void addMember();
// Method allows the user to add a member to the dynamic array of members by
// entering the name of the new member. Members of the same names are
// accepted. Method prints the new account number to the terminal.
// IN: String representing member name
// MODIFY: none
// OUT: Prints string stating the account number of new member

void loginLogic();
// Method allows the user to 'log in' by entering an account number; method
// checks if account number exists and prints name of account holder to
// terminal. If account number does not exist, the program asks user to try
// again. The account number is passed into a function in the memberList
// class that keeps track of the current logged in member. The method updates
// static bool 'loggedIn' variable to true.
// IN: Int variable from user representing account number
// MODIFY: none
// OUT: Prints name of account holder.

void logoutLogic();
// Method changes the static bool 'loggedIn' variable to false and passes a
// value representing a logged out state (-1) into a function in the MemberList
// class that keeps track of the current logged in member.
// IN: none
// MODIFY: none
// OUT: none

void rateChart();
// The method prints a chart of the ratings allowed and their meanings.
// IN: none
// MODIFY: none
// OUT: none

void rateBookLogic();
// Method allows the user to rate a new book or re-rate a book they've
// already rated. Method acquires int variable representing the isbn of a
// book; searches if the user already rated this book (by using current
// logged in member account number and isbn of book). If the rating is 0
// (member has not read book), method calls a function to change rating of
// the book. If the book already has a rating, method prints the current
// rating and asks if member would like to change the rating, acquires input
// for response. If input is yes/1, method calls a function to change rating
// of book. If the user does not want to change the rating, method prints a
// confirmation statement that rating did not change.
// IN: User input of book ISBN and input on choice to change book rating
// MODIFY: none
// OUT: Print statements of current ratings of rated books and confirmation
// if the rating was not changed.

void rateBook(int inputISBN);
// Method takes in a book ISBN int variable, finds
// IN: none
// MODIFY: none
// OUT: none

void viewAllRatings();
// Prints all of the current member's books and their ratings
// IN: none
// MODIFY: none
// OUT: none

bool preRecommendationsVerification();
// This method verifies if the user has not read/rated any books or if they
// have read/rated all of the books. Both options will lead to no
// recommendations.
// IN: none
// MODIFY: none
// OUT: none

void viewRecommendations();
// Method calculates the most and second to most compatible members/members
// with most similar tastes in books by calculating the dot product of the
// corresponding ratings. If the most compatible reader read the same books
// as the logged in member, method uses the second to most compatible member
// to recommend books.
// IN: none
// MODIFY: none
// OUT: none

void compatibleMemberBooks(int compatibleMember);
// Method prints the 'really liked' and 'liked' books from the most
// 'compatible' members/members with most similar tastes.
// IN: Integer value representing the account number of the most comp. member
// MODIFY: none
// OUT: none

bool membersReadSameBooks(int compatibleMember);
// Method verifies if the members read the same books, returns true if so,
// returns false if they read different books.
// IN: int variable representing the account number of the comp. member.
// MODIFY: none
// OUT: none


//create a static bool to keep track of when to quit the program
static bool quit;
//create a static bool to keep track of when a user is logged in
static bool loggedIn;
//create a ratingsList class instance
static RatingsList * ratings = new RatingsList();
//create a membersList class instance
static MemberList * members = new MemberList();
//create a BookList class instance
static BookList * arrayOfBooks = new BookList();

int main() {

    //welcome message&welcome function
    welcome();

    //create boolean variables to check if files open
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

    //get and print number of books and number of members
    printNumberOfContentsInFiles();

    //run the user interface until quit boolean turns true via user input
    do{

        //print menu
        printMenu(loggedIn);

        //run logic to interact with menu
        menuLogic(loggedIn);

    }while(!quit);

    return 0;
}

void welcome(){

    //initiate the welcome message
    string welcomeMessage = "\nWelcome to GoodBooks! "
            "\nThis program will recommend members books based on other\n"
            "readers with similar taste. Members can also keep\n"
            "a rating history of books read and rate/re-rate books. Members\n"
            "and guests can add books to the library and members to the\n"
            "GoodBooks program.\n";

    //print welcome message
    cout << welcomeMessage;
}

bool getFilePathBooks(string &filepathBooks) {

    //prompt user for filepath
    cout << "\nEnter the file with books: ";

    //read in user input
    cin >> filepathBooks;
    cout << endl;

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

    //call function to get number of books and print to terminal
    cout << "Number of Books: " << arrayOfBooks->numberOfBooks() << endl;

    //call function to get number of members and print to terminal
    cout << "Number of Members: " << members->numberOfMembers() << endl;


}

void printMenu(bool loggedIn) {

    //delcare all string variables needed for menu
    string menuHeader, menuFooter;
    string addMem, addBook, login, quitString, rtBk, viewRat, viewRec, logout;

    //initialize all string variables for menu
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

    //print menu based on whether user is logged in or not

    //print menu header
    cout << "\n" << menuHeader << endl;

    //these options are for guests and members
    cout << addMem << "\n" << addBook << "\n";

    //if logged out
    if (!loggedIn)
        cout << login << "\n" << quitString << endl;

    //if logged in
    if (loggedIn)
        cout << rtBk << "\n" << viewRat << "\n" << viewRec << "\n" << logout <<
             endl;

    //print footer
    cout << menuFooter << endl;

}

void menuLogic(bool loggedIn){

    //declare int variable to hold user input
    int userChoice;

    cout << "\nEnter menu option: ";
    cin >> userChoice;

    //manage hidden characters
    cin.clear();
    cin.ignore();

    //switch statement to call functions if the user is logged in
    if (!loggedIn){
        switch(userChoice){
            //add a new member
            case 1:
                addMember();
                break;
            //add new book
            case 2:
                addBook();
                break;
            //login
            case 3:
                loginLogic();
                break;
            //quit
            case 4:
                cout << "\nThanks for using GoodBooks!\n";
                //update static quit variable
                quit = true;
                break;
            //if user enters anything other than menu options
            default:
                //if user enters anything else
                cout << "Invalid input. Try again!\n";
                break;
        }
    } else if (loggedIn) {
        switch(userChoice) {
            //add new member
            case 1:
                addMember();
                break;
            //add new book
            case 2:
                addBook();
                break;
            //rate book
            case 3:
                rateBookLogic();
                break;
            //view ratings
            case 4:
                viewAllRatings();
                break;
            case 5:
            //view Recommendations
                if (preRecommendationsVerification()) {
                    viewRecommendations(); }
                break;
            //logout
            case 6:
                logoutLogic();
                break;
            //if user enters anything other than menu options
            default:
                cout << "\nInvalid input. Try again!\n";
                break;
        }

    }
}

void addBook() {

    //declare string variables to hold book information
    string author, title, year;

    //acquire book author
    cout << "Enter the author of the new book: ";
    getline (cin, author);

    //acquire book title
    cout << "Enter the title of the new book: ";
    getline (cin, title);

    //acquire book publication year
    cout << "Enter the year (or range of years) of the new book: ";
    getline (cin, year);

    //push strings into stringstream to push to arrayOfBooks add method
    stringstream ss;
    ss << author << ", " << title << ", " << year;

    //check if the title of the book already exists in the list;
    int ifFound = arrayOfBooks->find(author, title, year);


    //if it is found, state it's isbn
    if (ifFound != -1) {

        cout << "\nThis book is already added, its ISBN is: " << ifFound <<
             endl;

    //if it is not found, add this new book to the book array
    } else {
        arrayOfBooks->add(ss.str());

        //print confirmation statement with new books' isbn
        cout << "\nAdded! This book's ISBN is: " << arrayOfBooks->numberOfBooks
                () << endl;
    }

}

void addMember(){

    //declare string variable for name from user input;
    string name;

    //acquire name of new member
    cout << "Enter the name of the new member: ";
    cin >> name;

    //call add member function of ratings class
    ratings->addMember();

    //push values to the add method from Memberlist
    //print confirmation statement with new member's account number
    cout << members->addManually(name) << endl;

}

void loginLogic(){

    //declare int variable to hold the member account number
    int memberAccountNum;

    //acquire account number to log in
    cout << "Enter member account: ";
    cin >> memberAccountNum;

    //verify the input was numerical and check if member exists on array
    //if member number does not exist or invalid, allow them to enter it
    // again
    while (!cin.good() || !members->find(memberAccountNum))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input type. Try again: ";
        cin >> memberAccountNum;
    }

    //update loggedIn static variable
    loggedIn = true;

    //keep track of the logged in member to retrieve later
    members->saveLoggedInMem(memberAccountNum);

    //print confirmation statement of logging in with member's name
    cout << members->getNameOfMember(memberAccountNum) << " is logged "
                                                          "in!" << endl;
}

void logoutLogic(){

    //change static boolean
    loggedIn = false;

    //initialize an integer to assign when no one is logged in
    int loggedOutAccntPlaceholder = -1;

    members->saveLoggedInMem(loggedOutAccntPlaceholder);

}

void rateBookLogic(){

    //declare integer variables for book isbn and user rating input
    int inputISBN;
    int changeInput;

    //call function to print/display the different valid ratings
    rateChart();

    //acquire ISBN of book to rate
    cout << "Enter ISBN of book you'd like to rate: ";
    cin >> inputISBN;

    //check if the input was numerical, ask again if not
    while (!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input type. Try again: ";
        cin >> inputISBN;
    }

    //check this ISBN exists in the list, if not, ask again
    while (arrayOfBooks->getISBN(inputISBN) == -1){

        cin.clear();
        cin.ignore();

        cout << "Invalid input type. Try again: ";
        cin >> inputISBN;

    }

    //pass the user account number and isbn to get current rating of the book
    int ratingOfRequestedBook = ratings->getRating(members->getLoggedInMem(),
                                                   inputISBN);

    //if the current rating of the book is zero, allow user to rate
    if (ratingOfRequestedBook == 0) {

        //call function to acquire rating of the book
        rateBook(inputISBN);

    //if the book is already rated, display current rating and allow user to
    // change it if they chose
    } else {

        //prints book info and current rating of the book
        cout << arrayOfBooks->getBookTitle(inputISBN)
             << " by " << arrayOfBooks->getBookAuthor(inputISBN) << " already"
                " has a rating of " << ratingOfRequestedBook << "." << endl;

        //ask if user would like to change this rating and acquire
        cout << "Would you like to change it? Press 1 for yes: ";
        cin >> changeInput;

        cin.clear();
        cin.ignore();

        //validate input - if input is 1, allow them to change the rating
        if (changeInput == 1)
        {
            //call function to acquire rating of the book
            rateBook(inputISBN);

        //if they enter anything else, do not change the rating
        } else {

            cout << "Rating remains unchanged.\n";
        }
    }
}

void rateBook(int inputISBN) {

    //declare integer variable for holding input rating
    int inputRating;

    //print book information and acquire rating for book
    cout << "Enter rating for " << arrayOfBooks->getBookTitle(inputISBN)
         << " by " << arrayOfBooks->getBookAuthor(inputISBN) << ": ";
    cin >> inputRating;

    //validate that the rating falls within allowed numbers, otherwise ask again
    while ((inputRating != -5) && (inputRating != -3) &&
           (inputRating != 0) && (inputRating != 3) && (inputRating != 5))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Must enter a rating from options listed. Try again: ";
        cin >> inputRating;
    }

    //save this rating in the RatingsList array
    ratings->add(members->getLoggedInMem(), inputISBN, inputRating);

}

void rateChart(){

    //declare strings needed to display rate chart
    string rateHeader, rateFooter;
    string rateNegFive, rateNegThree, rateNegOne, rateZero, rateOne, rateThree,
            rateFive;

    //initialize these strings
    rateHeader = "********** RATINGS **********";
    rateFooter = "*****************************\n";
    rateNegFive ="* -5     |     Hated it!    *";
    rateNegThree="* -3     |  Didn't like it  *";
    rateZero =   "*  0     |  Haven't read it *";
    rateThree =   "*  3     |     Liked it!    *";
    rateFive=   "*  5     | Really liked it  *";

    //print the chart

    //print header
    cout << "\n" << rateHeader << endl;

    //print options
    cout << rateNegFive << "\n" << rateNegThree << "\n";
    cout << rateZero << "\n" << rateThree << "\n" << rateFive << endl;

    //print footer
    cout << rateFooter << endl;

}

void viewAllRatings(){

    //iterate through all of the books in the array based on size
    for (int i = 1; i <= arrayOfBooks->size(); i++){

        //print book information, commas in between, followed by rating
        cout << arrayOfBooks->getISBN(i) << ", " <<
             arrayOfBooks->getBookAuthor
                     (i) << ", " << arrayOfBooks->getBookTitle(i) <<
                     " => rating: " <<
             ratings->getRating(members->getLoggedInMem(), i) << endl;
    }
}

bool preRecommendationsVerification(){

    //get the number of books
    int bookNum = arrayOfBooks->numberOfBooks();

    //check whether the logged in member has not read/rated any books,
    //recommendations not possible if that's the case
    if (ratings->emptyFullVector(members->getLoggedInMem(), bookNum) == -3)
    {
        cout << "\nYou have not read/rated any books! Please read/rate at "
                "least\none book to receive recommendations.\n";
        return false;

    //check whether the member has read/rated all the books, recommendations
    // also not possible for this
    } else if (ratings->emptyFullVector(members->getLoggedInMem(),
                                        bookNum) == -2) {

        cout << "\nYou have read/rated all of the books! There are no more\n"
                "books to recommend for you. Go outside!\n";
        return false;

    //then the member has only read some of the books, return true to call
    // the viewRecommendations function
    } else {
        return true;
    }

}

void viewRecommendations(){

    //int variable to hold the maximum compatibility value
    int max = 0;
    //int variable to hold the 2nd to maximum compatibility value
    int max2 = 0;
    //int variable to hold the account number of maximum compatibility value
    int maxCompatibleMemberAccntNum;
    //int variable to hold the account number of maximum compatibility value
    int maxCompatibleMemberAccntNum2;


    //calculate the 'compatibility' between logged-in user and all other members
    //keep track of the maximum compatibility number
    //iterate through the members
    for (int i = 1; i <= members->size(); i++) {
        int num = 0;
        //don't compare logged in member to themselves (skip it by incrementing)
        if (i == members->getLoggedInMem()) {
            i++;
        }
        //iterate through the books
        for (int j = 1; j <= arrayOfBooks->size(); j++){

            //calculate the dot product between the two members
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

    //check if members read all the same books, if not same, use max member
    if (!membersReadSameBooks(maxCompatibleMemberAccntNum)) {
        compatibleMemberBooks(maxCompatibleMemberAccntNum);

    //if same, provide recommendation based on second to max compatible member
    } else {
        compatibleMemberBooks(maxCompatibleMemberAccntNum2);
    }
}

void compatibleMemberBooks(int compatibleMember) {

    //print name of compatible member
    cout << "You have similar taste as " <<
         members->getNameOfMember(compatibleMember) << "!\n" << endl;

    //print the books this compatible member really liked
    cout << "All books they really liked (rating of 5):" << endl;

    //iterate through the books
    for (int i = 1; i <= arrayOfBooks->size(); i++) {

        //if they did not read the same book
        if ((ratings->getRating(compatibleMember, i) != 0 ||
             ratings->getRating(members->getLoggedInMem(), i) != 0) &&
            (ratings->getRating(compatibleMember, i) == 0 ||
             ratings->getRating(members->getLoggedInMem(), i) == 0)) {

            //if they gave the book a rating of 5
            if (ratings->getRating(compatibleMember, i) == 5) {

                //print information of the book
                cout << arrayOfBooks->getISBN(i) << ", " <<
                     arrayOfBooks->getBookAuthor
                             (i) << ", " << arrayOfBooks->getBookTitle(i) <<
                     ", " << arrayOfBooks->getBookYear(i) << endl;
            }
        }
    }

    //print the books this compatible member really liked
    cout << "\nAll books they liked (rating of 3):" << endl;

    //iterate through the books
    for (int i = 1; i <= arrayOfBooks->size(); i++) {

        //if they did not read the same book
        if ((ratings->getRating(compatibleMember, i) != 0 ||
             ratings->getRating(members->getLoggedInMem(), i) != 0) &&
            (ratings->getRating(compatibleMember, i) == 0 ||
             ratings->getRating(members->getLoggedInMem(), i) == 0)) {

            //if they gave the book a rating of 3
            if (ratings->getRating(compatibleMember, i) == 3) {

                //print information of the book
                cout << arrayOfBooks->getISBN(i) << ", " <<
                     arrayOfBooks->getBookAuthor
                             (i) << ", " << arrayOfBooks->getBookTitle(i) <<
                     ", " << arrayOfBooks->getBookYear(i) << endl;
            }
        }
    }
}


bool membersReadSameBooks(int maxCompatibleMemberAccntNum){

    //iterate through all the books and check if both members read the same
    // books
    for (int i = 1; i <= arrayOfBooks->size(); i++) {
        if (ratings->getRating(maxCompatibleMemberAccntNum, i) != 0 &&
            ratings->getRating(members->getLoggedInMem(), i) != 0) {
            return true;
        }
    }
    return false;
}

