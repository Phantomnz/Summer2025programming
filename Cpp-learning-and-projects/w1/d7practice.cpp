#include <iostream>
using namespace std;
// C++ program to demonstrate encapsulation

//~Myclass(){//destructor code goes here}
//prevent memory leaks or clean up resources
//usually used to destroy pointers or close files
//this version of the destructor is called inside a class called Myclass


//C++ provides public, private, and protected to control access to members:

//public: accessible from anywhere
//private: only accessible within the class
//protected: accessible within the class and its derived classes

/*for encapsulation, do the following:
Bundle related data and functions together in a class or struct.
Use private (or at least protected) access specifiers for data you don't want to be tweaked with directly.
only expose through public (or protected) member functions/methods that provide controlled access to the data.
don't make data members public unless absolutely necessary.
This way, you can control how the data is accessed and modified, ensuring that it remains valid and consistent.
In headers, document what each public method does, what parameters it takes, and what it returns.
*/

class box {
private:
    int width;
public:
    void setwidth(int w) { width = w; } // member function to set width
    int getwidth() const { return width; } // member function to get width
}; //these two functions are public, so they can be accessed from outside the class
// they allow controlled access to the private member variable 'width'

class book{
private:
    string title; // private member variable to hold the book title
public:
    book(const string& t = "Unknown") : title(t) //initalizing the member variable title with the value of t
    {/*contructor with default value*/}
    string getTitle() const { return title; } // member function to get title
};
int main(){
    box b; // create a box object
    b.setwidth(10); // set width to 10
    cout << "Width of box: " << b.getwidth() << endl; // get width and print it
    book b1; // create a book object with default title
    book b2("C++ Programming"); // create a book object with specified title
    cout << "Book 1 title: " << b1.getTitle() << endl; // assuming getTitle() is defined
    cout << "Book 2 title: " << b2.getTitle() << endl; // print title of book 2

}