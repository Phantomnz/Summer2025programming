#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Counter {
    static int count; // Static member is shared across all instances of the class
public:
    Counter() { ++count; } // Constructor increments the static count
    static int getCount(){ return count;} // Static member function to access the static count
};

int Counter::count = 0; // Initialize static member
// must be defined outside the class

class Sample {
    const int id; // Constant member must be initialized in the constructor
    // or in the member initializer list
    public:
    Sample(int x) : id(x) {cout << "Sample created with id: " << id << endl;} // Constructor with member initializer list, const members must be initialized this way
};

class Box {
    int value = 1; // Default member initializer, value is initialized to 1
    friend void show(Box b); // Friend function declaration, friend function can access private and protected members of the class
};

void show(Box b) {
    cout << "Value: " << b.value << endl; // allowed because friend function show can access private members
}

class Animal {
public:
    void speak(){ cout << "generic animal sound\n" << endl; }//  (technically not stated to be) Virtual function to be overridden by derived classes
};

class Dog : public Animal {
public:
    void bark(){ cout << "Woof!\n"<< endl;}// Specific function for Dog class
};
// one class can inherit from another class, this is called inheritance

class Parent {
protected:
    int protectedValue; // Protected member, accessible from within the class and derived classes/subclasses but not from outside
};

class Child : public Parent {
    public:
    void access(){ protectedValue = 10;
        cout << "Accessing protected member: " << protectedValue << endl; 
        // Accessing protected member from Parent class
    }// Accessing protected member from Parent class
};

int main(){
    Counter c1, c2, c3; // Create three instances of Counter
    cout << "Count: " << Counter::getCount() << endl; // Access static member function to get count

    Sample s(3); // Create an instance of Sample with id initialized to 3

    Box b; // Create an instance of Box
    show(b); // Call friend function to show value

    Dog d; // Create an instance of Dog
    d.speak(); // Call base class function
    d.bark(); // Call Dog specific function

    Child child; // Create an instance of Child
    child.access(); // Access protected member through Child class
    return 0;
}