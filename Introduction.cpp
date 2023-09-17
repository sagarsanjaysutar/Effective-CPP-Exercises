/*!
 * \brief Experimenting with different constructors and different function types.
 * \note Picked up from Effective C++ Page 5.
 * \link https://courses.washington.edu/css342/zander/css332/passby.html
 * \link https://www.geeksforgeeks.org/passing-by-pointer-vs-passing-by-reference-in-c/
 */

#include <iostream>
using std::cout;
using std::endl;

class Constructors
{
public:
    int m_number;
    Constructors(int number);                         // Declare Default constructor
    Constructors(const Constructors &rhs);            // Declare Copy constructor
    Constructors &operator=(const Constructors &rhs); // Declare Copy Assignment Operator
};

Constructors::Constructors(int number)
{
    m_number = number;
}

/*!
 * \brief Pass-by-Value functions and Obj2(Obj1) call Copy Constructor. If not defined explicitly, it is implicitly defined.
 */
Constructors::Constructors(const Constructors &rhs)
{
    cout << "Copy Construct called. " << endl;
    m_number = rhs.m_number;
}

/*!
 * \brief Copy Assignment Operator. If not defined explicitly, it is implicitly defined.
 * This will be called whenever you do Constructors obj1,obj2; obj1 = obj2;
 */
Constructors &Constructors::operator=(const Constructors &rhs)
{
    cout << "Copy Assignment operator called." << endl;
    m_number = rhs.m_number;
}

/*! \brief Call-by-value function.
 *
 * Can either have this or Call-By-Reference function in a code, but not both.
 * From wherever this function is called, the Copy Constructor of the class is also called for the parameter,
 * as it's being copied from source object to function paramter object.
 */
// void randomFunction(Constructors objVal)
// {
//     cout << "Pass-by-value function called." << endl;
// }

/*!
 * \brief Call-by-pointer function.
 *
 * This does not call the Copy constructor of the class as only address is being passed around.
 */
void randomFunction(Constructors *objPtr)
{
    cout << "Pass-by-pointer function called." << endl;
}

/*! \brief Call by Reference function
 *
 * This does not call the Copy constructor of the class as only reference is being passed around(i.e. address)
 */
void randomFunction(Constructors &objRef)
{
    cout << "Pass-by-reference function called." << endl;
}

int main()
{
    Constructors cObj(10);    // Normal object creation.
    Constructors cObj1(112);  // Normal object creation.
    Constructors cObj2(cObj); // Calling Copy Constructor
    cObj = cObj1;             // Calling Copy Assignment operator

    randomFunction(cObj);  // Pass by Reference or Pass by Value is called based on which function uncommented.
    randomFunction(&cObj); // Pass by Pointer is called.

    return 0;
}