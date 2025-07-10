#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// overriding means redefining a base (virtual) class function in a derived class/subclass
// overloading means defining a function with the same name but different parameters in the same scope

class Base { // a class with at least one pure virtual function is called an abstract class
    // an abstract class cannot be instantiated, meaning you cannot create objects of it directly
    // it is meant to be a base class for other classes to derive from
    // it can contain both pure virtual functions and regular member functions
    // pure virtual functions are declared by assigning 0 to them, e.g., virtual void show() = 0;
    // pure virtual functions must be overridden in derived classes, otherwise the derived class will also become abstract
    // this class is a polymorphic base class, meaning it can be used to refer to objects of derived classes through base class pointers or references
public:
    virtual void show(){ cout << "Base class show function called." << endl; }// virtual keyword allows this function to be overridden in derived classes, enabling polymorphism
    virtual ~Base() = default; // virtual destructor for proper cleanup of derived class objects
    // a virtual destructor ensures that when a derived class object is deleted through a base class pointer, the derived class's destructor is called
    // so always use virtual destructors if the class is intended to be a base class/inherited from
};

class Derived : public Base {
public:
    void show() override final{ cout << "Derived class show function called." << endl; }// final keyword prevents further overriding of this function in any derived classes
    ~Derived() override { cout << "Derived class destructor called." << endl; } // override keyword ensures this destructor overrides the base class destructor
};

// override keyword is used to indicate that a function is intended to override a base class virtual function, and ensures it does so correctly

int main() {
    Base *basePtr = new Base(); // creating an object of the base class
    basePtr->show(); // calls the base class show function
    delete basePtr; // cleans up the base class object, calling the base class destructor
    Base* b = new Derived(); // base class pointer pointing to derived class object
    b->show(); // calls the overridden show function in the derived class
    delete b; // cleans up the derived class object, calling the derived class destructor
    return 0;
}