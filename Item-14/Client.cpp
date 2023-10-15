#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <vector>

using namespace boost::asio;
using boost::asio::ip::udp;
using namespace std;

class File{
public:
    File(std::string filePath, std::ios_base::openmode operationMode = std::ios::out) :
    m_filePath(filePath),
    m_file(filePath, operationMode)
    {
        cout << "File: Default Constructor called. " << this << endl;
    }

    ~File(){
        cout << "File: Destructor called. " << this << endl;
        close();
    }

    void write(std::string data){
        if(isOpen()){
            m_file.write(data.c_str(), data.length());
        }
        else{
            cout << "File: Can't write to a closed file.\n";
        }
    }
    
    //!< \deprecated This has been depreciated due to overcomplicated logic. Use fileToByteVec instead.
    boost::asio::const_buffer convertFileToBuffer(){
        if(isOpen()){
            // Clears any previous flag on the files like EOS & resets it's internal pointer.
            m_file.clear();
            m_file.seekg(0);

            std::vector<char> bufferByteVec;
            std::string fileLine;
            while(getline(m_file, fileLine)){
                for(char byte : fileLine)
                    bufferByteVec.push_back(byte);
                bufferByteVec.push_back('\n');
            }           
            return boost::asio::const_buffer(bufferByteVec.data(), bufferByteVec.size());
        }
        else{
            cout << "File not open;\n";            
        }
    }

    //!< \brief Returns a byte vector of the file contents.
    std::vector<char> fileToByteVec(){
        if(isOpen()){
            cout << "fileToByteVec 0" << endl;
            int fileSize = getSize() ;
            cout << "fileToByteVec 1" << endl;

            char buffer[fileSize];
            cout << "fileToByteVec 2" << endl;
            m_file.read(buffer, fileSize);
            cout << "fileToByteVec 3" << endl;
            return std::vector<char>(buffer, buffer + fileSize);
        }
        else{
            cout << "File not open;\n";            
        }
    }

    //!< \brief Checks if file is open.
    bool isOpen(){ return m_file.is_open(); }

    //!< \brief Closes the file.
    void close(){
        if(isOpen()){
            m_file.close();
        }
    }

    //!< \brief Returns total file size.
    int getSize(){
        if(isOpen()){
            m_file.seekg(0, std::ios_base::end);
            streampos fileSize = m_file.tellg();
            m_file.seekg(0, std::ios_base::beg);
            return fileSize;
        }
        else{
            cout << "File not open;\n";
            return 0;       
        }
    }

private:
    fstream m_file;
    std::string m_filePath;
};



int main(int argc, char *argv[]){
    
    File file("/home/ssutar/Tutorials/Effective-CPP/Item-14/random.txt"); 
    file.write("Stuff written by client\n");
    
    cout << "0\n";    
    io_service ioService;
    udp::resolver resolver(ioService);
    udp::endpoint serverEndpoint = *resolver.resolve(udp::resolver::query(udp::v4(), "localhost", "1024")); // why third parameter?
    cout << "1\n";
    udp::socket udpSocket(ioService);
    cout << "2\n";
    udpSocket.open(udp::v4());
    cout << "3\n";
    // Sending Single string is success.
    // std::string dataStr("sagar");
    // std::vector<char> dataVec(dataStr.begin(), dataStr.end());
    
    // char* data1 = "sagar";
    // char* data2 = "sutar";
    // std::vector<char> dataVec = { data1, data2 };
    // udpSocket.send_to(boost::asio::buffer(dataVec.data(), dataVec.size()), serverEndpoint);
    // Deallocate memory when done
    // for (char* str : dataVec) {
    //     delete[] str;
    // }
    // std::vector<std::vector<char> dataVec(dataStr.begin(), dataStr.end());


    // udpSocket.send_to(file.convertFileToBuffer(), serverEndpoint);
    udpSocket.send_to(boost::asio::buffer(file.fileToByteVec().data(), file.getSize()), serverEndpoint);
    // return 0;
    cout << "2\n";
    std::array<char, 10> receivedACK;
    cout << "3\n";
    udp::endpoint clientEndpoint;
    cout << "4\n";
    size_t len = udpSocket.receive_from(buffer(receivedACK), clientEndpoint);
    cout << "5\n";
    std::cout.write(receivedACK.data(), len);
    cout << "3\n";
    return 0;
}