/**
 * \brief Highlight points.
 *
 * Points to keep in mind.
 * 
 * 1. (Pg. 124) Pass by reference (for user defined classes) is efficient than pass by value.
 * 
 * 2. Item 28: If Class B is within Class A & it's declared as the first data member, then Class A & Class B will have same address.
 *  This continues downstream as well i.e. if Class C is within Class B as the first data member, then Class A, B & C have same addresses.
 * \ref https://stackoverflow.com/a/14481302
 * 
 */
