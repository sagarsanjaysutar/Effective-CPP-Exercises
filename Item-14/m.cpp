#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

std::vector<char> convertFileToBuffer(std::fstream &file){
        if(file.is_open()){
            std::vector<char> m_byteDataVec;
            // m_byteDataVec.clear();
            file.clear();
            file.seekg(0);
            std::string fileLine;
            while(getline(file, fileLine)){
                for(char byte : fileLine)
                    m_byteDataVec.push_back(byte);
                m_byteDataVec.push_back('\n');
            }           
            return m_byteDataVec;
        }
        else{
            cout << "File not open;\n";
        }
    }

     std::vector<char> fileToByteVec(std::fstream &file){
        if(file.is_open()){
            file.seekg(0, std::ios_base::end);
            int fileSize = file.tellg();
            file.seekg(0, std::ios_base::beg);
            
            char buffer[fileSize];
            file.read(buffer, fileSize);

            return std::vector<char>(buffer, buffer + fileSize); 
        } 
        else{
            cout << "File not open;\n";
        }      
    }

int main() {
    // Create an fstream object and open a file in read and write mode
    std::ios_base::openmode operationMode = std::ios::in | std::ios::out;
    std::fstream file;
    file.open("random.txt", operationMode);
    
    // std::fstream file2;("random.txt", operationMode);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        // return 1;
    }
    file.open("random.txt", operationMode);
    if(!file.is_open()){
        std::cerr << "Failed to open the file." << std::endl;
    }
    return 0;

    // // Write data to the file
    // file << "Hello, World!" << std::endl;

    // // Seek to the beginning of the file
    // file.seekg(0);

    // // Read data from the file
    // std::string line;
    // std::getline(file, line);

    // // Print the read data
    // std::cout << "Read from file: " << line << std::endl;
    // cout << "0\n";
    

    // file.seekg(0, std::ios_base::end);
    // streampos fileSizePos = file.tellg();
    // int fileSize = fileSizePos;
    // file.seekg(0, std::ios_base::beg);
    
    // char fileContent[fileSize];
    

    // file.read(fileContent, fileSize);

    // std::vector<char> fileVec(fileContent, fileContent + fileSize);
    // std::vector<char> fileVec(convertFileToBuffer(file));
    

    for(char c : fileToByteVec(file)){
        cout << c;
    }
    
    cout << "\nxx\n" ;

    for(char c : fileToByteVec(file)){
        cout << c;
    }
    cout << "\nxx\n" ;
    // Close the file
    file.close();

    return 0;
}
