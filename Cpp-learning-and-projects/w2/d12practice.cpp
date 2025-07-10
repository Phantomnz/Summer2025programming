#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class A { public: void showA();}; // C++ allows multiple inheritance
class B { public: void showB();}; // so class C can inherit from both A and B as base classes
class C : public A, public B {
public:
    void showC() {
        std::cout << "Class C" << std::endl;
    }
};


void A::showA() {
    std::cout << "Class A" << std::endl;
}
void B::showB() {
    std::cout << "Class B" << std::endl;
}


class Base {};
class D : virtual public Base {}; // Virtual inheritance to avoid ambiguity in diamond problem
class E : virtual public Base {}; // E also inherits from Base virtually
class F : public D, public E {}; // F inherits from both D and E
// when 2 bases inherit from the same base class, we use virtual inheritance to avoid ambiguity

float x = 4.35f; // float variable
int y = static_cast<int>(x); // static_cast to convert float to int
// static_cast is used for safe conversions between types
// y will be 4, as static_cast truncates the decimal part

int *p = new int(10); // Dynamically allocate an integer and initialize it to 10


unique_ptr<int> uptr = make_unique<int>(10); // Create a unique pointer to an integer initialized to 10
// unique_ptr automatically manages memory and deletes the integer when it goes out of scope

shared_ptr<int> sptr = make_shared<int>(20); // Create a shared pointer to an integer initialized to 20
// shared_ptr allows multiple pointers to share ownership of the same integer

int main(){
    C objC; // Create an object of class C
    objC.showA(); // Call method from base class A
    objC.showB(); // Call method from base class B
    objC.showC(); // Call method from class C

    F objF; // Create an object of class F
    // objF can access members of D and E through virtual inheritance

    cout << "Value of y after static_cast: " << y << endl; // Output the value of y

    cout << "Unique pointer value: " << *uptr << endl; // Output the value managed by unique_ptr
    cout << "Shared pointer value: " << *sptr << endl; // Output the value managed by shared_ptr
    delete p; // Free the dynamically allocated memory
    return 0;
}