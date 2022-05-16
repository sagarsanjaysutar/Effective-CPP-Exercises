#include <iostream>
#include <iterator>
#include <vector>
#include <string.h>

using std::cout;
using std::endl;

class WordBlock
{
public:
    explicit WordBlock(std::string word);
    /*!
     *  Overloading "+" operator. It returns a const value.
     */
    std::string operator+(const WordBlock &rhsWord);
    void operator=(const WordBlock &rhsWord);

private:
    std::string m_word;
};

WordBlock::WordBlock(std::string word) : m_word(word) {}

std::string WordBlock::operator+(const WordBlock &rhsWord)
{
    cout << "Appending " << rhsWord.m_word << " to " << m_word << endl;
    m_word.append(rhsWord.m_word);
    return m_word;
}

void WordBlock::operator=(const WordBlock &rhsWord)
{
    cout << "Replacing " << m_word << " with " << rhsWord.m_word << endl;
    m_word = rhsWord.m_word;
}

int main()
{

    std::vector<int>
        numbers = {1, 23, 3, 435, 423};

    // A normal vector iterator that acts as a pointer which points to a certain vector.
    std::vector<int>::iterator iter = numbers.begin();

    /*! #00
     * A const vector iterator that acts a a const pointer i.e.
     * it can't point to anything different but we can modify the value that it points to.
     *
     * An iterator which point to something that can be modified.
     */
    const std::vector<int>::iterator intIter = numbers.begin();
    *intIter = 45; // Allowed. Changed the value that the pointer points to.
    // intIter++;     // Error. Incrementing the pointer. It can't point to anything different.

    /*! #01
     * Using const_iterator.
     * An iterator which point to something that can't be modified.
     */
    std::vector<int>::const_iterator constIter = numbers.begin();
    // *constIter = 45; // Error. Can't change the value that pointer points to.
    constIter++; // Allowed. Inrementing the pointer.

    /*! #03
     * Returning a const value from a function.
     * Good idea as client errors are reduced and safety is maintained;
     * See Item 24
     */
    WordBlock word1("Sagar ");
    WordBlock word2("Sutar");
    WordBlock word3("Random");

    word2 = word3;
    cout << "Result" << word1 + word2 << endl; // The addition here returns a const value.

    return 0;
}