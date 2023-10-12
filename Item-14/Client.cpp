#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <vector>

using namespace boost::asio;
using boost::asio::ip::udp;
using namespace std;

class File{
public:
    File(std::string filePath, std::ios_base::openmode operationMode = std::ios::out | std::ios::in) :
    m_file(filePath, operationMode)
    {
        cout << "File: Default Constructor called. " << this << endl;
    }

    ~File(){
        cout << "File: Destructor called. " << this << endl;
        m_file.close();
    }

    void write(std::string data){
        cout << "write 0\n";
        if(isOpen()){
            cout << "write 1\n";
            m_file.write(data.c_str(), data.length());
            cout << "write 2\n";
            
        }
        cout << "write 3\n";
    }

    bool isOpen(){ return m_file.is_open(); }

    boost::asio::const_buffer convertFileToBuffer(){
        if(isOpen()){
            m_byteDataVec.clear();
            m_file.clear();
            m_file.seekg(0);
            cout << "eof " << m_file.eof();
            std::string fileLine;
            while(getline(m_file, fileLine)){
                cout << "\ncc " << fileLine << endl;
                // std::vector<char> bytes(fileLine.begin(), fileLine.end());
                // const char *cStr = fileLine.c_str() + '\0';
                for(char byte : fileLine){
                    m_byteDataVec.push_back(byte);
                }
                m_byteDataVec.push_back('\n');
            }           
            cout << "\nxx \t" << m_byteDataVec.size() <<"\n";
            return boost::asio::const_buffer(m_byteDataVec.data(), m_byteDataVec.size());
        }
        else{
            cout << "File not open;\n";
        }
    }
private:
    fstream m_file;
    std::vector<char> m_byteDataVec;
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
    udpSocket.send_to(file.convertFileToBuffer(), serverEndpoint);
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