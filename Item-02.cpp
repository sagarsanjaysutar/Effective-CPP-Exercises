/**
 * \brief Item 2: Use const whenever possible.
 * Trying not to use #define macro.
 * Benefits:
 * 1. Semantic (syntactical) constraint is provided to the object i.e. const keyword.
 * 2. 
 */

#include <iostream>
#include <vector>
#include <array>
using namespace std;

/** #00 Defining a Constant Pointer.
 *  const int *objPtr = ....;   // Data becomes const
 *  int *const objPtr = ....;   // Pointer becomes const
 *
 * Both "pointer" and "value that pointer point to" is declared const.
 * because more often than not, this header file will be included in many source files.
 *
 * \todo Figure out why can't we do the same for integer i.e. const int *const ASPECT_RATIO = 12; ??
 * Refer: https://stackoverflow.com/questions/18048140/int-and-const-int-initialization-and-conversion-in-c
 */
const char *const ASPECT_RATIO = "12";

class Generic
{
public:
    Generic() : 
     m_monthArr({"Jan", "Feb"}),
     m_monthArrPtr(&m_monthArr[0]),
     m_mutableMonthArr({"Nov", "Dec"}),
     m_mutableMonthArrPtr(&m_mutableMonthArr[0]){}
    ~Generic(){}

    /*! #01
     * Declaring class-specific const. Make it static.
     * Can't make class specific #define MACRO i.e. no encapsulation.
     */
    static const int NumOfMonths = 12;

    /**
     * \brief This is an unsafe function as it return's a private pointer member. 
     * This member function passes the compiler's "bitwise" const pre-check, but this function doesn't ACT const.
     * Refer typesOfConst() example.
    */
    std::string* getFirstMonthName() const{
        return m_monthArrPtr;
    }

    /**
     * \brief Still an unsafe function as it return's a private pointer members,
     * but notice that despite being a const function, we can assign values to member variables. 
     * This demonstrates logical const.
    */
    std::string* getMonthName(int monthNum) const{
        m_mutableMonthArrPtr = &m_mutableMonthArr[monthNum];
        return m_mutableMonthArrPtr;
    }

    
private:
    std::array<std::string, NumOfMonths> m_monthArr;
    std::string *m_monthArrPtr;

    // mutable is used for logical const where we allow modification of members in const function
    mutable std::array<std::string, NumOfMonths> m_mutableMonthArr;
    mutable std::string* m_mutableMonthArrPtr;
};

/**
 * \brief Demonstrates various uses of const pointer or const-data pointer
*/
void runConstIterators(){
    std::vector<int> intVec = {1, 45, 24, 34, 53, 10, 23};

    // 1. Normal iterator is just a pointer, thus the following work.    
    std::vector<int>::iterator vecItr = intVec.begin();
    vecItr++;                   // The pointer points to next element. 
    ++(*vecItr);                // Deference the iterator & increment the data it points to.   
    cout << "intVec:";
    for(vecItr; vecItr != intVec.end(); ++vecItr){ 
        cout << " " << *vecItr; 
    }
    cout << "\n";

    // 2. const-data pointer/const_interator: The data pointed by the iterator cannot be changed. 
    // Iterator can point to different data. 
    std::vector<int>::const_iterator vecConstDataItr = intVec.begin();
    // ++(*vecConstDataItr);    // Error as we are trying to change data.
    vecConstDataItr++;

    // 3. const iterator: The iterator (pointer) cannot be changed, data it points to can be. 
    const std::vector<int>::iterator vecConstItr = intVec.begin();
    ++(*vecConstItr);
    // vecConstItr++;           // Error as we are trying to change what the pointer points to. 
}

void typesOfConst(){
    /**
     * 1. Bitwise/Physical/Default const
     * Precondition: No assignments to member variables for it to be const function. Compiler detect this.
     *
     * Flaw
     * In the following example, the getFirstMonthName() returns a pointer which points to an internal private array.
     * Despite being a bitwise const function, the client can mutate the result as follow
     * 
     * Solution
     * getFirstMonthName() should returns a const data-pointer 
     */ 
    Generic obj;
    std::string* monthPtr = obj.getFirstMonthName();
    *monthPtr = "Sep";
    cout <<  "Modified Month: " << *obj.getFirstMonthName() << endl;

    /**
     * 2. Logical const
     * If you anyway want to mutate a member variable in a const function, use the mutable keyword.
    */
   std::string* monthNameItr = obj.getMonthName(1);
   *monthNameItr = "Jun";
   cout <<  "Modified Month: " << *obj.getMonthName(1) << endl;
}

int main(){

    // runConstIterators();
    typesOfConst();

    return 0;
}