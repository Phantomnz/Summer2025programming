#include <iostream>
#include "MyHeader.h"
#include <vector>

using namespace std;



namespace Mynamespace {
    void myFunction() {
        cout << "Hello from Mynamespace!" << endl;
    }
}
// This code defines a namespace called Mynamespace and a function called myFunction within it.

//Directive (`using namespace std;`) imports all names from `std`.

//Declaration (`using std::cout;`) imports just one name, reducing risk of name clashes.

vector<int> nums; // This code declares an empty vector of integers called nums.

main() {
    cout << "Hello, World!" << endl; // Output: Hello, World!

    Mynamespace::myFunction(); // Call the function from the namespace

    nums.push_back(1); // This code adds the integer 1 to the end of the vector nums.

    int x = nums[0]; // This code retrieves the first element of the vector nums and assigns it to the variable x.

    nums.size(); // This code retrieves the size of the vector nums.

    return 0;
}

