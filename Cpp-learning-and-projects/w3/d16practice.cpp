#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
using namespace std;

class File{
    ofstream out;
public:
    File(const string& name) : out(name) { 
        if (!out) {
            cerr << "Error opening file: " << name << endl;
            exit(1);
        }
    }
    ~File() { out.close(); }
};
// RAII (Resource Acquisition Is Initialization) is a programming idiom that ensures resources are properly released when they are no longer needed.
// C++ uses RAII to manage resources. A constructor acquires resources (like memory or file handles) and a destructor releases them (when the object goes out of scope).
// This ensures that resources are properly cleaned up, preventing leaks and other issues.

/*Exception Safety Levels
    
    C++ functions aim for different exception safety guarantees:
    
    - Basic: No resource leaks.
    - Strong: State is unchanged on failure.
    - No-throw: Guarantees no exceptions.*/


int main() {
    // Example of RAII with file handling
    try {
        File myFile("example.txt");
        // Perform file operations here
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    // Example of smart pointers
    unique_ptr<int> p1 = make_unique<int>(10); // Using unique_ptr for automatic memory management
    // unique_ptr automatically deletes its pointer automatically when it goes out of scope, cannot be copied but can be moved.
    shared_ptr<int> p2 = make_shared<int>(20); // Using shared_ptr for shared ownership
    // uses reference counting to delete the pointer when the last shared_ptr goes out of scope.
    shared_ptr<int> p3 = p2; // p3 shares ownership of the same integer as p2
    weak_ptr<int> p4 = p2; // weak pointer does not participate in owndership, it can be used to check if the shared pointer is still valid without affecting its reference count.
    // weak_ptr is used to avoid circular references in shared_ptr.

    cout << "Unique pointer value: " << *p1 << endl;
    cout << "Shared pointer value: " << *p2 << endl;
    cout << "Weak pointer value (expired): " << (p4.expired() ? "expired" : "valid") << endl;

    return 0;
}