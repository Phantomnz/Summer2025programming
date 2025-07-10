#include <iostream>
#include <string>
using namespace std;

class Point {
    int x = 2;// member variable initialized to 2
    int y = 3;// member variable initialized to 3
    // member variables are private by default, they can only be accessed by member functions of the class
public:
    int getX() const { return x; } //const member function, ensures it does not modify the object
    int getY() const { return this->y; } //this pointer is used to access the current object, here it is used to access the member variable y
};

class printer {
public:
    void print(); // function declaration for print without parameters
    void print(string msg);//overloaded function to print a message, you can have multiple functions with the same name but different parameters
};

void printer::print() { // function definition for print without parameters
    cout << "Printing from printer::print()" << endl;
}

void printer::print(string msg) { // function definition for print with string parameter
    cout << msg << endl;
}

class Box {
public:
    Box(); // default constructor
    Box(int size);// constructor with one parameter
    Box(int w, int h);// constructor with two parameters
    // you can have multiple constructors with different parameters, this is called constructor overloading, allows intializing objects in different ways
};

Box::Box() {
    cout << "Box default constructor called" << endl; // default constructor initializes the object without any parameters
}

Box::Box(int size) {
    cout << "Box constructor with size: " << size << endl; // constructor with one parameter initializes the object with a single size parameter
}

Box::Box(int w, int h) { 
    cout << "Box constructor with width: " << w << " and height: " << h << endl; // constructor with two parameters initializes the object with width and height
}

class counter {
    int count = 0; // member variable initialized to 0
public:
    counter& increment(){
        ++count; // increment the count by 1
        return *this; // return the current object by reference, allows chaining of increment calls
    }
    counter& reset(){
        count = 0; // reset the count to 0
        return *this; // return the current object by reference, allows chaining of reset calls
    }
};

int main(){
    Point p;
    cout << "Point coordinates: (" << p.getX() << ", " << p.getY() << ")" << endl;

    printer pr;
    pr.print();
    pr.print("Hello, World!");

    Box b1; // default constructor
    Box b2(10); // constructor with one parameter
    Box b3(10, 20); // constructor with two parameters

    counter c;
    c.increment().increment().reset(); // chaining increment and reset calls

    return 0;
}
