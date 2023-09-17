#include <iostream>
#include <iterator>
#include <vector>
#include <string.h>
#include <sstream>
#include <ostream>
#include <cstring>

using std::cout;
using std::endl;

class WordBlock
{
public:
    /*!
     * Construct to build empty object.
     */
    WordBlock();

    /*!
     * Constructor to build object like
     * \code WordBlock obj = "Anyword"; or WordBlock obj("Anyword");
     */
    WordBlock(const char *word);

    /*!
     * Constructor to build object like
     * \code WordBlock obj = obj0; or WordBlock obj(obj0);
     */
    WordBlock(const WordBlock &word);

    std::size_t getWordLen() const;

    /*!
     * Destructor
     */
    ~WordBlock();

    // Operator overloading
    const std::string operator+(const WordBlock &rhsWord); //!< It returns a const value.
    void operator=(const WordBlock &rhsWord);
    void operator=(const std::string rhsWord);
    const char &operator[](std::size_t pos);

    /*!
     * Had to make it a "friend" function to access the private member var.
     * This is because the stream operator(<<) has 'ostream' as the first parameter.
     * Thus it can't be a member function like other operators.
     * \link https://stackoverflow.com/a/237074/15060921
     * \link https://stackoverflow.com/a/1905502/15060921
     */
    friend std::ostream &operator<<(std::ostream &os, const WordBlock &rhsWord);

private:
    std::string m_word;

    // Making both the var. mutable, so it could be edited in bitwise const function.
    mutable std::size_t m_wordLength;
    mutable bool m_wordLengthValid;

    bool setWord(std::string word);

    // Constant(bitwise) member function i.e. it won't change class's member vars. https://stackoverflow.com/a/21478486/15060921
    std::string getWord() const;
};

WordBlock::WordBlock(const char *word) : m_word(word)
{
    cout << "WordBlock: Intializing with a char pointer: " << getWord() << endl;
}

WordBlock::WordBlock(const WordBlock &word) : m_word(word.getWord())
{
    cout << "WordBlock: Intializing with a WordBlock: " << getWord() << endl;
}

WordBlock::WordBlock()
{
    cout << "WordBlock: Intializing with an empty object" << endl;
}

WordBlock::~WordBlock() {}

bool WordBlock::setWord(std::string word)
{
    if (word != m_word)
    {
        m_wordLengthValid = false;
        m_word = word;
    }
}

std::string WordBlock::getWord() const
{
    return m_word;
}

std::size_t WordBlock::getWordLen() const
{
    if (!m_wordLengthValid)
    {
        m_wordLength = std::strlen(m_word.c_str());
        m_wordLengthValid = true;
    }
    return m_wordLength;
}

const std::string WordBlock::operator+(const WordBlock &rhsWord)
{
    cout << "WordBlock: Adding " << getWord() << " and " << rhsWord.getWord() << endl;
    return std::string(m_word + " " + rhsWord.getWord());
}

void WordBlock::operator=(const WordBlock &rhsWord)
{
    cout << "WordBlock: Assigning " << rhsWord.getWord() << " <WordBlock> to object. " << endl;
    setWord(rhsWord.m_word);
}

void WordBlock::operator=(const std::string rhsWord)
{
    cout << "WordBlock: Assigning " << rhsWord << " <std::string> to object." << endl;
    setWord(rhsWord);
}

const char &WordBlock::operator[](std::size_t pos)
{
    cout << "WordBlock: Retriving " << pos << "th index value of " << getWord() << endl;
    return (getWord().at(pos));
}

std::ostream &operator<<(std::ostream &os, const WordBlock &rhsWord)
{
    cout << "WordBlock: Printing " << rhsWord.getWord() << endl;
    os << rhsWord.getWord();
    return os;
}

int main()
{

    std::vector<int> numbers = {1, 23, 3, 435, 423};

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
     *
     * Couldn't reproduce this, even after non-const return from + operator func.
     * word1 + word2 = word3
     */
    WordBlock word1("Sagar");
    WordBlock word2 = "Sutar";
    WordBlock word3(word1);
    WordBlock word4;

    word3 = word1 + word2;
    word4 = word3;
    cout << word4[3] << endl;
    cout << word4 << "  - Length: " << word4.getWordLen() << endl;

    return 0;
}