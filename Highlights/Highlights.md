
# Highlight points

## Points to keep in mind

1. (Pg. 124) Pass by reference (for user defined classes) is efficient than pass by value.

1. Item 28: If Class B is within Class A & it's declared as the first data member, then Class A & Class B will have same addresses.  This continues downstream as well i.e. if Class C is within Class B as the first data member, then Class A, B & C will have same addresses. [Refer](https://stackoverflow.com/a/14481302)

1. Stack vs Heap
 Stack: Where local variables/object get stored. Objects get deleted once out of scope. For limited use only, can't make huge objects. Heap: Objects initialised with new keyword. Must be manually freed.

1. If you have both copy constructor & assignment operator overloaded, then the following will call the copy constructor, not the assignment operator. [Refer](https://stackoverflow.com/a/64693952/22622355).

   ```cpp
    Random obj;
    Random obj1 = obj
   ```

    This will call the assignment operator

    ```cpp
        Random obj, obj1;
        obj1 = obj;
    ```
