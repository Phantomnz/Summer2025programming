#include <iostream>
using namespace std;
extern "C" { // C linkage for the function, allows use of c headers in C++
  #include "d4practice.h"
}
int add(int, int); //function prototype, you will need to define this function later
inline int square(int x) { return x * x; } //inline function, used to define a function that is small and called frequently
void greet(string name = "Guest"); //function prototype with default argument


int main(){
    int result = add(3, 4); 
    int squared = square(5); 
    greet();
    cout << "The sum is: " << result << endl; //output the result of the add function
    cout << "The square is: " << squared << endl; //output the result of the square function
}

int add(int a, int b) { //function definition
    return a + b;
}

void greet(string name){ //function definition with default argument
    cout << "Hello, " << name << "!" << endl;

}