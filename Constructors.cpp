#include <iostream>

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
 * Pass by Value is calling Copy Constructor. If not defined explicitly, it is implicitly defined.
 */
Constructors::Constructors(const Constructors &rhs)
{
    m_number = rhs.m_number;
}

/*!
 * Copy Assignment Operator. If not defined explicitly, it is implicitly defined.
 */
Constructors &Constructors::operator=(const Constructors &rhs)
{
    m_number = rhs.m_number;
}

int main()
{
    Constructors cObj(10);
    Constructors cObj1(112);
    Constructors cObj2(cObj); // Calling Copy Constructor
    cObj = cObj1;             // Calling Copy Assignment operator

    std::cout << "cObj Number: " << cObj.m_number << std::endl;
    std::cout << "cObj1 Number: " << cObj1.m_number << std::endl;
    std::cout << "cObj2 Number: " << cObj2.m_number << std::endl;
    return 0;
}