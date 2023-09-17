/**
 * \brief The following code produces an undefined behaviour where we are able to
 *  access data member of a delete variable. This delete variable is a dangle pointer.
 * \ref https://stackoverflow.com/a/1930474
 * \note Picked up from Effective C++ Page 19
*/
#include <iostream>
using namespace std;

class Internal{
public:
	Internal() { cout << "Internal: Default Constructor Called. " << this << endl; }
	~Internal(){ cout << "Internal: Destructor Called. " << this << endl; }
	std::string getRandomStr(){ return "Sagar"; }
};

class Rectangle{
public:
	Rectangle() : m_intObj(){ cout << "Rectangle: Default Constructor Called. " << this <<endl; }
	~Rectangle(){ cout << "Rectangle: Destructor Called. " << this << endl; }
	// Note that a "reference" is returned here.
	Internal &getInternal(){ return m_intObj; }
private:
	Internal m_intObj;
};

class GUI{
public:
	GUI() : m_rec() { cout << "GUI: Default Constructor Called. " << this << endl; }
	~GUI(){ cout << "GUI: Destructor Called. " << this << endl; }
	// Note that a "value" is returned here.
	Rectangle getRectangle(){ return m_rec; }
private:
	Rectangle m_rec;
};

int main() {
	GUI guiObj;
	cout << "\n============================" << endl;
	// Note: Keep a keen eye to the memory addresses. 
	// 1. Calling guiObj.getRectangle() returns a new temp Rectangle obj.
	// 2. Calling guiObj.getRectangle().getInternal() returns the m_intObj of this temp Rectangle obj.
	// 3. Calling &(guiObj.getRectangle().getInternal()) returns the address of this m_intObj.
	// 4. We store that address in Internal *intObj.
	// 5. At the end of this line, the temp Rectangle obj is delete & thereby the it's Internal obj is also deleted.
	// 6. Despite the temp Internal obj being deleted, calling "intObj->getRandomStr()" works.
	// 7. This is because we've already stored the deleted temp Internal's address in intObj.
	Internal *intObj = &(guiObj.getRectangle().getInternal());	
	cout << "Address of intObj: " << intObj << endl;
	cout << "Access member of intObj: " << intObj->getRandomStr() << endl;	
	cout << "============================\n" << endl;
	return 0;
}