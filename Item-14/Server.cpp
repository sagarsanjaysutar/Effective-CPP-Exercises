/**
 * \brief Item 14: Think carefully about copying behaviour in resource-managing classes.
 */

#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include "FileManager.cpp"

#define PORT_NUMBER 1024

using namespace boost::asio;
using boost::asio::ip::udp;
using namespace std;

class Server{
public:
    Server() : m_udpSocket(m_ioContext){
        cout << "Server::Server()\n";

        initiateSocketConn();
    }
    ~Server(){
        cout << "Server::~Server()\n";
        if(m_udpSocket.is_open())
            m_udpSocket.close();
    }

     void receiveByteData(std::vector<char> &fileData){
        if(!m_udpSocket.is_open()){
            cout << "Server: Socket not open for sharing data.\n";
            return;
        }
        else{
            try{
                cout << "Server: Waiting for data from client...\n";
                boost::system::error_code err;
                int bytesRead = m_udpSocket.receive_from(boost::asio::buffer(fileData, fileData.size()), m_endpoint, 0, err);

                if(err)
                    throw std::runtime_error(err.message());
                else{
                    fileData.resize(bytesRead);
                    std::cout << "Server: Received " << bytesRead << " bytes from " << m_endpoint << "\n";
                }
            }catch(std::exception &ex){
                cout << "Server: Failed to receive message to the localhost with port " << PORT_NUMBER;
            cout << ": " << ex.what() << endl;
            }

            m_udpSocket.close();
        }    
    }

private:
    // Provides the core I/O features.
    boost::asio::io_context m_ioContext;

    // Server endpoint
    boost::asio::ip::udp::endpoint m_endpoint;

    // UDP Socket
    boost::asio::ip::udp::socket m_udpSocket;

    // Initialise the socket connection
    void initiateSocketConn(){
        try{
            boost::system::error_code err;

            // Initialise the server endpoint
            m_endpoint.address(boost::asio::ip::address_v4::any());
            m_endpoint.port(PORT_NUMBER);

            // Opens a socket without binding to a specific port.
            m_udpSocket.open(udp::v4(), err);

            // Binding the socket to the localhost & the specified port number
            m_udpSocket.bind(m_endpoint, err);

            if(err){
                throw std::runtime_error(err.message());
            }
            else{
                cout << "Client: Socket bind to localhost with port " << PORT_NUMBER << " successful." << endl;
            }

        }catch(std::exception& ex){
            cout << "Client: Failed to bind the socket to the localhost with port " << PORT_NUMBER;
            cout << ": " << ex.what() << endl;
        }
    }

   
};

int main()
{
    std::vector<char> receivedStrBuffer(100);
    Server obj;
    obj.receiveByteData(receivedStrBuffer);

    File file("server.txt", std::ios::out);
    file.write(std::string(receivedStrBuffer.begin(), receivedStrBuffer.end()));

    return 0;
}