#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <cstring>
using namespace std;

/**
 * File: A File Manager class. Handles safe creation, ownership transfer & deletion of the fstream object.
*/
class File{
public:
    File(std::string filePath, std::ios_base::openmode operationMode = std::ios_base::in | std::ios_base::out) :
    m_operationMode(operationMode),
    m_filePath(filePath),
    m_filePtr(std::shared_ptr<fstream>(new fstream(filePath, operationMode), fileDeleter))
    {
        cout << "xxx \t " << std::ios::in << "\n";
        cout << "xxx \t " << std::ios::out << "\n";
        cout << "xxx \t " << m_filePtr.get()->is_open() << "\n";
        cout << "File: Default Constructor called. " << this;
        cout << " | fstream created " << m_filePtr.get() << endl;
    }
    
    //!< \brief Copy Constructor
    File(const File &file){        
        cout << "File: Copy Constructor called. " << this;
        m_filePath = file.m_filePath;
        m_operationMode = file.m_operationMode;

        // Shallow copy: Here the ownership of file is transferred.
        // In O/P, you will notice only one file object gets deleted once the program ends.
        // m_filePtr.reset(file.m_filePtr.get());

        // Deep Copy: We make a new copy of the file object.
        // In O/P, you will see two file objects gets deleted, one that this class holds 
        // & another the parent oject which was used during the copy construction.
        std::shared_ptr<fstream> fileCopy = std::shared_ptr<fstream>(new fstream(m_filePath, m_operationMode), fileDeleter);
        m_filePtr.swap(fileCopy);
        
        cout << " | fstream created " << m_filePtr.get() << endl;
    }

    // Disallow assignment.
    File& operator=(const File &file) = delete;

    ~File(){
        cout << "File: Destructor called. " << this << endl;
    }

    //!< \brief Custom deleter for the fstream object.
    static void fileDeleter(fstream *file){ 
        cout << "File: Custom ifstream deleter called. " << file << endl;        
        if(file->is_open())
            file->close();       
        delete file;
    }

    //!< \brief Basic write function.
    void write(std::string data){
        if(isOpen()){
            m_filePtr.get()->write(data.c_str(), data.length());
            cout << "File: Written " << data.size() << " bytes to " << m_filePath << endl;
        }
        else{
            cout << "File: Can't write to a closed file.\n";
        }
    }
    
    //!< \brief Returns a byte vector of the file contents.
    std::vector<char> fileToByteVec(){
        if(isOpen()){
            int fileSize = getSize();
            char buffer[fileSize];            
            m_filePtr.get()->read(buffer, fileSize);
            return std::vector<char>(buffer, buffer + fileSize);
        }
        else{
            cout << "File not open;\n";            
        }
    }

    //!< \brief Checks if file is open.
    bool isOpen(){ return m_filePtr.get()->is_open(); }

    //!< \brief Closes the file.
    void close(){
        if(isOpen()){
            m_filePtr.get()->close();
        }
    }

    //!< \brief Returns total file size.
    int getSize(){
        if(isOpen()){
            m_filePtr.get()->seekg(0, std::ios_base::end);
            streampos fileSize = m_filePtr.get()->tellg();
            m_filePtr.get()->seekg(0, std::ios_base::beg);
            return fileSize;
        }
        else{
            cout << "File not open;\n";
            return 0;       
        }
    }

private:
    std::shared_ptr<fstream> m_filePtr;
    std::string m_filePath;
    std::ios_base::openmode m_operationMode;
};


/**============= Following are testing function for the FileManager class =============*/
/**
 * \brief In this function we test whether the File's shared pointer keep the underlying fstream alive.
*/
// void randonFunction(File &obj){
//     cout << "randonFunction() called with " << &obj << endl;
//     std::this_thread::sleep_for(std::chrono::seconds(5));
//     cout << "randonFunction() ended.\n";
// }

// /**
//  * \brief In this function we test the ownership/copy construction behaviour of the File.
// */
// void basicTest(){
//     cout << "basicTest() called.\n";
//     File f("/home/ssutar/Tutorials/Effective-CPP/Item-14/random.txt");
//     File f1 = f;
//     f1.write("Sagar");
//     for(char c : f1.fileToByteVec()){
//         cout << c;
//     }
//     cout << "\n";
//     randonFunction(f1);
//     cout << "basicTest() ended.\n";
// }
// int main(){
//     cout << "======================= File Manager Creation/Deletion =======================\n";
//     basicTest();
//     cout << "==============================================================================\n";
//     return 0;
// }