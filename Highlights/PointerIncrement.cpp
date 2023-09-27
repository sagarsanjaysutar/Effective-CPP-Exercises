/*!
 * \brief Picked up from a CV tutorial
 * \link https://github1s.com/opencv/opencv/blob/3.4/samples/cpp/tutorial_code/core/mat_mask_operations/mat_mask_operations.cpp#L95-L96
 * \link https://stackoverflow.com/a/55085988
 */
#include <iostream>
using namespace std;

void pointerIncrement(){
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
}

int main()
{
    pointerIncrement();
    return 0;
}
