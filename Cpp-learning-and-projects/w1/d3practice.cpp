#include <iostream>
using namespace std;

int x = 2;

void sayHello(){ //void function, so it doesn't return anything
    //void functions are useful for printing or doing something without returning a value
    cout << "Hello";
}

int square(int x){ //square function takes an integer and returns its square
    //this is a local variable, so it doesn't affect the global variable x
    x = x * x;
    return x;
}

void increment(int& x){ //increment function takes a reference to an integer and increments it
    //the & next to int allows the function to modify the original variable
    x++;
}

main(){
    cout << "Initial value of x: " << x << endl;
    cout << "Square of x: " << square(x) << endl;
    cout << "Value of x after square, showing that the original value is unchanged: " << x << endl;
    increment(x);
    cout << "Value of x after increment, showing how some functions can change global values: " << x << endl;
}