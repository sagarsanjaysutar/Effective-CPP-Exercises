/**
 * \brief Item 14: Think carefully about copying behaviour in resource-managing classes.
*/

#include <iostream>
using namespace std;

class SmartPtr{
public:
    SmartPtr(){
        cout << "SmartPtr: Default Constructor called. " << this << endl;
    }

    ~SmartPtr(){
        cout << "SmartPtr: Destructor called. " << this << endl;
    }
    
};

int main(){

    return 0;
}