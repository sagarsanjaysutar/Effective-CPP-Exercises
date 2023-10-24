#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <vector>
#include "FileManager.cpp"

#define PORT_NUMBER 1024

using namespace boost::asio;
using boost::asio::ip::udp;
using namespace std;

/**
 * \brief A UDP based client which opens a File, writes some data to it & then sends it to a server.
*/
class Client{
public:
    Client() : m_udpSocket(m_ioContext){
        cout << "Client::Client()\n";

        initiateSocketConn();     
    }
    ~Client(){
        cout << "~Client::Client()\n";
        if(m_udpSocket.is_open())
            m_udpSocket.close();
    }    

    // Blocking function
    void sendByteData(std::vector<char> byteData){

        if(!m_udpSocket.is_open()){
            cout << "Client: Socket not open for sharing data.\n";
            return;
        }
        else{
            try{
                boost::system::error_code err;
                m_udpSocket.send_to(boost::asio::buffer(byteData, byteData.size()), m_serverEndpoint, 0, err);

                if(err)
                    throw std::runtime_error(err.message());
                else{
                    cout << "Client: Message sent.\n";                    
                }
            }catch(std::exception &ex){
                cout << "Client: Failed to send message to the localhost with port " << PORT_NUMBER;
            cout << ": " << ex.what() << endl;
            }

            m_udpSocket.close();
        }
    }

private:
    // Provides the core I/O features.
    boost::asio::io_context m_ioContext;

    // Server endpoint
    boost::asio::ip::udp::endpoint m_serverEndpoint;

    // UDP Socket
    boost::asio::ip::udp::socket m_udpSocket;

    // Initialise the socket connection
    void initiateSocketConn(){
        try{
            boost::system::error_code err;

            // Initialise the server endpoint
            m_serverEndpoint.address(boost::asio::ip::address_v4::any());
            m_serverEndpoint.port(PORT_NUMBER);

            // Opens a socket without binding to a specific port.
            m_udpSocket.open(udp::v4(), err);

            // Binding the socket to the localhost & the specified port number
            m_udpSocket.bind(m_serverEndpoint, err);

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

int main(int argc, char *argv[]){
    
    File file("/home/ssutar/Tutorials/Effective-CPP/Item-14/client.txt");
    file.write("Stuff written by Client.\n");

    Client obj;
    obj.sendByteData(file.fileToByteVec());

    return 0;
}