/**
 * \brief Item 2: Use const whenever possible.
 * Trying not to use #define macro.
 * Benefits:
 * 1. Semantic (syntactical) constraint is provided to the object i.e. const keyword.
 * 2. 
 * 
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
     * \brief This demonstrates bitwise const.
     * This is an unsafe function as it return's a private pointer member. 
     * This member function passes the compiler's "bitwise" const pre-check, but this function doesn't ACT const.
     * Refer typesOfConst() example.
     * 
     * \ref https://stackoverflow.com/a/8788917
    */
    std::string* getMonthNamePtr() const{
        return m_monthArrPtr;
    }

    /**
     * \brief This demonstrates logical const.
     * Still an unsafe function as it return's a private pointer members,
     * but notice that despite being a const function, we can assign values to member variables.
     * Refer typesOfConst() example.
    */
    std::string* getMonthNamePtr(int monthNum) const{
        m_mutableMonthArrPtr = &m_mutableMonthArr[monthNum];
        return m_mutableMonthArrPtr;
    }

    /**
     * \brief Const function. This directly gets called if `const Generic obj` is declared.
    */
    const std::string& getValidMonthName(int monthNum) const{
        cout << "const getValidMonthName(...) called." << endl;
        if(monthNum >= 1 && monthNum <= 12){
            return m_monthArr.at(monthNum);
        }
    }

    /**
     * Non-const function. This gets called if `Generic obj` is declared.
     * We want to call the const version of this function to avoid code duplication, there is no direct way. 
    */
    std::string& getValidMonthName(int monthNum){
        cout << "Non-const getValidMonthName(...) called." << endl;
        return const_cast<std::string&>(                                    // 02. Remove the const from the return value.
            static_cast<const Generic>(*this).getValidMonthName(monthNum)   // 01. Cast the "non-const" instance of Generic into a const one.
        );
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
 * \note In following example, we've changed the data that the pointer points to but we can't do the same references.
 * \ref https://stackoverflow.com/a/7713317
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
    std::string* monthPtr = obj.getMonthNamePtr();
    *monthPtr = "Sep";
    cout <<  "Modified Month: " << *obj.getMonthNamePtr() << endl;

    /**
     * 2. Logical const
     * If you anyway want to mutate a member variable in a const function, use the mutable keyword.
    */
   std::string* monthNameItr = obj.getMonthNamePtr(1);
   *monthNameItr = "Jun";
   cout <<  "Modified Month: " << *obj.getMonthNamePtr(1) << endl;
}

void constNonConstFunc(){
    const Generic constObj;
    Generic obj;

    // constObj.getValidMonthName(1);
    obj.getValidMonthName(1);
}

int main(){

    // runConstIterators();
    // typesOfConst();
    constNonConstFunc();

    return 0;
}