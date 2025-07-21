#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Point { // a structure to represent a point in 2D space
    int x, y;
    Point(int x, int y) : x(x), y(y) {} // Constructor to initialize x and y
    void print() { // Method to print the point coordinates
        cout << x << ", " << y << endl;
    }
};

class Pointl { // a class to represent a point in 2D space
    int a, b;
public: // Public access specifier to allow access to members
// public members can be accessed from outside the class
    Pointl(int a, int b) : a(a), b(b) {} // Constructor to initialize a and b
    void print() { // Method to print the point coordinates
        cout << a << ", " << b << endl;
    }
};
int main(){
    Point p1(10, 20); // Create a point at (10, 20)
    p1.print(); // Print the point
    Pointl p2(30, 40); // Create another point at (30, 40)
    p2.print(); // Print the second point
}