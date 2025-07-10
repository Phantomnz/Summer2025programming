#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Point {
    int x = 1; // default value for x
    int y = 1; // default value for y
    Point() = default; // Default constructor
    Point(const Point& other) : x(other.x), y(other.y) {} // copy constructor, a special constructor that creates a new object as a copy of an existing object

};

// using an intializer list is more efficient and required for const or reference members
// assigning in the body works, but might cause a default construction followed by reassignment

struct Coord {
    int a = 1; // default value for a
    int b = 2; // default value for b
    Coord(int a) : Coord(a, 0) {} // constructor with one parameter, initializes b to 0
    Coord(int a, int b) : a(a), b(b) {} // constructor with two parameters
    // one constructor can call another constructor in the same class
};

//destructors are mentioned again for day 9, but they are not used in this code
//look at day 7 for more information on destructors

int main() {
    Point p1; // default constructor
    Point p2(p1); // copy constructor

    Coord c1(5); // calls Coord(int a)
    Coord c2(3, 4); // calls Coord(int a, int b)

    cout << "Point p1: (" << p1.x << ", " << p1.y << ")" << endl;
    cout << "Point p2: (" << p2.x << ", " << p2.y << ")" << endl;
    cout << "Coord c1: (" << c1.a << ", " << c1.b << ")" << endl;
    cout << "Coord c2: (" << c2.a << ", " << c2.b << ")" << endl;

    return 0;
}