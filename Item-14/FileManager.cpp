#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
using namespace std;

class File{
public:
    File(std::string filePath, std::ios_base::openmode operationMode = std::ios::out) :
    m_filePath(filePath),
    m_filePtr(std::shared_ptr<fstream>(new fstream(filePath, operationMode), fileDeleter))
    {
        cout << "File: Default Constructor called. " << this << endl;
    }

    // Ownership transfered
    File(const File &file){
         cout << "File: Copy Constructor called. " << this << endl;
        m_filePath = file.m_filePath;
        // m_filePtr.reset(file.m_filePtr.get());
        m_filePtr = std::shared_ptr<ifstream>(new ifstream(m_filePath), fileDeleter);
    }

    // Disallow assignment.
    File& operator=(const File &file) = delete;

    ~File(){
        cout << "File: Destructor called. " << this << endl;
    }

    static void fileDeleter(fstream *file){ 
        cout << "File: Custom ifstream deleter called." << endl;        
        if(file->is_open())
            file->close();       
        delete file;
    }

    void write(std::string data){
        if(isOpen()){
            m_filePtr.get()->write(data.c_str(), data.length());
        }
        else{
            cout << "File: Can't write to a closed file.\n";
        }
    }
    
    //!< \brief Returns a byte vector of the file contents.
    std::vector<char> fileToByteVec(){
        if(isOpen()){
            int fileSize = getSize() ;
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
};

int main(){
    cout << "0\n";
    File f("random.txt");
    File f1 = f;
    cout << "2\n";
    return 0;
}