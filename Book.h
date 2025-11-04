#ifndef BOOK_H //prevents the file from being included more than once
#define BOOK_H

#include <iostream> //For input/ output
#include <string> //For using string data type

using namespace std; //Allows use of functions without using std::

class Book {
    //Private attributes
    string title;
    string author;
    int publicationYear;
public:
    // Default constructor: creates an empty book
    Book() : title(""), author(""), publicationYear(0) {}
    // Paramitzed constructor: creates a book with a given title, author and year
    Book(string title_in, string author_in, int year_in) 
        : title(title_in), author(author_in), publicationYear(year_in) {}

    // Getter methods to access private data
    string get_title() const { return title; } // Returns the book's title
    string get_author() const { return author; } // Returns the author's name
    int get_year() const { return publicationYear; } // Returns the publication year

    // Overloaded assignment operator
    Book& operator=(const Book& other) {
        if(this == &other) return *this;
        this->author = other.get_author();
        this->publicationYear = other.get_year();
        this->title = other.get_title();
        return *this;
    }

    // Displays the book's details in a formatted way
    void display() const {
         cout<< "Title: " << title << " | Author: " << author <<endl;
         cout << " | Year: " << publicationYear << endl;
    }
};

#endif