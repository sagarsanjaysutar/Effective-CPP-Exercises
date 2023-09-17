/*!
 * \brief Experimenting with obscure C++ code.
 * \note Picked up from Effective C++ Page 7.
 */

#include <iostream>

/*!
 * Trying to print a null pointer.
 * O/P: Won't print anything. Won't let other function execute which are called after this.
 */
void printingNullPtr()
{
    int *ptr = 0;
    std::cout << "Trying to print null ptr." << std::endl;
    std::cout << *ptr << std::endl;
}

/*!
 * Trying to access out of range element of array.
 * O/P: Prints different letters
 */
void outOfRangeArrAccess()
{
    char name[] = "Sagar";
    std::cout << "Trying to access out of range element of array." << std::endl;
    std::cout << name[10] << std::endl;
}

int main()
{
    outOfRangeArrAccess();
    printingNullPtr();
    return 0;
}