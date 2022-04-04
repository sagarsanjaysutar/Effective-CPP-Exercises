#include <iostream>

int main()
{

    /*!
        Post increment(b++) increments b,
        then returns the previous value of b.

        Pre increment(++b) increments b,
        then returns the new value of b.
    */

    int numbers[] = {10, 34, 11, 56, 98};
    int *numbersPtr = &numbers[4]; // Pointer pointing at 2nd element.
    // Pointer is preincremented i.e. it points at next element (in this case: from 2nd to 3rd)
    // then 982 is placed at 3rd index.
    // Basically assigning value to next item.
    *(++numbersPtr) = 982;

    for (int num : numbers)
    {
        std::cout << num << std::endl;
    }

    return 0;
}