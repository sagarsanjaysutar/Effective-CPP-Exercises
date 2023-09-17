/**
 * \brief Item 28: Avoid returning "handles" to object internals
 * 
 * 1. Object internals can be it's private members. Considering that for user defined classes,
 *  it's better to pass the class's objects by reference, if any of the class's function returns a reference 
 *  to the private variable (handler), the encapsulation of the class is broken.
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
};

int main()
{
    Number obj;

    // 01. The following breaks encapsulation as client gets reference to a private var.
    int *numPtr = &obj.getNumber(); 
    // Now the client is able to change private variable of the class. 
    ++(*numPtr);
    cout << "Number: " << *numPtr << "\t" << obj.getNumber() << endl;

    // // 02. Trying the same with const class
    // const Number constObj;
    // cout << "Const Number: " << *numPtr << "\t" << constObj.getNumber() << endl;
}