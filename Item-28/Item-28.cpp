/**
 * \brief Item 28: Avoid returning "handles" to object internals
 * 
 * 1. Object internals can be it's private members. If any of the class's functions return a reference 
 *  to a private variable (handler) then the encapsulation of that class is broken.
 *  The client now has reference to class's private member. 
*/

#include <iostream>
using namespace std;

class Number
{
private:
    int m_num = 5;
public:
    // Function returning a reference to private variable.
    int &getNumber() { return m_num; }   
    const int& getConstNumber() { return m_num; } 
};

int main()
{
    Number obj;

    // 01. The following breaks encapsulation as client gets reference to a private var.
    int *numPtr = &obj.getNumber(); 
    // Now the client is able to change private variable of the class. 
    ++(*numPtr);
    cout << "Number: " << *numPtr << "\t" << obj.getNumber() << endl;

    // 02. The above problem can be solved by returning a const private var. 
    const int* numConstPrt = &obj.getConstNumber();  
    // ++(*numConstPrt); This now fails. 
    cout << "Const Number: " << *numConstPrt << endl;
    
    
}