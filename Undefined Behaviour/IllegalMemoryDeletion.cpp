/**
 * \brief Stack & Heap memory allocation & deallocation's illegal use. 
 * \ref https://icarus.cs.weber.edu/~dab/cs1410/textbook/4.Pointers/dynamic.html 
*/
#include <iostream>
using namespace std;

class Person{
public:
    Person() {cout << "Person: Created\n"; }
    ~Person() {cout << "Person: Destroyed\n"; }
};

int main(){
    cout << "0\n";
    Person	p;          // Created on stack
    cout << "1\n";
    Person*	p2 = &p;    // Address stored in p2
    cout << "2\n";
    delete p2;          // Address deleted.
    cout << "3\n";
    // Seg fault here, because we've manaully deleted a stack variable 
    // which in itself is responsible for automatically deleting stack variable.
    return 0;
}
