/**
 * \brief Item 13: Use objects to manage resources.
 * 
 * Resources can be dynamically allocated memory, file descriptors, mutex locks, database connections,
 * network sockets, etc. These are generally allocated on the heap, not on stack.
 * 
 * It's best to have a resource manager as opposed to manually freeing them. 
 * 
 * 
*/

#include <iostream>
#include <memory>

using namespace std;

class Generic{
public:
    Generic(){ cout << "Generic: Default constructor called.\t" << this << endl; }
    ~Generic(){ cout << "Generic: Destructor called.\t" << this << endl; }
};

void smartPointer(){
    // A regular C++ ptr
    int *intPtr = new int[3]{1, 3,4};

    /**
     * \brief Auto Ptr (Depreciated). 
     * Unusual behaviour:
     * 1. Exclusive data ownership i.e. two auto pointers cannot points at same data.
     * 2. Copying the pointer is allowed where the data ownership is transferred to the another pointer & it becomes null.
     * This is unusual copying behavior.
    */
    std::auto_ptr<Generic> objAutoPtr(new Generic());
    std::auto_ptr<Generic> objAutoPtrCopy(objAutoPtr);  // Copying allowed. Ownership transferred. objAutoPtr is null.
    // std::auto_ptr<Generic> objAutoPtrCopy(objAutoPtr.get()) ;    // Seg Fault as two ptr points to same data.

    /**
     * \brief Unique Ptr
     * Exclusive data ownership. The pointer cannot be copied.
     * It can transfer the ownership.
    */
    std::unique_ptr<Generic> objUniquePtr = std::make_unique<Generic>();
    //std::unique_ptr<Generic> objUniquePtrCopy = objUniquePtr;             // Copying is not allowed
    std::unique_ptr<Generic> objUniquePtrNew = std::move(objUniquePtr);    // Transferring is allowed

    /**
     * \brief Shared pointer
    */
    std::shared_ptr<Generic> objSharedPtr = std::make_shared<Generic>();
    std::shared_ptr<Generic> objSharedPtrCopy = objSharedPtr;   // Usual Copying allowed

    // Although this can point to a dynamically allocated array, it won't delete it 
    // as shared_ptr uses `delete` not `delete[]`
    // std::shared_ptr<int[]> arrSharedPtr = std::make_shared<int[5]>(1,2,3,4,5);
    // std::shared_ptr<string[]> arrSharedPtr = std::make_shared<string[1]>("1,2,3,4,5");
}

int main(){
    smartPointer();
    return 0;
}